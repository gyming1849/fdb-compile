#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
/*
 * PriorityMultiLock.actor.h
 *
 * This source file is part of the FoundationDB open source project
 *
 * Copyright 2013-2022 Apple Inc. and the FoundationDB project authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// When actually compiled (NO_INTELLISENSE), include the generated version of this file.  In intellisense use the source
// version.
#if defined(NO_INTELLISENSE) && !defined(FLOW_PRIORITYMULTILOCK_ACTOR_G_H)
#define FLOW_PRIORITYMULTILOCK_ACTOR_G_H
#include "flow/PriorityMultiLock.actor.g.h"
#elif !defined(PRIORITYMULTILOCK_ACTOR_H)
#define PRIORITYMULTILOCK_ACTOR_H

#include "flow/flow.h"
#include <boost/intrusive/list.hpp>
#include "flow/actorcompiler.h" // This must be the last #include.

#define PRIORITYMULTILOCK_DEBUG 0

#if PRIORITYMULTILOCK_DEBUG || !defined(NO_INTELLISENSE)
#define pml_debug_printf(...)                                                                                          \
	if (now() > 0) {                                                                                                   \
		printf("pml line=%04d ", __LINE__);                                                                            \
		printf(__VA_ARGS__);                                                                                           \
	}
#else
#define pml_debug_printf(...)
#endif

// A multi user lock with a concurrent holder limit where waiters request a lock with a priority
// id and are granted locks based on a total concurrency and relative weights of the current active
// priorities.  Priority id's must start at 0 and are sequential integers.  Priority id numbers
// are not related to the importance of the priority in execution.
//
// Scheduling logic
// Let
// 	 weights[n] = configured weight for priority n
//   waiters[n] = the number of waiters for priority n
//   runnerCounts[n] = number of runners at priority n
//
//   totalPendingWeights = sum of weights for all priorities with waiters[n] > 0
//   When waiters[n] becomes == 0, totalPendingWeights -= weights[n]
//   When waiters[n] becomes  > 0, totalPendingWeights += weights[n]
//
//   The total capacity of a priority to be considered when launching tasks is
//     ceil(weights[n] / totalPendingWeights * concurrency)
//
// For improved memory locality the properties mentioned above are stored as priorities[n].<property>
// in the actual implementation.
//
// The interface is similar to FlowMutex except that lock holders can just drop the lock to release it.
//
// Usage:
//   Lock lock = wait(prioritylock.lock(priority_id));
//   lock.release();  // Explicit release, or
//   // let lock and all copies of lock go out of scope to release
class PriorityMultiLock : public ReferenceCounted<PriorityMultiLock> {
public:
	// Waiting on the lock returns a Lock, which is really just a Promise<Void>
	// Calling release() is not necessary, it exists in case the Lock holder wants to explicitly release
	// the Lock before it goes out of scope.
	struct Lock {
		void release() { promise.send(Void()); }
		bool isLocked() const { return promise.canBeSet(); }

		// This is exposed in case the caller wants to use/copy it directly
		Promise<Void> promise;
	};

	PriorityMultiLock(int concurrency, std::string weights)
	  : PriorityMultiLock(concurrency, parseStringToVector<int>(weights, ',')) {}

	PriorityMultiLock(int concurrency, std::vector<int> weightsByPriority)
	  : concurrency(concurrency), available(concurrency), waiting(0), totalPendingWeights(0), killed(false) {

		priorities.resize(weightsByPriority.size());
		for (int i = 0; i < priorities.size(); ++i) {
			priorities[i].priority = i;
			priorities[i].weight = weightsByPriority[i];
		}

		fRunner = runner(this);
	}

	~PriorityMultiLock() { kill(); }

	Future<Lock> lock(int priority = 0) {
		if (killed)
			throw broken_promise();

		Priority& p = priorities[priority];
		Queue& q = p.queue;

		// If this priority currently has no waiters
		if (q.empty()) {
			// Add this priority's weight to the total for priorities with pending work.  This must be done
			// so that currenctCapacity() below will assign capacaity to this priority.
			totalPendingWeights += p.weight;

			// If there are slots available and the priority has capacity then don't make the caller wait
			if (available > 0 && p.runners < currentCapacity(p.weight)) {
				// Remove this priority's weight from the total since it will remain empty
				totalPendingWeights -= p.weight;

				// Return a Lock to the caller
				Lock lock;
				addRunner(lock, &p);

				pml_debug_printf("lock nowait priority %d  %s\n", priority, toString().c_str());
				return lock;
			}

			// If we didn't return above then add the priority to the waitingPriorities list
			waitingPriorities.push_back(p);
		}

		Waiter& w = q.emplace_back();
		++waiting;

		pml_debug_printf("lock wait priority %d  %s\n", priority, toString().c_str());
		return w.lockPromise.getFuture();
	}

	// Halt stops the PML from handing out any new locks but leaves waiters and runners alone.
	// Existing and new waiters will not see an error, they will just never get a lock.
	// Can be safely called multiple times.
	void halt() {
		pml_debug_printf("halt %s\n", toString().c_str());
		brokenOnDestruct.reset();

		if (fRunner.isValid()) {
			fRunner.cancel();
			// Adjust available and concurrency so that if all runners finish the available
			available -= concurrency;
			concurrency = 0;
		}

		waitingPriorities.clear();
	}

	// Halt, then make existing and new waiters get a broken_promise error.
	// Can be safely called multiple times.
	void kill() {
		if (!killed) {
			// Killed must be set first because waiters which ignore exceptions could call wait again immediately.
			killed = true;
			halt();
			for (auto& p : priorities) {
				p.queue.clear();
			}
		}
	}

	std::string toString() const {
		std::string s = format("{ ptr=%p concurrency=%d available=%d running=%d waiting=%d "
		                       "pendingWeights=%d ",
		                       this,
		                       concurrency,
		                       available,
		                       concurrency - available,
		                       waiting,
		                       totalPendingWeights);

		for (auto& p : priorities) {
			s += format("{%s} ", p.toString(this).c_str());
		}

		s += "}";

		return s;
	}

	int maxPriority() const { return priorities.size() - 1; }

	int getRunnersCount() const { return concurrency - available; }
	int getWaitersCount() const { return waiting; }

	int getWaitersCount(const unsigned int priority) const {
		ASSERT(priority < priorities.size());
		return priorities[priority].queue.size();
	}

	int getRunnersCount(const unsigned int priority) const {
		ASSERT(priority < priorities.size());
		return priorities[priority].runners;
	}

private:
	struct Waiter {
		Promise<Lock> lockPromise;
	};

	// Total execution slots allowed across all priorities
	int concurrency;
	// Current available execution slots
	int available;
	// Total waiters across all priorities
	int waiting;
	// Sum of weights for all priorities with 1 or more waiters
	int totalPendingWeights;

	typedef Deque<Waiter> Queue;

	struct Priority : boost::intrusive::list_base_hook<> {
		Priority() : runners(0), weight(0), priority(-1) {}

		// Queue of waiters at this priority
		Queue queue;
		// Number of runners at this priority
		int runners;
		// Configured weight for this priority
		int weight;
		// Priority number for convenience, matches *this's index in PML priorities vector
		int priority;

		std::string toString(const PriorityMultiLock* pml) const {
			return format("priority=%d weight=%d run=%d wait=%d cap=%d",
			              priority,
			              weight,
			              runners,
			              queue.size(),
			              queue.empty() ? 0 : pml->currentCapacity(weight));
		}
	};

	std::vector<Priority> priorities;
	typedef boost::intrusive::list<Priority, boost::intrusive::constant_time_size<false>> WaitingPrioritiesList;

	// List of all priorities with 1 or more waiters.  This list exists so that the scheduling loop
	// does not have to iterage over the priorities vector checking priorities without waiters.
	WaitingPrioritiesList waitingPriorities;

	Future<Void> fRunner;
	AsyncTrigger wakeRunner;
	Promise<Void> brokenOnDestruct;
	bool killed;

																#line 257 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
// This generated class is to be used only via handleRelease()
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
template <class HandleReleaseActor>
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
class HandleReleaseActorState {
															#line 263 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
public:
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	HandleReleaseActorState(Reference<PriorityMultiLock> const& self,Priority* const& priority,Future<Void> const& holder) 
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		 : self(self),
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		   priority(priority),
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		   holder(holder)
															#line 274 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
	{
		fdb_probe_actor_create("handleRelease", reinterpret_cast<unsigned long>(this));

	}
	~HandleReleaseActorState() 
	{
		fdb_probe_actor_destroy("handleRelease", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 256 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("%f handleRelease self=%p start\n", now(), self.getPtr());
															#line 289 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			try {
															#line 258 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				StrictFuture<Void> __when_expr_0 = holder;
															#line 258 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 295 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				static_cast<HandleReleaseActor*>(this)->actor_wait_state = 1;
															#line 258 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< HandleReleaseActor, 0, Void >*>(static_cast<HandleReleaseActor*>(this)));
															#line 299 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				loopDepth = 0;
			}
			catch (Error& error) {
				loopDepth = a_body1Catch2(error, loopDepth);
			} catch (...) {
				loopDepth = a_body1Catch2(unknown_error(), loopDepth);
			}
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch1(Error error,int loopDepth=0) 
	{
		delete static_cast<HandleReleaseActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 264 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("lock release priority %d  %s\n", (int)(priority->priority), self->toString().c_str());
															#line 266 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("%f handleRelease self=%p releasing\n", now(), self.getPtr());
															#line 267 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		++self->available;
															#line 268 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		priority->runners -= 1;
															#line 271 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		if (self->waiting > 0)
															#line 335 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		{
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			self->wakeRunner.trigger();
															#line 339 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		}
		loopDepth = a_body1cont7(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 261 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("%f handleRelease self=%p error %s\n", now(), self.getPtr(), e.what());
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			loopDepth = a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(Void const& _,int loopDepth) 
	{
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("%f handleRelease self=%p success\n", now(), self.getPtr());
															#line 365 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("%f handleRelease self=%p success\n", now(), self.getPtr());
															#line 374 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont2(_, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<HandleReleaseActor*>(this)->actor_wait_state > 0) static_cast<HandleReleaseActor*>(this)->actor_wait_state = 0;
		static_cast<HandleReleaseActor*>(this)->ActorCallback< HandleReleaseActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< HandleReleaseActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("handleRelease", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<HandleReleaseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("handleRelease", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< HandleReleaseActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("handleRelease", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<HandleReleaseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("handleRelease", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< HandleReleaseActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("handleRelease", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<HandleReleaseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("handleRelease", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont4(int loopDepth) 
	{
		try {
			loopDepth = a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont7(int loopDepth) 
	{
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		delete static_cast<HandleReleaseActor*>(this);
															#line 471 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	Reference<PriorityMultiLock> self;
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	Priority* priority;
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	Future<Void> holder;
															#line 482 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
};
// This generated class is to be used only via handleRelease()
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
class HandleReleaseActor final : public Actor<void>, public ActorCallback< HandleReleaseActor, 0, Void >, public FastAllocated<HandleReleaseActor>, public HandleReleaseActorState<HandleReleaseActor> {
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
public:
	using FastAllocated<HandleReleaseActor>::operator new;
	using FastAllocated<HandleReleaseActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(2787882295027842048UL, 9227132448034290688UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< HandleReleaseActor, 0, Void >;
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	HandleReleaseActor(Reference<PriorityMultiLock> const& self,Priority* const& priority,Future<Void> const& holder) 
															#line 504 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		 : Actor<void>(),
		   HandleReleaseActorState<HandleReleaseActor>(self, priority, holder),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("handleRelease", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(6658627256276112384UL, 15392802504858084352UL);
		ActorExecutionContextHelper __helper(static_cast<HandleReleaseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("handleRelease");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("handleRelease", reinterpret_cast<unsigned long>(this), -1);

	}
};
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
static void handleRelease( Reference<PriorityMultiLock> const& self, Priority* const& priority, Future<Void> const& holder ) {
															#line 255 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	new HandleReleaseActor(self, priority, holder);
															#line 527 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
}

#line 275 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"

	void addRunner(Lock& lock, Priority* priority) {
		priority->runners += 1;
		--available;
		handleRelease(Reference<PriorityMultiLock>::addRef(this), priority, lock.promise.getFuture());
	}

	// Current maximum running tasks for the specified priority, which must have waiters
	// or the result is undefined
	int currentCapacity(int weight) const {
		// The total concurrency allowed for this priority at present is the total concurrency times
		// priority's weight divided by the total weights for all priorities with waiters.
		return ceil((float)weight / totalPendingWeights * concurrency);
	}

																#line 546 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
// This generated class is to be used only via runner()
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
template <class RunnerActor>
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
class RunnerActorState {
															#line 552 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
public:
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	RunnerActorState(PriorityMultiLock* const& self) 
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		 : self(self),
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		   error(self->brokenOnDestruct.getFuture()),
															#line 294 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		   p(self->waitingPriorities.end())
															#line 563 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
	{
		fdb_probe_actor_create("runner", reinterpret_cast<unsigned long>(this));

	}
	~RunnerActorState() 
	{
		fdb_probe_actor_destroy("runner", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 296 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			;
															#line 578 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			loopDepth = a_body1loopHead1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch1(Error error,int loopDepth=0) 
	{
		this->~RunnerActorState();
		static_cast<RunnerActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1(int loopDepth) 
	{
															#line 297 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("runner loop start  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 300 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("runner loop waitTrigger  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 301 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		StrictFuture<Void> __when_expr_0 = self->wakeRunner.onTrigger();
															#line 301 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		if (static_cast<RunnerActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 614 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
		static_cast<RunnerActor*>(this)->actor_wait_state = 1;
															#line 301 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RunnerActor, 0, Void >*>(static_cast<RunnerActor*>(this)));
															#line 619 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(Void const& _,int loopDepth) 
	{
															#line 302 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("%f runner loop wake  priority=%d  %s\n", now(), p->priority, self->toString().c_str());
															#line 305 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		for(;self->available > 0 && self->waiting > 0;) {
															#line 306 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("  launch loop start  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 309 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			for(;;) {
															#line 310 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				if (p == self->waitingPriorities.end())
															#line 636 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				{
															#line 311 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
					p = self->waitingPriorities.begin();
															#line 640 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				}
															#line 314 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				pml_debug_printf("    launch loop scan  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 316 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				if (!p->queue.empty() && p->runners < self->currentCapacity(p->weight))
															#line 646 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				{
					break;
				}
															#line 319 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				++p;
															#line 652 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 322 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Queue& queue = p->queue;
															#line 323 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Waiter w = queue.front();
															#line 324 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			queue.pop_front();
															#line 328 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Priority* pPriority = &*p;
															#line 329 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (queue.empty())
															#line 664 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 330 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				p = self->waitingPriorities.erase(p);
															#line 331 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				self->totalPendingWeights -= pPriority->weight;
															#line 333 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				pml_debug_printf( "      emptied priority  priority=%d  %s\n", pPriority->priority, self->toString().c_str());
															#line 672 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 337 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			--self->waiting;
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Lock lock;
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			w.lockPromise.send(lock);
															#line 343 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (error.isReady())
															#line 682 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 344 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				return a_body1Catch1(error.getError(), std::max(0, loopDepth - 1));
															#line 686 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (lock.promise.canBeSet())
															#line 690 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				self->addRunner(lock, pPriority);
															#line 694 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 352 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("    launched alreadyDone=%d priority=%d  %s\n", !lock.promise.canBeSet(), pPriority->priority, self->toString().c_str());
															#line 698 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		}
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont1(Void && _,int loopDepth) 
	{
															#line 302 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		pml_debug_printf("%f runner loop wake  priority=%d  %s\n", now(), p->priority, self->toString().c_str());
															#line 305 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
		for(;self->available > 0 && self->waiting > 0;) {
															#line 306 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("  launch loop start  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 309 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			for(;;) {
															#line 310 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				if (p == self->waitingPriorities.end())
															#line 716 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				{
															#line 311 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
					p = self->waitingPriorities.begin();
															#line 720 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				}
															#line 314 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				pml_debug_printf("    launch loop scan  priority=%d  %s\n", p->priority, self->toString().c_str());
															#line 316 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				if (!p->queue.empty() && p->runners < self->currentCapacity(p->weight))
															#line 726 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
				{
					break;
				}
															#line 319 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				++p;
															#line 732 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 322 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Queue& queue = p->queue;
															#line 323 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Waiter w = queue.front();
															#line 324 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			queue.pop_front();
															#line 328 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Priority* pPriority = &*p;
															#line 329 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (queue.empty())
															#line 744 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 330 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				p = self->waitingPriorities.erase(p);
															#line 331 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				self->totalPendingWeights -= pPriority->weight;
															#line 333 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				pml_debug_printf( "      emptied priority  priority=%d  %s\n", pPriority->priority, self->toString().c_str());
															#line 752 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 337 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			--self->waiting;
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			Lock lock;
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			w.lockPromise.send(lock);
															#line 343 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (error.isReady())
															#line 762 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 344 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				return a_body1Catch1(error.getError(), std::max(0, loopDepth - 1));
															#line 766 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			if (lock.promise.canBeSet())
															#line 770 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			{
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
				self->addRunner(lock, pPriority);
															#line 774 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
			}
															#line 352 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
			pml_debug_printf("    launched alreadyDone=%d priority=%d  %s\n", !lock.promise.canBeSet(), pPriority->priority, self->toString().c_str());
															#line 778 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		}
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RunnerActor*>(this)->actor_wait_state > 0) static_cast<RunnerActor*>(this)->actor_wait_state = 0;
		static_cast<RunnerActor*>(this)->ActorCallback< RunnerActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RunnerActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("runner", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunnerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runner", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RunnerActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("runner", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunnerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runner", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RunnerActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("runner", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RunnerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runner", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	PriorityMultiLock* self;
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	Future<Void> error;
															#line 294 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	WaitingPrioritiesList::iterator p;
															#line 865 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
};
// This generated class is to be used only via runner()
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
class RunnerActor final : public Actor<Void>, public ActorCallback< RunnerActor, 0, Void >, public FastAllocated<RunnerActor>, public RunnerActorState<RunnerActor> {
															#line 870 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
public:
	using FastAllocated<RunnerActor>::operator new;
	using FastAllocated<RunnerActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12998288727059383040UL, 7782231169990931968UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RunnerActor, 0, Void >;
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	RunnerActor(PriorityMultiLock* const& self) 
															#line 887 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
		 : Actor<Void>(),
		   RunnerActorState<RunnerActor>(self),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("runner", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(11759470971493413376UL, 9671572266735255808UL);
		ActorExecutionContextHelper __helper(static_cast<RunnerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("runner");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("runner", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RunnerActor, 0, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
[[nodiscard]] static Future<Void> runner( PriorityMultiLock* const& self ) {
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
	return Future<Void>(new RunnerActor(self));
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/PriorityMultiLock.actor.g.h"
}

#line 359 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/PriorityMultiLock.actor.h"
};

#include "flow/unactorcompiler.h"

#endif
