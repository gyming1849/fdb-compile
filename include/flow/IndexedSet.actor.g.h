#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
/*
 * IndexedSet.actor.h
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
#if defined(NO_INTELLISENSE) && !defined(FLOW_INDEXEDSET_ACTOR_G_H)
#define FLOW_INDEXEDSET_ACTOR_G_H
#include "flow/IndexedSet.actor.g.h"
#elif !defined(FLOW_INDEXEDSET_ACTOR_H)
#define FLOW_INDEXEDSET_ACTOR_H

#include "flow/flow.h"
#include "flow/Platform.h"
#include "flow/actorcompiler.h" // This must be the last #include.

															#line 37 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
namespace {
// This generated class is to be used only via ISFreeNodes()
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
template <class Node, class ISFreeNodesActor>
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
class ISFreeNodesActorState {
															#line 44 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
public:
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	ISFreeNodesActorState(std::vector<Node*> const& toFree,bool const& synchronous) 
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		 : toFree(toFree),
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		   synchronous(synchronous),
															#line 40 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		   eraseCount(0),
															#line 47 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		   prefetchQueue()
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
	{
		fdb_probe_actor_create("ISFreeNodes", reinterpret_cast<unsigned long>(this));

	}
	~ISFreeNodesActorState() 
	{
		fdb_probe_actor_destroy("ISFreeNodes", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 48 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			;
															#line 72 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
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
		this->~ISFreeNodesActorState();
		static_cast<ISFreeNodesActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 71 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		if (!static_cast<ISFreeNodesActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~ISFreeNodesActorState(); static_cast<ISFreeNodesActor*>(this)->destroy(); return 0; }
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		new (&static_cast<ISFreeNodesActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~ISFreeNodesActorState();
		static_cast<ISFreeNodesActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

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
															#line 48 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		if (!(!prefetchQueue.empty() || !toFree.empty()))
															#line 114 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 50 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		for(;prefetchQueue.size() < 10 && !toFree.empty();) {
															#line 51 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			_mm_prefetch((const char*)toFree.back(), _MM_HINT_T0);
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			prefetchQueue.push_back(toFree.back());
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			toFree.pop_back();
															#line 126 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		}
															#line 56 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		auto n = prefetchQueue.front();
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		prefetchQueue.pop_front();
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		if (n->child[0])
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		{
															#line 60 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			toFree.push_back(n->child[0]);
															#line 138 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		}
															#line 61 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		if (n->child[1])
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		{
															#line 62 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			toFree.push_back(n->child[1]);
															#line 146 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		}
															#line 63 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		n->child[0] = n->child[1] = 0;
															#line 64 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		delete n;
															#line 65 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		++eraseCount;
															#line 67 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
		if (!synchronous && eraseCount % 1000 == 0)
															#line 156 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		{
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			StrictFuture<Void> __when_expr_0 = yield();
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			if (static_cast<ISFreeNodesActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 162 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
			static_cast<ISFreeNodesActor*>(this)->actor_wait_state = 1;
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ISFreeNodesActor, 0, Void >*>(static_cast<ISFreeNodesActor*>(this)));
															#line 167 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
			loopDepth = 0;
		}
		else
		{
			loopDepth = a_body1loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1break1(int loopDepth) 
	{
		try {
			return a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ISFreeNodesActor*>(this)->actor_wait_state > 0) static_cast<ISFreeNodesActor*>(this)->actor_wait_state = 0;
		static_cast<ISFreeNodesActor*>(this)->ActorCallback< ISFreeNodesActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< ISFreeNodesActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ISFreeNodesActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ISFreeNodesActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ISFreeNodesActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ISFreeNodesActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ISFreeNodesActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("ISFreeNodes", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	std::vector<Node*> toFree;
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	bool synchronous;
															#line 40 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	int eraseCount;
															#line 47 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	Deque<Node*> prefetchQueue;
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
};
// This generated class is to be used only via ISFreeNodes()
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
template <class Node>
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
class ISFreeNodesActor final : public Actor<Void>, public ActorCallback< ISFreeNodesActor<Node>, 0, Void >, public FastAllocated<ISFreeNodesActor<Node>>, public ISFreeNodesActorState<Node, ISFreeNodesActor<Node>> {
															#line 298 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
public:
	using FastAllocated<ISFreeNodesActor<Node>>::operator new;
	using FastAllocated<ISFreeNodesActor<Node>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(7405198265847390720UL, 14099361761464977920UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< ISFreeNodesActor<Node>, 0, Void >;
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	ISFreeNodesActor(std::vector<Node*> const& toFree,bool const& synchronous) 
															#line 315 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
		 : Actor<Void>(),
		   ISFreeNodesActorState<Node, ISFreeNodesActor<Node>>(toFree, synchronous),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("ISFreeNodes", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(8765232048900860416UL, 7242892047979872512UL);
		ActorExecutionContextHelper __helper(static_cast<ISFreeNodesActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("ISFreeNodes");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("ISFreeNodes", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< ISFreeNodesActor<Node>, 0, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
template <class Node>
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
Future<Void> ISFreeNodes( std::vector<Node*> const& toFree, bool const& synchronous ) {
															#line 35 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"
	return Future<Void>(new ISFreeNodesActor<Node>(toFree, synchronous));
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/build/flow/include/flow/IndexedSet.actor.g.h"
}

#line 73 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/IndexedSet.actor.h"

#include "flow/unactorcompiler.h"
#endif
