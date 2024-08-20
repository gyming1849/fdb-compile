#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
/*
 * genericactors.actor.h
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

// When actually compiled (NO_INTELLISENSE), include the generated version of this file.  In intellisense use the source
// version.
#if defined(NO_INTELLISENSE) && !defined(FDBRPC_GENERICACTORS_ACTOR_G_H)
#define FDBRPC_GENERICACTORS_ACTOR_G_H
#include "fdbrpc/genericactors.actor.g.h"
#elif !defined(RPCGENERICACTORS_ACTOR_H)
#define RPCGENERICACTORS_ACTOR_H

#include "flow/genericactors.actor.h"
#include "fdbrpc/fdbrpc.h"
#include "fdbrpc/WellKnownEndpoints.h"
#include "flow/Hostname.h"
#include "flow/actorcompiler.h" // This must be the last #include.

// To avoid diretly access INetworkConnection::net()->removeCachedDNS(), which will require heavy include budget, put
// the call to FlowTransport.actor.cpp as a external function.
extern void removeCachedDNS(const std::string& host, const std::string& service);

															#line 41 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via retryBrokenPromise()
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P, class RetryBrokenPromiseActor>
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryBrokenPromiseActorState {
															#line 48 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryBrokenPromiseActorState(RequestStream<Req, P> const& to,Req const& request) 
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : to(to),
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   request(request)
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("retryBrokenPromise", reinterpret_cast<unsigned long>(this));

	}
	~RetryBrokenPromiseActorState() 
	{
		fdb_probe_actor_destroy("retryBrokenPromise", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 45 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 72 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~RetryBrokenPromiseActorState();
		static_cast<RetryBrokenPromiseActor*>(this)->sendErrorAndDelPromiseRef(error);
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
		try {
															#line 47 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<REPLY_TYPE(Req)> __when_expr_0 = to.getReply(request);
															#line 47 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state < 0) return a_body1loopBody1Catch1(actor_cancelled(), loopDepth);
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1loopBody1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
			static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state = 1;
															#line 47 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RetryBrokenPromiseActor, 0, REPLY_TYPE(Req) >*>(static_cast<RetryBrokenPromiseActor*>(this)));
															#line 110 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1loopBody1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1loopBody1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 50 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() != error_code_broken_promise)
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 51 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(e, std::max(0, loopDepth - 1));
															#line 136 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = delayJittered(FLOW_KNOBS->PREVENT_FAST_SPIN_DELAY);
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1Catch1when1(__when_expr_1.get(), loopDepth); };
			static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state = 2;
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryBrokenPromiseActor, 1, Void >*>(static_cast<RetryBrokenPromiseActor*>(this)));
															#line 149 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1cont2(REPLY_TYPE(Req) const& reply,int loopDepth) 
	{
															#line 48 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<RetryBrokenPromiseActor*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply); this->~RetryBrokenPromiseActorState(); static_cast<RetryBrokenPromiseActor*>(this)->destroy(); return 0; }
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<RetryBrokenPromiseActor*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply);
		this->~RetryBrokenPromiseActorState();
		static_cast<RetryBrokenPromiseActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1cont2(REPLY_TYPE(Req) && reply,int loopDepth) 
	{
															#line 48 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<RetryBrokenPromiseActor*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply); this->~RetryBrokenPromiseActorState(); static_cast<RetryBrokenPromiseActor*>(this)->destroy(); return 0; }
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<RetryBrokenPromiseActor*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply);
		this->~RetryBrokenPromiseActorState();
		static_cast<RetryBrokenPromiseActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(REPLY_TYPE(Req) const& reply,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(reply, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(REPLY_TYPE(Req) && reply,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(std::move(reply), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state > 0) static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state = 0;
		static_cast<RetryBrokenPromiseActor*>(this)->ActorCallback< RetryBrokenPromiseActor, 0, REPLY_TYPE(Req) >::remove();

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor, 0, REPLY_TYPE(Req) >*,REPLY_TYPE(Req) const& value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor, 0, REPLY_TYPE(Req) >*,REPLY_TYPE(Req) && value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RetryBrokenPromiseActor, 0, REPLY_TYPE(Req) >*,Error err) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1Catch1cont1(Void const& _,int loopDepth) 
	{
															#line 54 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		CODE_PROBE(true, "retryBrokenPromise");
															#line 263 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1cont1(Void && _,int loopDepth) 
	{
															#line 54 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		CODE_PROBE(true, "retryBrokenPromise");
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1Catch1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1Catch1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state > 0) static_cast<RetryBrokenPromiseActor*>(this)->actor_wait_state = 0;
		static_cast<RetryBrokenPromiseActor*>(this)->ActorCallback< RetryBrokenPromiseActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1Catch1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1Catch1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RetryBrokenPromiseActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RequestStream<Req, P> to;
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 356 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via retryBrokenPromise()
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P>
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryBrokenPromiseActor final : public Actor<REPLY_TYPE(Req)>, public ActorCallback< RetryBrokenPromiseActor<Req, P>, 0, REPLY_TYPE(Req) >, public ActorCallback< RetryBrokenPromiseActor<Req, P>, 1, Void >, public FastAllocated<RetryBrokenPromiseActor<Req, P>>, public RetryBrokenPromiseActorState<Req, P, RetryBrokenPromiseActor<Req, P>> {
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<RetryBrokenPromiseActor<Req, P>>::operator new;
	using FastAllocated<RetryBrokenPromiseActor<Req, P>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12370115973017772288UL, 11666753539692015360UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Req)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RetryBrokenPromiseActor<Req, P>, 0, REPLY_TYPE(Req) >;
friend struct ActorCallback< RetryBrokenPromiseActor<Req, P>, 1, Void >;
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryBrokenPromiseActor(RequestStream<Req, P> const& to,Req const& request) 
															#line 381 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<REPLY_TYPE(Req)>(),
		   RetryBrokenPromiseActorState<Req, P, RetryBrokenPromiseActor<Req, P>>(to, request),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(1319033180585192448UL, 2205428165340483584UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("retryBrokenPromise");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RetryBrokenPromiseActor<Req, P>, 0, REPLY_TYPE(Req) >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RetryBrokenPromiseActor<Req, P>, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P>
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Req)> retryBrokenPromise( RequestStream<Req, P> const& to, Req const& request ) {
															#line 39 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<REPLY_TYPE(Req)>(new RetryBrokenPromiseActor<Req, P>(to, request));
															#line 417 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 58 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 422 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via retryBrokenPromise()
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P, class RetryBrokenPromiseActor1>
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryBrokenPromiseActor1State {
															#line 429 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryBrokenPromiseActor1State(RequestStream<Req, P> const& to,Req const& request,TaskPriority const& taskID) 
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : to(to),
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   request(request),
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   taskID(taskID)
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("retryBrokenPromise", reinterpret_cast<unsigned long>(this));

	}
	~RetryBrokenPromiseActor1State() 
	{
		fdb_probe_actor_destroy("retryBrokenPromise", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 65 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 455 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~RetryBrokenPromiseActor1State();
		static_cast<RetryBrokenPromiseActor1*>(this)->sendErrorAndDelPromiseRef(error);
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
		try {
															#line 67 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<REPLY_TYPE(Req)> __when_expr_0 = to.getReply(request, taskID);
															#line 67 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state < 0) return a_body1loopBody1Catch1(actor_cancelled(), loopDepth);
															#line 488 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1loopBody1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
			static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state = 1;
															#line 67 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RetryBrokenPromiseActor1, 0, REPLY_TYPE(Req) >*>(static_cast<RetryBrokenPromiseActor1*>(this)));
															#line 493 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1loopBody1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1loopBody1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 70 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() != error_code_broken_promise)
															#line 515 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 71 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(e, std::max(0, loopDepth - 1));
															#line 519 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 72 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 73 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = delayJittered(FLOW_KNOBS->PREVENT_FAST_SPIN_DELAY, taskID);
															#line 73 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 527 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1Catch1when1(__when_expr_1.get(), loopDepth); };
			static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state = 2;
															#line 73 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryBrokenPromiseActor1, 1, Void >*>(static_cast<RetryBrokenPromiseActor1*>(this)));
															#line 532 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1cont2(REPLY_TYPE(Req) const& reply,int loopDepth) 
	{
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<RetryBrokenPromiseActor1*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply); this->~RetryBrokenPromiseActor1State(); static_cast<RetryBrokenPromiseActor1*>(this)->destroy(); return 0; }
															#line 547 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<RetryBrokenPromiseActor1*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply);
		this->~RetryBrokenPromiseActor1State();
		static_cast<RetryBrokenPromiseActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1cont2(REPLY_TYPE(Req) && reply,int loopDepth) 
	{
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<RetryBrokenPromiseActor1*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply); this->~RetryBrokenPromiseActor1State(); static_cast<RetryBrokenPromiseActor1*>(this)->destroy(); return 0; }
															#line 559 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<RetryBrokenPromiseActor1*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply);
		this->~RetryBrokenPromiseActor1State();
		static_cast<RetryBrokenPromiseActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(REPLY_TYPE(Req) const& reply,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(reply, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(REPLY_TYPE(Req) && reply,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(std::move(reply), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state > 0) static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state = 0;
		static_cast<RetryBrokenPromiseActor1*>(this)->ActorCallback< RetryBrokenPromiseActor1, 0, REPLY_TYPE(Req) >::remove();

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor1, 0, REPLY_TYPE(Req) >*,REPLY_TYPE(Req) const& value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor1, 0, REPLY_TYPE(Req) >*,REPLY_TYPE(Req) && value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RetryBrokenPromiseActor1, 0, REPLY_TYPE(Req) >*,Error err) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1Catch1cont1(Void const& _,int loopDepth) 
	{
															#line 74 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		CODE_PROBE(true, "retryBrokenPromise with taskID");
															#line 646 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1cont1(Void && _,int loopDepth) 
	{
															#line 74 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		CODE_PROBE(true, "retryBrokenPromise with taskID");
															#line 655 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1Catch1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1Catch1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1Catch1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state > 0) static_cast<RetryBrokenPromiseActor1*>(this)->actor_wait_state = 0;
		static_cast<RetryBrokenPromiseActor1*>(this)->ActorCallback< RetryBrokenPromiseActor1, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor1, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1Catch1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RetryBrokenPromiseActor1, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1Catch1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RetryBrokenPromiseActor1, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RequestStream<Req, P> to;
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TaskPriority taskID;
															#line 741 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via retryBrokenPromise()
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P>
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryBrokenPromiseActor1 final : public Actor<REPLY_TYPE(Req)>, public ActorCallback< RetryBrokenPromiseActor1<Req, P>, 0, REPLY_TYPE(Req) >, public ActorCallback< RetryBrokenPromiseActor1<Req, P>, 1, Void >, public FastAllocated<RetryBrokenPromiseActor1<Req, P>>, public RetryBrokenPromiseActor1State<Req, P, RetryBrokenPromiseActor1<Req, P>> {
															#line 748 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<RetryBrokenPromiseActor1<Req, P>>::operator new;
	using FastAllocated<RetryBrokenPromiseActor1<Req, P>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12370115973017772288UL, 11666753539692015360UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Req)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RetryBrokenPromiseActor1<Req, P>, 0, REPLY_TYPE(Req) >;
friend struct ActorCallback< RetryBrokenPromiseActor1<Req, P>, 1, Void >;
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryBrokenPromiseActor1(RequestStream<Req, P> const& to,Req const& request,TaskPriority const& taskID) 
															#line 766 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<REPLY_TYPE(Req)>(),
		   RetryBrokenPromiseActor1State<Req, P, RetryBrokenPromiseActor1<Req, P>>(to, request, taskID),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("retryBrokenPromise", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(6570520380275648512UL, 15966776091354598656UL);
		ActorExecutionContextHelper __helper(static_cast<RetryBrokenPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("retryBrokenPromise");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("retryBrokenPromise", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RetryBrokenPromiseActor1<Req, P>, 0, REPLY_TYPE(Req) >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RetryBrokenPromiseActor1<Req, P>, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, bool P>
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Req)> retryBrokenPromise( RequestStream<Req, P> const& to, Req const& request, TaskPriority const& taskID ) {
															#line 59 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<REPLY_TYPE(Req)>(new RetryBrokenPromiseActor1<Req, P>(to, request, taskID));
															#line 802 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 807 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via tryInitializeRequestStream()
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, class TryInitializeRequestStreamActor>
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryInitializeRequestStreamActorState {
															#line 814 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryInitializeRequestStreamActorState(RequestStream<Req>* const& stream,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : stream(stream),
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   hostname(hostname),
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   token(token)
															#line 825 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this));

	}
	~TryInitializeRequestStreamActorState() 
	{
		fdb_probe_actor_destroy("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Optional<NetworkAddress>> __when_expr_0 = hostname.resolve();
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<TryInitializeRequestStreamActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 842 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<TryInitializeRequestStreamActor*>(this)->actor_wait_state = 1;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< TryInitializeRequestStreamActor, 0, Optional<NetworkAddress> >*>(static_cast<TryInitializeRequestStreamActor*>(this)));
															#line 847 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~TryInitializeRequestStreamActorState();
		static_cast<TryInitializeRequestStreamActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
															#line 82 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 870 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 83 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryInitializeRequestStreamActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~TryInitializeRequestStreamActorState(); static_cast<TryInitializeRequestStreamActor*>(this)->destroy(); return 0; }
															#line 874 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryInitializeRequestStreamActor*>(this)->SAV< Void >::value()) Void(Void());
			this->~TryInitializeRequestStreamActorState();
			static_cast<TryInitializeRequestStreamActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		ASSERT(stream != nullptr);
															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		*stream = RequestStream<Req>(Endpoint::wellKnown({ address.get() }, token));
															#line 87 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TryInitializeRequestStreamActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~TryInitializeRequestStreamActorState(); static_cast<TryInitializeRequestStreamActor*>(this)->destroy(); return 0; }
															#line 886 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TryInitializeRequestStreamActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~TryInitializeRequestStreamActorState();
		static_cast<TryInitializeRequestStreamActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> && address,int loopDepth) 
	{
															#line 82 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 83 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryInitializeRequestStreamActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~TryInitializeRequestStreamActorState(); static_cast<TryInitializeRequestStreamActor*>(this)->destroy(); return 0; }
															#line 902 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryInitializeRequestStreamActor*>(this)->SAV< Void >::value()) Void(Void());
			this->~TryInitializeRequestStreamActorState();
			static_cast<TryInitializeRequestStreamActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		ASSERT(stream != nullptr);
															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		*stream = RequestStream<Req>(Endpoint::wellKnown({ address.get() }, token));
															#line 87 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TryInitializeRequestStreamActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~TryInitializeRequestStreamActorState(); static_cast<TryInitializeRequestStreamActor*>(this)->destroy(); return 0; }
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TryInitializeRequestStreamActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~TryInitializeRequestStreamActorState();
		static_cast<TryInitializeRequestStreamActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
		loopDepth = a_body1cont1(address, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> && address,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(address), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<TryInitializeRequestStreamActor*>(this)->actor_wait_state > 0) static_cast<TryInitializeRequestStreamActor*>(this)->actor_wait_state = 0;
		static_cast<TryInitializeRequestStreamActor*>(this)->ActorCallback< TryInitializeRequestStreamActor, 0, Optional<NetworkAddress> >::remove();

	}
	void a_callback_fire(ActorCallback< TryInitializeRequestStreamActor, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> const& value) 
	{
		fdb_probe_actor_enter("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryInitializeRequestStreamActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TryInitializeRequestStreamActor, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> && value) 
	{
		fdb_probe_actor_enter("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryInitializeRequestStreamActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< TryInitializeRequestStreamActor, 0, Optional<NetworkAddress> >*,Error err) 
	{
		fdb_probe_actor_enter("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TryInitializeRequestStreamActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RequestStream<Req>* stream;
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Hostname hostname;
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WellKnownEndpoints token;
															#line 1003 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via tryInitializeRequestStream()
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryInitializeRequestStreamActor final : public Actor<Void>, public ActorCallback< TryInitializeRequestStreamActor<Req>, 0, Optional<NetworkAddress> >, public FastAllocated<TryInitializeRequestStreamActor<Req>>, public TryInitializeRequestStreamActorState<Req, TryInitializeRequestStreamActor<Req>> {
															#line 1010 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<TryInitializeRequestStreamActor<Req>>::operator new;
	using FastAllocated<TryInitializeRequestStreamActor<Req>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17635227042594014720UL, 13603459720077882624UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< TryInitializeRequestStreamActor<Req>, 0, Optional<NetworkAddress> >;
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryInitializeRequestStreamActor(RequestStream<Req>* const& stream,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 1027 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   TryInitializeRequestStreamActorState<Req, TryInitializeRequestStreamActor<Req>>(stream, hostname, token),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(11987049042958738176UL, 7713147327583174656UL);
		ActorExecutionContextHelper __helper(static_cast<TryInitializeRequestStreamActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("tryInitializeRequestStream");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("tryInitializeRequestStream", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< TryInitializeRequestStreamActor<Req>, 0, Optional<NetworkAddress> >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> tryInitializeRequestStream( RequestStream<Req>* const& stream, Hostname const& hostname, WellKnownEndpoints const& token ) {
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new TryInitializeRequestStreamActor<Req>(stream, hostname, token));
															#line 1062 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 89 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 1067 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via tryGetReplyFromHostname()
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, class TryGetReplyFromHostnameActor>
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryGetReplyFromHostnameActorState {
															#line 1074 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryGetReplyFromHostnameActorState(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : request(request),
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   hostname(hostname),
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   token(token)
															#line 1085 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	~TryGetReplyFromHostnameActorState() 
	{
		fdb_probe_actor_destroy("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Optional<NetworkAddress>> __when_expr_0 = hostname.resolve();
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1102 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state = 1;
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor, 0, Optional<NetworkAddress> >*>(static_cast<TryGetReplyFromHostnameActor*>(this)));
															#line 1107 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~TryGetReplyFromHostnameActorState();
		static_cast<TryGetReplyFromHostnameActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 1130 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 97 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryGetReplyFromHostnameActor*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(ErrorOr<REPLY_TYPE(Req)>(lookup_failed())); this->~TryGetReplyFromHostnameActorState(); static_cast<TryGetReplyFromHostnameActor*>(this)->destroy(); return 0; }
															#line 1134 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryGetReplyFromHostnameActor*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(ErrorOr<REPLY_TYPE(Req)>(lookup_failed()));
			this->~TryGetReplyFromHostnameActorState();
			static_cast<TryGetReplyFromHostnameActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 99 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		RequestStream<Req> to(Endpoint::wellKnown({ address.get() }, token));
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to.tryGetReply(request);
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1146 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state = 2;
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<TryGetReplyFromHostnameActor*>(this)));
															#line 1151 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> && address,int loopDepth) 
	{
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 1160 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 97 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryGetReplyFromHostnameActor*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(ErrorOr<REPLY_TYPE(Req)>(lookup_failed())); this->~TryGetReplyFromHostnameActorState(); static_cast<TryGetReplyFromHostnameActor*>(this)->destroy(); return 0; }
															#line 1164 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryGetReplyFromHostnameActor*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(ErrorOr<REPLY_TYPE(Req)>(lookup_failed()));
			this->~TryGetReplyFromHostnameActorState();
			static_cast<TryGetReplyFromHostnameActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 99 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		RequestStream<Req> to(Endpoint::wellKnown({ address.get() }, token));
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to.tryGetReply(request);
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1176 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state = 2;
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<TryGetReplyFromHostnameActor*>(this)));
															#line 1181 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
		loopDepth = a_body1cont1(address, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> && address,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(address), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state > 0) static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state = 0;
		static_cast<TryGetReplyFromHostnameActor*>(this)->ActorCallback< TryGetReplyFromHostnameActor, 0, Optional<NetworkAddress> >::remove();

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> const& value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> && value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< TryGetReplyFromHostnameActor, 0, Optional<NetworkAddress> >*,Error err) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 101 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (reply.isError())
															#line 1265 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 102 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (reply.getError().code() == error_code_request_maybe_delivered)
															#line 1271 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				removeCachedDNS(hostname.host, hostname.service);
															#line 1275 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
		}
															#line 108 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TryGetReplyFromHostnameActor*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(reply); this->~TryGetReplyFromHostnameActorState(); static_cast<TryGetReplyFromHostnameActor*>(this)->destroy(); return 0; }
															#line 1280 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TryGetReplyFromHostnameActor*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(std::move(reply)); // state_var_RVO
		this->~TryGetReplyFromHostnameActorState();
		static_cast<TryGetReplyFromHostnameActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(ErrorOr<REPLY_TYPE(Req)> const& __reply,int loopDepth) 
	{
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reply = __reply;
															#line 1292 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(ErrorOr<REPLY_TYPE(Req)> && __reply,int loopDepth) 
	{
		reply = std::move(__reply);
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state > 0) static_cast<TryGetReplyFromHostnameActor*>(this)->actor_wait_state = 0;
		static_cast<TryGetReplyFromHostnameActor*>(this)->ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >::remove();

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> const& value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> && value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< TryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,Error err) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Hostname hostname;
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WellKnownEndpoints token;
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ErrorOr<REPLY_TYPE(Req)> reply;
															#line 1375 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via tryGetReplyFromHostname()
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryGetReplyFromHostnameActor final : public Actor<ErrorOr<REPLY_TYPE(Req)>>, public ActorCallback< TryGetReplyFromHostnameActor<Req>, 0, Optional<NetworkAddress> >, public ActorCallback< TryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >, public FastAllocated<TryGetReplyFromHostnameActor<Req>>, public TryGetReplyFromHostnameActorState<Req, TryGetReplyFromHostnameActor<Req>> {
															#line 1382 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<TryGetReplyFromHostnameActor<Req>>::operator new;
	using FastAllocated<TryGetReplyFromHostnameActor<Req>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(6148058114994026240UL, 11100571950252025600UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<ErrorOr<REPLY_TYPE(Req)>>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< TryGetReplyFromHostnameActor<Req>, 0, Optional<NetworkAddress> >;
friend struct ActorCallback< TryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >;
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryGetReplyFromHostnameActor(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 1400 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<ErrorOr<REPLY_TYPE(Req)>>(),
		   TryGetReplyFromHostnameActorState<Req, TryGetReplyFromHostnameActor<Req>>(request, hostname, token),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(15864352401317259008UL, 17495629469512462336UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("tryGetReplyFromHostname");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< TryGetReplyFromHostnameActor<Req>, 0, Optional<NetworkAddress> >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< TryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<ErrorOr<REPLY_TYPE(Req)>> tryGetReplyFromHostname( Req const& request, Hostname const& hostname, WellKnownEndpoints const& token ) {
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<ErrorOr<REPLY_TYPE(Req)>>(new TryGetReplyFromHostnameActor<Req>(request, hostname, token));
															#line 1436 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 110 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 1441 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via tryGetReplyFromHostname()
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, class TryGetReplyFromHostnameActor1>
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryGetReplyFromHostnameActor1State {
															#line 1448 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryGetReplyFromHostnameActor1State(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token,TaskPriority const& taskID) 
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : request(request),
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   hostname(hostname),
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   token(token),
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   taskID(taskID)
															#line 1461 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	~TryGetReplyFromHostnameActor1State() 
	{
		fdb_probe_actor_destroy("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Optional<NetworkAddress>> __when_expr_0 = hostname.resolve();
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1478 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 1;
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor1, 0, Optional<NetworkAddress> >*>(static_cast<TryGetReplyFromHostnameActor1*>(this)));
															#line 1483 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~TryGetReplyFromHostnameActor1State();
		static_cast<TryGetReplyFromHostnameActor1*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
															#line 120 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 1506 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 121 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(ErrorOr<REPLY_TYPE(Req)>(lookup_failed())); this->~TryGetReplyFromHostnameActor1State(); static_cast<TryGetReplyFromHostnameActor1*>(this)->destroy(); return 0; }
															#line 1510 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(ErrorOr<REPLY_TYPE(Req)>(lookup_failed()));
			this->~TryGetReplyFromHostnameActor1State();
			static_cast<TryGetReplyFromHostnameActor1*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 123 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		RequestStream<Req> to(Endpoint::wellKnown({ address.get() }, token));
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to.tryGetReply(request, taskID);
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1522 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 2;
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<TryGetReplyFromHostnameActor1*>(this)));
															#line 1527 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Optional<NetworkAddress> && address,int loopDepth) 
	{
															#line 120 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!address.present())
															#line 1536 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 121 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(ErrorOr<REPLY_TYPE(Req)>(lookup_failed())); this->~TryGetReplyFromHostnameActor1State(); static_cast<TryGetReplyFromHostnameActor1*>(this)->destroy(); return 0; }
															#line 1540 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(ErrorOr<REPLY_TYPE(Req)>(lookup_failed()));
			this->~TryGetReplyFromHostnameActor1State();
			static_cast<TryGetReplyFromHostnameActor1*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 123 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		RequestStream<Req> to(Endpoint::wellKnown({ address.get() }, token));
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to.tryGetReply(request, taskID);
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1552 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 2;
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<TryGetReplyFromHostnameActor1*>(this)));
															#line 1557 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> const& address,int loopDepth) 
	{
		loopDepth = a_body1cont1(address, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Optional<NetworkAddress> && address,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(address), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state > 0) static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 0;
		static_cast<TryGetReplyFromHostnameActor1*>(this)->ActorCallback< TryGetReplyFromHostnameActor1, 0, Optional<NetworkAddress> >::remove();

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor1, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> const& value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor1, 0, Optional<NetworkAddress> >*,Optional<NetworkAddress> && value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< TryGetReplyFromHostnameActor1, 0, Optional<NetworkAddress> >*,Error err) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 125 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (reply.isError())
															#line 1641 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 126 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (reply.getError().code() == error_code_request_maybe_delivered)
															#line 1647 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				removeCachedDNS(hostname.host, hostname.service);
															#line 1651 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
		}
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV<ErrorOr<REPLY_TYPE(Req)>>::futures) { (void)(reply); this->~TryGetReplyFromHostnameActor1State(); static_cast<TryGetReplyFromHostnameActor1*>(this)->destroy(); return 0; }
															#line 1656 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TryGetReplyFromHostnameActor1*>(this)->SAV< ErrorOr<REPLY_TYPE(Req)> >::value()) ErrorOr<REPLY_TYPE(Req)>(std::move(reply)); // state_var_RVO
		this->~TryGetReplyFromHostnameActor1State();
		static_cast<TryGetReplyFromHostnameActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(ErrorOr<REPLY_TYPE(Req)> const& __reply,int loopDepth) 
	{
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reply = __reply;
															#line 1668 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(ErrorOr<REPLY_TYPE(Req)> && __reply,int loopDepth) 
	{
		reply = std::move(__reply);
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state > 0) static_cast<TryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 0;
		static_cast<TryGetReplyFromHostnameActor1*>(this)->ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >::remove();

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> const& value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> && value) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< TryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,Error err) 
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Hostname hostname;
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WellKnownEndpoints token;
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TaskPriority taskID;
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ErrorOr<REPLY_TYPE(Req)> reply;
															#line 1753 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via tryGetReplyFromHostname()
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TryGetReplyFromHostnameActor1 final : public Actor<ErrorOr<REPLY_TYPE(Req)>>, public ActorCallback< TryGetReplyFromHostnameActor1<Req>, 0, Optional<NetworkAddress> >, public ActorCallback< TryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >, public FastAllocated<TryGetReplyFromHostnameActor1<Req>>, public TryGetReplyFromHostnameActor1State<Req, TryGetReplyFromHostnameActor1<Req>> {
															#line 1760 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<TryGetReplyFromHostnameActor1<Req>>::operator new;
	using FastAllocated<TryGetReplyFromHostnameActor1<Req>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(6148058114994026240UL, 11100571950252025600UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<ErrorOr<REPLY_TYPE(Req)>>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< TryGetReplyFromHostnameActor1<Req>, 0, Optional<NetworkAddress> >;
friend struct ActorCallback< TryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >;
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TryGetReplyFromHostnameActor1(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token,TaskPriority const& taskID) 
															#line 1778 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<ErrorOr<REPLY_TYPE(Req)>>(),
		   TryGetReplyFromHostnameActor1State<Req, TryGetReplyFromHostnameActor1<Req>>(request, hostname, token, taskID),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(7327004164435705600UL, 9362516771815281408UL);
		ActorExecutionContextHelper __helper(static_cast<TryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("tryGetReplyFromHostname");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("tryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< TryGetReplyFromHostnameActor1<Req>, 0, Optional<NetworkAddress> >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< TryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<ErrorOr<REPLY_TYPE(Req)>> tryGetReplyFromHostname( Req const& request, Hostname const& hostname, WellKnownEndpoints const& token, TaskPriority const& taskID ) {
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<ErrorOr<REPLY_TYPE(Req)>>(new TryGetReplyFromHostnameActor1<Req>(request, hostname, token, taskID));
															#line 1814 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 134 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 1819 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via retryGetReplyFromHostname()
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, class RetryGetReplyFromHostnameActor>
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryGetReplyFromHostnameActorState {
															#line 1826 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryGetReplyFromHostnameActorState(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : request(request),
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   hostname(hostname),
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   token(token),
															#line 140 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   reconnectInterval(FLOW_KNOBS->HOSTNAME_RECONNECT_INIT_INTERVAL),
															#line 141 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   to()
															#line 1841 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	~RetryGetReplyFromHostnameActorState() 
	{
		fdb_probe_actor_destroy("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 1856 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~RetryGetReplyFromHostnameActorState();
		static_cast<RetryGetReplyFromHostnameActor*>(this)->sendErrorAndDelPromiseRef(error);
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
															#line 143 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<NetworkAddress> __when_expr_0 = hostname.resolveWithRetry();
															#line 143 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1888 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 1;
															#line 143 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor, 0, NetworkAddress >*>(static_cast<RetryGetReplyFromHostnameActor*>(this)));
															#line 1893 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(NetworkAddress const& address,int loopDepth) 
	{
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (to == nullptr || to->getEndpoint().getPrimaryAddress() != address)
															#line 1902 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			to = std::make_unique<RequestStream<Req>>(Endpoint::wellKnown({ address }, token));
															#line 1906 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to->tryGetReply(request);
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1912 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 2;
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<RetryGetReplyFromHostnameActor*>(this)));
															#line 1917 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(NetworkAddress && address,int loopDepth) 
	{
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (to == nullptr || to->getEndpoint().getPrimaryAddress() != address)
															#line 1926 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			to = std::make_unique<RequestStream<Req>>(Endpoint::wellKnown({ address }, token));
															#line 1930 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to->tryGetReply(request);
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1936 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 2;
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<RetryGetReplyFromHostnameActor*>(this)));
															#line 1941 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(NetworkAddress const& address,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(address, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(NetworkAddress && address,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(std::move(address), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor*>(this)->ActorCallback< RetryGetReplyFromHostnameActor, 0, NetworkAddress >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 0, NetworkAddress >*,NetworkAddress const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 0, NetworkAddress >*,NetworkAddress && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor, 0, NetworkAddress >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont2(int loopDepth) 
	{
															#line 148 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (reply.isError())
															#line 2025 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 149 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 150 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (reply.getError().code() == error_code_request_maybe_delivered)
															#line 2031 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 152 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_2 = delay(reconnectInterval);
															#line 152 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2037 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont2when1(__when_expr_2.get(), loopDepth); };
				static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 3;
															#line 152 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor, 2, Void >*>(static_cast<RetryGetReplyFromHostnameActor*>(this)));
															#line 2042 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				loopDepth = 0;
			}
			else
			{
															#line 156 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(reply.getError(), std::max(0, loopDepth - 1));
															#line 2049 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
		}
		else
		{
															#line 159 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<RetryGetReplyFromHostnameActor*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply.get()); this->~RetryGetReplyFromHostnameActorState(); static_cast<RetryGetReplyFromHostnameActor*>(this)->destroy(); return 0; }
															#line 2056 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<RetryGetReplyFromHostnameActor*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply.get());
			this->~RetryGetReplyFromHostnameActorState();
			static_cast<RetryGetReplyFromHostnameActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(ErrorOr<REPLY_TYPE(Req)> const& __reply,int loopDepth) 
	{
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reply = __reply;
															#line 2069 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(ErrorOr<REPLY_TYPE(Req)> && __reply,int loopDepth) 
	{
		reply = std::move(__reply);
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor*>(this)->ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor, 1, ErrorOr<REPLY_TYPE(Req)> >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1loopBody1cont4(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont5(int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void const& _,int loopDepth) 
	{
															#line 153 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reconnectInterval = std::min(2 * reconnectInterval, FLOW_KNOBS->HOSTNAME_RECONNECT_MAX_INTERVAL);
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		removeCachedDNS(hostname.host, hostname.service);
															#line 2162 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void && _,int loopDepth) 
	{
															#line 153 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reconnectInterval = std::min(2 * reconnectInterval, FLOW_KNOBS->HOSTNAME_RECONNECT_MAX_INTERVAL);
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		removeCachedDNS(hostname.host, hostname.service);
															#line 2173 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont2when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont2when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor*>(this)->ActorCallback< RetryGetReplyFromHostnameActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Hostname hostname;
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WellKnownEndpoints token;
															#line 140 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	double reconnectInterval;
															#line 141 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::unique_ptr<RequestStream<Req>> to;
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ErrorOr<REPLY_TYPE(Req)> reply;
															#line 2265 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via retryGetReplyFromHostname()
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryGetReplyFromHostnameActor final : public Actor<REPLY_TYPE(Req)>, public ActorCallback< RetryGetReplyFromHostnameActor<Req>, 0, NetworkAddress >, public ActorCallback< RetryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >, public ActorCallback< RetryGetReplyFromHostnameActor<Req>, 2, Void >, public FastAllocated<RetryGetReplyFromHostnameActor<Req>>, public RetryGetReplyFromHostnameActorState<Req, RetryGetReplyFromHostnameActor<Req>> {
															#line 2272 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<RetryGetReplyFromHostnameActor<Req>>::operator new;
	using FastAllocated<RetryGetReplyFromHostnameActor<Req>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(15132832946306835712UL, 8430026994514112768UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Req)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RetryGetReplyFromHostnameActor<Req>, 0, NetworkAddress >;
friend struct ActorCallback< RetryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >;
friend struct ActorCallback< RetryGetReplyFromHostnameActor<Req>, 2, Void >;
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryGetReplyFromHostnameActor(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token) 
															#line 2291 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<REPLY_TYPE(Req)>(),
		   RetryGetReplyFromHostnameActorState<Req, RetryGetReplyFromHostnameActor<Req>>(request, hostname, token),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(8105731838203262464UL, 6747209311745633280UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("retryGetReplyFromHostname");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor<Req>, 0, NetworkAddress >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor<Req>, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Req)> retryGetReplyFromHostname( Req const& request, Hostname const& hostname, WellKnownEndpoints const& token ) {
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<REPLY_TYPE(Req)>(new RetryGetReplyFromHostnameActor<Req>(request, hostname, token));
															#line 2328 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 163 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 2333 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via retryGetReplyFromHostname()
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req, class RetryGetReplyFromHostnameActor1>
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryGetReplyFromHostnameActor1State {
															#line 2340 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryGetReplyFromHostnameActor1State(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token,TaskPriority const& taskID) 
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : request(request),
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   hostname(hostname),
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   token(token),
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   taskID(taskID),
															#line 172 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   reconnectInitInterval(FLOW_KNOBS->HOSTNAME_RECONNECT_INIT_INTERVAL),
															#line 173 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   to()
															#line 2357 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	~RetryGetReplyFromHostnameActor1State() 
	{
		fdb_probe_actor_destroy("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 174 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 2372 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~RetryGetReplyFromHostnameActor1State();
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->sendErrorAndDelPromiseRef(error);
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
															#line 175 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<NetworkAddress> __when_expr_0 = hostname.resolveWithRetry();
															#line 175 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2404 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 1;
															#line 175 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor1, 0, NetworkAddress >*>(static_cast<RetryGetReplyFromHostnameActor1*>(this)));
															#line 2409 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(NetworkAddress const& address,int loopDepth) 
	{
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (to == nullptr || to->getEndpoint().getPrimaryAddress() != address)
															#line 2418 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 177 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			to = std::make_unique<RequestStream<Req>>(Endpoint::wellKnown({ address }, token));
															#line 2422 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to->tryGetReply(request, taskID);
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2428 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 2;
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<RetryGetReplyFromHostnameActor1*>(this)));
															#line 2433 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(NetworkAddress && address,int loopDepth) 
	{
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (to == nullptr || to->getEndpoint().getPrimaryAddress() != address)
															#line 2442 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 177 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			to = std::make_unique<RequestStream<Req>>(Endpoint::wellKnown({ address }, token));
															#line 2446 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Req)>> __when_expr_1 = to->tryGetReply(request, taskID);
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2452 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 2;
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*>(static_cast<RetryGetReplyFromHostnameActor1*>(this)));
															#line 2457 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(NetworkAddress const& address,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(address, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(NetworkAddress && address,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(std::move(address), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->ActorCallback< RetryGetReplyFromHostnameActor1, 0, NetworkAddress >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 0, NetworkAddress >*,NetworkAddress const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 0, NetworkAddress >*,NetworkAddress && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor1, 0, NetworkAddress >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont2(int loopDepth) 
	{
															#line 180 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (reply.isError())
															#line 2541 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 181 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			resetReply(request);
															#line 182 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (reply.getError().code() == error_code_request_maybe_delivered)
															#line 2547 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_2 = delay(reconnectInitInterval);
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2553 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont2when1(__when_expr_2.get(), loopDepth); };
				static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 3;
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< RetryGetReplyFromHostnameActor1, 2, Void >*>(static_cast<RetryGetReplyFromHostnameActor1*>(this)));
															#line 2558 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				loopDepth = 0;
			}
			else
			{
															#line 189 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(reply.getError(), std::max(0, loopDepth - 1));
															#line 2565 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
		}
		else
		{
															#line 192 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!static_cast<RetryGetReplyFromHostnameActor1*>(this)->SAV<REPLY_TYPE(Req)>::futures) { (void)(reply.get()); this->~RetryGetReplyFromHostnameActor1State(); static_cast<RetryGetReplyFromHostnameActor1*>(this)->destroy(); return 0; }
															#line 2572 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			new (&static_cast<RetryGetReplyFromHostnameActor1*>(this)->SAV< REPLY_TYPE(Req) >::value()) REPLY_TYPE(Req)(reply.get());
			this->~RetryGetReplyFromHostnameActor1State();
			static_cast<RetryGetReplyFromHostnameActor1*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(ErrorOr<REPLY_TYPE(Req)> const& __reply,int loopDepth) 
	{
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reply = __reply;
															#line 2585 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(ErrorOr<REPLY_TYPE(Req)> && __reply,int loopDepth) 
	{
		reply = std::move(__reply);
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,ErrorOr<REPLY_TYPE(Req)> && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor1, 1, ErrorOr<REPLY_TYPE(Req)> >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1loopBody1cont4(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont5(int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void const& _,int loopDepth) 
	{
															#line 185 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reconnectInitInterval = std::min(2 * reconnectInitInterval, FLOW_KNOBS->HOSTNAME_RECONNECT_MAX_INTERVAL);
															#line 187 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		removeCachedDNS(hostname.host, hostname.service);
															#line 2678 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont6(Void && _,int loopDepth) 
	{
															#line 185 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		reconnectInitInterval = std::min(2 * reconnectInitInterval, FLOW_KNOBS->HOSTNAME_RECONNECT_MAX_INTERVAL);
															#line 187 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		removeCachedDNS(hostname.host, hostname.service);
															#line 2689 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont2when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont2when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont6(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state > 0) static_cast<RetryGetReplyFromHostnameActor1*>(this)->actor_wait_state = 0;
		static_cast<RetryGetReplyFromHostnameActor1*>(this)->ActorCallback< RetryGetReplyFromHostnameActor1, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< RetryGetReplyFromHostnameActor1, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< RetryGetReplyFromHostnameActor1, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Req request;
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Hostname hostname;
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WellKnownEndpoints token;
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TaskPriority taskID;
															#line 172 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	double reconnectInitInterval;
															#line 173 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::unique_ptr<RequestStream<Req>> to;
															#line 179 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ErrorOr<REPLY_TYPE(Req)> reply;
															#line 2783 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via retryGetReplyFromHostname()
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class RetryGetReplyFromHostnameActor1 final : public Actor<REPLY_TYPE(Req)>, public ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 0, NetworkAddress >, public ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >, public ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 2, Void >, public FastAllocated<RetryGetReplyFromHostnameActor1<Req>>, public RetryGetReplyFromHostnameActor1State<Req, RetryGetReplyFromHostnameActor1<Req>> {
															#line 2790 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<RetryGetReplyFromHostnameActor1<Req>>::operator new;
	using FastAllocated<RetryGetReplyFromHostnameActor1<Req>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(15132832946306835712UL, 8430026994514112768UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Req)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 0, NetworkAddress >;
friend struct ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >;
friend struct ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 2, Void >;
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	RetryGetReplyFromHostnameActor1(Req const& request,Hostname const& hostname,WellKnownEndpoints const& token,TaskPriority const& taskID) 
															#line 2809 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<REPLY_TYPE(Req)>(),
		   RetryGetReplyFromHostnameActor1State<Req, RetryGetReplyFromHostnameActor1<Req>>(request, hostname, token, taskID),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(17472137469036657408UL, 14566631732372783360UL);
		ActorExecutionContextHelper __helper(static_cast<RetryGetReplyFromHostnameActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("retryGetReplyFromHostname");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("retryGetReplyFromHostname", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 0, NetworkAddress >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 1, ErrorOr<REPLY_TYPE(Req)> >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< RetryGetReplyFromHostnameActor1<Req>, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class Req>
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Req)> retryGetReplyFromHostname( Req const& request, Hostname const& hostname, WellKnownEndpoints const& token, TaskPriority const& taskID ) {
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<REPLY_TYPE(Req)>(new RetryGetReplyFromHostnameActor1<Req>(request, hostname, token, taskID));
															#line 2846 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 196 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 2851 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via timeoutWarning()
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class TimeoutWarningActor>
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TimeoutWarningActorState {
															#line 2858 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TimeoutWarningActorState(Future<T> const& what,double const& time,PromiseStream<Void> const& output) 
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : what(what),
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   time(time),
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output),
															#line 199 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   end(delay(time))
															#line 2871 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("timeoutWarning", reinterpret_cast<unsigned long>(this));

	}
	~TimeoutWarningActorState() 
	{
		fdb_probe_actor_destroy("timeoutWarning", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 200 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 2886 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~TimeoutWarningActorState();
		static_cast<TimeoutWarningActor*>(this)->sendErrorAndDelPromiseRef(error);
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
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<T> __when_expr_0 = what;
															#line 200 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<TimeoutWarningActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2918 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
															#line 204 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<Void> __when_expr_1 = end;
															#line 2922 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when2(__when_expr_1.get(), loopDepth); };
		static_cast<TimeoutWarningActor*>(this)->actor_wait_state = 1;
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< TimeoutWarningActor, 0, T >*>(static_cast<TimeoutWarningActor*>(this)));
															#line 204 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TimeoutWarningActor, 1, Void >*>(static_cast<TimeoutWarningActor*>(this)));
															#line 2929 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1when1(T const& t,int loopDepth) 
	{
															#line 202 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TimeoutWarningActor*>(this)->SAV<T>::futures) { (void)(t); this->~TimeoutWarningActorState(); static_cast<TimeoutWarningActor*>(this)->destroy(); return 0; }
															#line 2944 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TimeoutWarningActor*>(this)->SAV< T >::value()) T(t);
		this->~TimeoutWarningActorState();
		static_cast<TimeoutWarningActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(T && t,int loopDepth) 
	{
															#line 202 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<TimeoutWarningActor*>(this)->SAV<T>::futures) { (void)(t); this->~TimeoutWarningActorState(); static_cast<TimeoutWarningActor*>(this)->destroy(); return 0; }
															#line 2956 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<TimeoutWarningActor*>(this)->SAV< T >::value()) T(t);
		this->~TimeoutWarningActorState();
		static_cast<TimeoutWarningActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when2(Void const& _,int loopDepth) 
	{
															#line 205 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(Void());
															#line 206 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		end = delay(time);
															#line 2970 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void && _,int loopDepth) 
	{
															#line 205 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(Void());
															#line 206 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		end = delay(time);
															#line 2981 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<TimeoutWarningActor*>(this)->actor_wait_state > 0) static_cast<TimeoutWarningActor*>(this)->actor_wait_state = 0;
		static_cast<TimeoutWarningActor*>(this)->ActorCallback< TimeoutWarningActor, 0, T >::remove();
		static_cast<TimeoutWarningActor*>(this)->ActorCallback< TimeoutWarningActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< TimeoutWarningActor, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TimeoutWarningActor, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< TimeoutWarningActor, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TimeoutWarningActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< TimeoutWarningActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< TimeoutWarningActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> what;
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	double time;
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	PromiseStream<Void> output;
															#line 199 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<Void> end;
															#line 3115 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via timeoutWarning()
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class TimeoutWarningActor final : public Actor<T>, public ActorCallback< TimeoutWarningActor<T>, 0, T >, public ActorCallback< TimeoutWarningActor<T>, 1, Void >, public FastAllocated<TimeoutWarningActor<T>>, public TimeoutWarningActorState<T, TimeoutWarningActor<T>> {
															#line 3122 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<TimeoutWarningActor<T>>::operator new;
	using FastAllocated<TimeoutWarningActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(15914535601622732800UL, 4994816230682106368UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<T>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< TimeoutWarningActor<T>, 0, T >;
friend struct ActorCallback< TimeoutWarningActor<T>, 1, Void >;
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	TimeoutWarningActor(Future<T> const& what,double const& time,PromiseStream<Void> const& output) 
															#line 3140 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<T>(),
		   TimeoutWarningActorState<T, TimeoutWarningActor<T>>(what, time, output),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("timeoutWarning", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(15138501800934750976UL, 17855053322769819392UL);
		ActorExecutionContextHelper __helper(static_cast<TimeoutWarningActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("timeoutWarning");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("timeoutWarning", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< TimeoutWarningActor<T>, 0, T >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<T> timeoutWarning( Future<T> const& what, double const& time, PromiseStream<Void> const& output ) {
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<T>(new TimeoutWarningActor<T>(what, time, output));
															#line 3175 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 210 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 3180 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via forwardPromise()
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class ForwardPromiseActor>
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActorState {
															#line 3187 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActorState(Promise<T> const& output,Future<T> const& input) 
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : output(output),
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   input(input)
															#line 3196 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	~ForwardPromiseActorState() 
	{
		fdb_probe_actor_destroy("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 214 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<T> __when_expr_0 = input;
															#line 214 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 3214 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				static_cast<ForwardPromiseActor*>(this)->actor_wait_state = 1;
															#line 214 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ForwardPromiseActor, 0, T >*>(static_cast<ForwardPromiseActor*>(this)));
															#line 3218 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		delete static_cast<ForwardPromiseActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		loopDepth = a_body1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2(const Error& err,int loopDepth=0) 
	{
		try {
															#line 217 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output.sendError(err);
															#line 3253 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(T const& value,int loopDepth) 
	{
															#line 215 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3268 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(T && value,int loopDepth) 
	{
															#line 215 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3277 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& value,int loopDepth) 
	{
		loopDepth = a_body1cont2(value, loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && value,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(value), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ForwardPromiseActor*>(this)->actor_wait_state > 0) static_cast<ForwardPromiseActor*>(this)->actor_wait_state = 0;
		static_cast<ForwardPromiseActor*>(this)->ActorCallback< ForwardPromiseActor, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ForwardPromiseActor, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont5(int loopDepth) 
	{
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		delete static_cast<ForwardPromiseActor*>(this);
															#line 3374 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Promise<T> output;
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 3383 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via forwardPromise()
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActor final : public Actor<void>, public ActorCallback< ForwardPromiseActor<T>, 0, T >, public FastAllocated<ForwardPromiseActor<T>>, public ForwardPromiseActorState<T, ForwardPromiseActor<T>> {
															#line 3390 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<ForwardPromiseActor<T>>::operator new;
	using FastAllocated<ForwardPromiseActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12919583154996586240UL, 776859750784572928UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< ForwardPromiseActor<T>, 0, T >;
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActor(Promise<T> const& output,Future<T> const& input) 
															#line 3407 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<void>(),
		   ForwardPromiseActorState<T, ForwardPromiseActor<T>>(output, input),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(7843831184336454144UL, 11100125588628783360UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("forwardPromise");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), -1);

	}
};
} // namespace
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
void forwardPromise( Promise<T> const& output, Future<T> const& input ) {
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	new ForwardPromiseActor<T>(output, input);
															#line 3433 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 220 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 3438 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via forwardPromise()
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class ForwardPromiseActor1>
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActor1State {
															#line 3445 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActor1State(ReplyPromise<T> const& output,Future<T> const& input) 
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : output(output),
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   input(input)
															#line 3454 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	~ForwardPromiseActor1State() 
	{
		fdb_probe_actor_destroy("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 224 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<T> __when_expr_0 = input;
															#line 224 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 3472 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				static_cast<ForwardPromiseActor1*>(this)->actor_wait_state = 1;
															#line 224 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ForwardPromiseActor1, 0, T >*>(static_cast<ForwardPromiseActor1*>(this)));
															#line 3476 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		delete static_cast<ForwardPromiseActor1*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		loopDepth = a_body1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2(const Error& err,int loopDepth=0) 
	{
		try {
															#line 227 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output.sendError(err);
															#line 3511 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(T const& value,int loopDepth) 
	{
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3526 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(T && value,int loopDepth) 
	{
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3535 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& value,int loopDepth) 
	{
		loopDepth = a_body1cont2(value, loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && value,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(value), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ForwardPromiseActor1*>(this)->actor_wait_state > 0) static_cast<ForwardPromiseActor1*>(this)->actor_wait_state = 0;
		static_cast<ForwardPromiseActor1*>(this)->ActorCallback< ForwardPromiseActor1, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor1, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor1, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ForwardPromiseActor1, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont5(int loopDepth) 
	{
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		delete static_cast<ForwardPromiseActor1*>(this);
															#line 3632 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReplyPromise<T> output;
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 3641 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via forwardPromise()
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActor1 final : public Actor<void>, public ActorCallback< ForwardPromiseActor1<T>, 0, T >, public FastAllocated<ForwardPromiseActor1<T>>, public ForwardPromiseActor1State<T, ForwardPromiseActor1<T>> {
															#line 3648 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<ForwardPromiseActor1<T>>::operator new;
	using FastAllocated<ForwardPromiseActor1<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12919583154996586240UL, 776859750784572928UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< ForwardPromiseActor1<T>, 0, T >;
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActor1(ReplyPromise<T> const& output,Future<T> const& input) 
															#line 3665 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<void>(),
		   ForwardPromiseActor1State<T, ForwardPromiseActor1<T>>(output, input),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(2116168105338813184UL, 9531603158096391936UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("forwardPromise");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), -1);

	}
};
} // namespace
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
void forwardPromise( ReplyPromise<T> const& output, Future<T> const& input ) {
															#line 221 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	new ForwardPromiseActor1<T>(output, input);
															#line 3691 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 230 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 3696 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via forwardPromise()
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class ForwardPromiseActor2>
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActor2State {
															#line 3703 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActor2State(PromiseStream<T> const& output,Future<T> const& input) 
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : output(output),
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   input(input)
															#line 3712 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	~ForwardPromiseActor2State() 
	{
		fdb_probe_actor_destroy("forwardPromise", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 234 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<T> __when_expr_0 = input;
															#line 234 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 3730 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				static_cast<ForwardPromiseActor2*>(this)->actor_wait_state = 1;
															#line 234 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ForwardPromiseActor2, 0, T >*>(static_cast<ForwardPromiseActor2*>(this)));
															#line 3734 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		delete static_cast<ForwardPromiseActor2*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		loopDepth = a_body1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 237 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output.sendError(e);
															#line 3769 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = a_body1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(T const& value,int loopDepth) 
	{
															#line 235 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3784 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(T && value,int loopDepth) 
	{
															#line 235 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output.send(value);
															#line 3793 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& value,int loopDepth) 
	{
		loopDepth = a_body1cont2(value, loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && value,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(value), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ForwardPromiseActor2*>(this)->actor_wait_state > 0) static_cast<ForwardPromiseActor2*>(this)->actor_wait_state = 0;
		static_cast<ForwardPromiseActor2*>(this)->ActorCallback< ForwardPromiseActor2, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor2, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor2*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ForwardPromiseActor2, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor2*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ForwardPromiseActor2, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor2*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont5(int loopDepth) 
	{
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		delete static_cast<ForwardPromiseActor2*>(this);
															#line 3890 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	PromiseStream<T> output;
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 3899 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via forwardPromise()
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ForwardPromiseActor2 final : public Actor<void>, public ActorCallback< ForwardPromiseActor2<T>, 0, T >, public FastAllocated<ForwardPromiseActor2<T>>, public ForwardPromiseActor2State<T, ForwardPromiseActor2<T>> {
															#line 3906 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<ForwardPromiseActor2<T>>::operator new;
	using FastAllocated<ForwardPromiseActor2<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12919583154996586240UL, 776859750784572928UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< ForwardPromiseActor2<T>, 0, T >;
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ForwardPromiseActor2(PromiseStream<T> const& output,Future<T> const& input) 
															#line 3923 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<void>(),
		   ForwardPromiseActor2State<T, ForwardPromiseActor2<T>>(output, input),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("forwardPromise", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(2946058180034076160UL, 9151250485096794880UL);
		ActorExecutionContextHelper __helper(static_cast<ForwardPromiseActor2*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("forwardPromise");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("forwardPromise", reinterpret_cast<unsigned long>(this), -1);

	}
};
} // namespace
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
void forwardPromise( PromiseStream<T> const& output, Future<T> const& input ) {
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	new ForwardPromiseActor2<T>(output, input);
															#line 3949 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 240 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 3954 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via broadcast()
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class BroadcastActor>
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class BroadcastActorState {
															#line 3961 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	BroadcastActorState(Future<T> const& input,std::vector<Promise<T>> const& output) 
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : input(input),
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output)
															#line 3970 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("broadcast", reinterpret_cast<unsigned long>(this));

	}
	~BroadcastActorState() 
	{
		fdb_probe_actor_destroy("broadcast", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 243 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<T> __when_expr_0 = input;
															#line 243 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<BroadcastActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 3987 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<BroadcastActor*>(this)->actor_wait_state = 1;
															#line 243 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< BroadcastActor, 0, T >*>(static_cast<BroadcastActor*>(this)));
															#line 3992 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~BroadcastActorState();
		static_cast<BroadcastActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(T const& value,int loopDepth) 
	{
															#line 244 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		for(int i = 0;i < output.size();i++) {
															#line 245 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output[i].send(value);
															#line 4017 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 246 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<BroadcastActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~BroadcastActorState(); static_cast<BroadcastActor*>(this)->destroy(); return 0; }
															#line 4021 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<BroadcastActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~BroadcastActorState();
		static_cast<BroadcastActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1(T && value,int loopDepth) 
	{
															#line 244 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		for(int i = 0;i < output.size();i++) {
															#line 245 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output[i].send(value);
															#line 4035 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 246 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<BroadcastActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~BroadcastActorState(); static_cast<BroadcastActor*>(this)->destroy(); return 0; }
															#line 4039 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<BroadcastActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~BroadcastActorState();
		static_cast<BroadcastActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1when1(T const& value,int loopDepth) 
	{
		loopDepth = a_body1cont1(value, loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && value,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(value), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<BroadcastActor*>(this)->actor_wait_state > 0) static_cast<BroadcastActor*>(this)->actor_wait_state = 0;
		static_cast<BroadcastActor*>(this)->ActorCallback< BroadcastActor, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< BroadcastActor, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< BroadcastActor, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< BroadcastActor, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::vector<Promise<T>> output;
															#line 4126 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via broadcast()
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class BroadcastActor final : public Actor<Void>, public ActorCallback< BroadcastActor<T>, 0, T >, public FastAllocated<BroadcastActor<T>>, public BroadcastActorState<T, BroadcastActor<T>> {
															#line 4133 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<BroadcastActor<T>>::operator new;
	using FastAllocated<BroadcastActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(859278153549127424UL, 5228739611524632320UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< BroadcastActor<T>, 0, T >;
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	BroadcastActor(Future<T> const& input,std::vector<Promise<T>> const& output) 
															#line 4150 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   BroadcastActorState<T, BroadcastActor<T>>(input, output),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(10055547700014470400UL, 5083019977608030976UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("broadcast");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< BroadcastActor<T>, 0, T >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> broadcast( Future<T> const& input, std::vector<Promise<T>> const& output ) {
															#line 241 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new BroadcastActor<T>(input, output));
															#line 4185 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 248 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 4190 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via broadcast()
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class BroadcastActor1>
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class BroadcastActor1State {
															#line 4197 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	BroadcastActor1State(Future<T> const& input,std::vector<ReplyPromise<T>> const& output) 
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : input(input),
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output)
															#line 4206 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("broadcast", reinterpret_cast<unsigned long>(this));

	}
	~BroadcastActor1State() 
	{
		fdb_probe_actor_destroy("broadcast", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 251 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<T> __when_expr_0 = input;
															#line 251 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<BroadcastActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4223 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<BroadcastActor1*>(this)->actor_wait_state = 1;
															#line 251 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< BroadcastActor1, 0, T >*>(static_cast<BroadcastActor1*>(this)));
															#line 4228 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~BroadcastActor1State();
		static_cast<BroadcastActor1*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(T const& value,int loopDepth) 
	{
															#line 252 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		for(int i = 0;i < output.size();i++) {
															#line 253 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output[i].send(value);
															#line 4253 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 254 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<BroadcastActor1*>(this)->SAV<Void>::futures) { (void)(Void()); this->~BroadcastActor1State(); static_cast<BroadcastActor1*>(this)->destroy(); return 0; }
															#line 4257 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<BroadcastActor1*>(this)->SAV< Void >::value()) Void(Void());
		this->~BroadcastActor1State();
		static_cast<BroadcastActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1(T && value,int loopDepth) 
	{
															#line 252 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		for(int i = 0;i < output.size();i++) {
															#line 253 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			output[i].send(value);
															#line 4271 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
															#line 254 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<BroadcastActor1*>(this)->SAV<Void>::futures) { (void)(Void()); this->~BroadcastActor1State(); static_cast<BroadcastActor1*>(this)->destroy(); return 0; }
															#line 4275 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<BroadcastActor1*>(this)->SAV< Void >::value()) Void(Void());
		this->~BroadcastActor1State();
		static_cast<BroadcastActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1when1(T const& value,int loopDepth) 
	{
		loopDepth = a_body1cont1(value, loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && value,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(value), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<BroadcastActor1*>(this)->actor_wait_state > 0) static_cast<BroadcastActor1*>(this)->actor_wait_state = 0;
		static_cast<BroadcastActor1*>(this)->ActorCallback< BroadcastActor1, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< BroadcastActor1, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< BroadcastActor1, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< BroadcastActor1, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::vector<ReplyPromise<T>> output;
															#line 4362 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via broadcast()
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class BroadcastActor1 final : public Actor<Void>, public ActorCallback< BroadcastActor1<T>, 0, T >, public FastAllocated<BroadcastActor1<T>>, public BroadcastActor1State<T, BroadcastActor1<T>> {
															#line 4369 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<BroadcastActor1<T>>::operator new;
	using FastAllocated<BroadcastActor1<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(859278153549127424UL, 5228739611524632320UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< BroadcastActor1<T>, 0, T >;
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	BroadcastActor1(Future<T> const& input,std::vector<ReplyPromise<T>> const& output) 
															#line 4386 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   BroadcastActor1State<T, BroadcastActor1<T>>(input, output),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("broadcast", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(6044184165491527168UL, 6125521375055677184UL);
		ActorExecutionContextHelper __helper(static_cast<BroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("broadcast");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("broadcast", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< BroadcastActor1<T>, 0, T >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> broadcast( Future<T> const& input, std::vector<ReplyPromise<T>> const& output ) {
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new BroadcastActor1<T>(input, output));
															#line 4421 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 256 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 4426 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via incrementalBroadcast()
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class IncrementalBroadcastActor>
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastActorState {
															#line 4433 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastActorState(Future<T> const& input,std::vector<Promise<T>> const& output,int const& batchSize) 
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : input(input),
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output),
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   batchSize(batchSize)
															#line 4444 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("incrementalBroadcast", reinterpret_cast<unsigned long>(this));

	}
	~IncrementalBroadcastActorState() 
	{
		fdb_probe_actor_destroy("incrementalBroadcast", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<T> __when_expr_0 = input;
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4461 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state = 1;
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastActor, 0, T >*>(static_cast<IncrementalBroadcastActor*>(this)));
															#line 4466 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~IncrementalBroadcastActorState();
		static_cast<IncrementalBroadcastActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 260 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i = 0;
															#line 261 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		;
															#line 4491 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont1loopHead1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& __value,int loopDepth) 
	{
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		value = __value;
															#line 4500 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && __value,int loopDepth) 
	{
		value = std::move(__value);
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastActor*>(this)->ActorCallback< IncrementalBroadcastActor, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastActor, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 267 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<IncrementalBroadcastActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~IncrementalBroadcastActorState(); static_cast<IncrementalBroadcastActor*>(this)->destroy(); return 0; }
															#line 4579 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<IncrementalBroadcastActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~IncrementalBroadcastActorState();
		static_cast<IncrementalBroadcastActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1cont1loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1(int loopDepth) 
	{
															#line 261 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!(i < output.size()))
															#line 4598 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
			return a_body1cont1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 262 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output[i].send(value);
															#line 263 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if ((i + 1) % batchSize == 0)
															#line 4606 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 264 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = delay(0);
															#line 264 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 4612 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1cont1loopBody1when1(__when_expr_1.get(), loopDepth); };
			static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state = 2;
															#line 264 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastActor, 1, Void >*>(static_cast<IncrementalBroadcastActor*>(this)));
															#line 4617 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		else
		{
			loopDepth = a_body1cont1loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont1break1(int loopDepth) 
	{
		try {
			return a_body1cont2(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont1loopBody1cont1(int loopDepth) 
	{
															#line 261 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i++;
															#line 4644 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (loopDepth == 0) return a_body1cont1loopHead1(0);

		return loopDepth;
	}
	int a_body1cont1loopBody1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastActor*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastActor*>(this)->ActorCallback< IncrementalBroadcastActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::vector<Promise<T>> output;
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int batchSize;
															#line 259 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	T value;
															#line 260 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int i;
															#line 4746 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via incrementalBroadcast()
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastActor final : public Actor<Void>, public ActorCallback< IncrementalBroadcastActor<T>, 0, T >, public ActorCallback< IncrementalBroadcastActor<T>, 1, Void >, public FastAllocated<IncrementalBroadcastActor<T>>, public IncrementalBroadcastActorState<T, IncrementalBroadcastActor<T>> {
															#line 4753 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<IncrementalBroadcastActor<T>>::operator new;
	using FastAllocated<IncrementalBroadcastActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12096545462705738752UL, 12135200417365164288UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< IncrementalBroadcastActor<T>, 0, T >;
friend struct ActorCallback< IncrementalBroadcastActor<T>, 1, Void >;
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastActor(Future<T> const& input,std::vector<Promise<T>> const& output,int const& batchSize) 
															#line 4771 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   IncrementalBroadcastActorState<T, IncrementalBroadcastActor<T>>(input, output, batchSize),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(4812002838856963328UL, 13434094745575330304UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("incrementalBroadcast");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< IncrementalBroadcastActor<T>, 0, T >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< IncrementalBroadcastActor<T>, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> incrementalBroadcast( Future<T> const& input, std::vector<Promise<T>> const& output, int const& batchSize ) {
															#line 257 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new IncrementalBroadcastActor<T>(input, output, batchSize));
															#line 4807 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 269 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 4812 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via incrementalBroadcast()
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class IncrementalBroadcastActor1>
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastActor1State {
															#line 4819 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastActor1State(Future<T> const& input,std::vector<ReplyPromise<T>> const& output,int const& batchSize) 
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : input(input),
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output),
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   batchSize(batchSize)
															#line 4830 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("incrementalBroadcast", reinterpret_cast<unsigned long>(this));

	}
	~IncrementalBroadcastActor1State() 
	{
		fdb_probe_actor_destroy("incrementalBroadcast", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<T> __when_expr_0 = input;
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4847 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state = 1;
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastActor1, 0, T >*>(static_cast<IncrementalBroadcastActor1*>(this)));
															#line 4852 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
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
		this->~IncrementalBroadcastActor1State();
		static_cast<IncrementalBroadcastActor1*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 273 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i = 0;
															#line 274 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		;
															#line 4877 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont1loopHead1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& __value,int loopDepth) 
	{
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		value = __value;
															#line 4886 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && __value,int loopDepth) 
	{
		value = std::move(__value);
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastActor1*>(this)->ActorCallback< IncrementalBroadcastActor1, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor1, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor1, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastActor1, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 280 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<IncrementalBroadcastActor1*>(this)->SAV<Void>::futures) { (void)(Void()); this->~IncrementalBroadcastActor1State(); static_cast<IncrementalBroadcastActor1*>(this)->destroy(); return 0; }
															#line 4965 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<IncrementalBroadcastActor1*>(this)->SAV< Void >::value()) Void(Void());
		this->~IncrementalBroadcastActor1State();
		static_cast<IncrementalBroadcastActor1*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1cont1loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1(int loopDepth) 
	{
															#line 274 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!(i < output.size()))
															#line 4984 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
			return a_body1cont1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 275 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output[i].send(value);
															#line 276 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if ((i + 1) % batchSize == 0)
															#line 4992 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 277 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = delay(0);
															#line 277 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 4998 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1cont1loopBody1when1(__when_expr_1.get(), loopDepth); };
			static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state = 2;
															#line 277 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastActor1, 1, Void >*>(static_cast<IncrementalBroadcastActor1*>(this)));
															#line 5003 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		else
		{
			loopDepth = a_body1cont1loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont1break1(int loopDepth) 
	{
		try {
			return a_body1cont2(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont1loopBody1cont1(int loopDepth) 
	{
															#line 274 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i++;
															#line 5030 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (loopDepth == 0) return a_body1cont1loopHead1(0);

		return loopDepth;
	}
	int a_body1cont1loopBody1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastActor1*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastActor1*>(this)->ActorCallback< IncrementalBroadcastActor1, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor1, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastActor1, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastActor1, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::vector<ReplyPromise<T>> output;
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int batchSize;
															#line 272 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	T value;
															#line 273 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int i;
															#line 5132 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via incrementalBroadcast()
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastActor1 final : public Actor<Void>, public ActorCallback< IncrementalBroadcastActor1<T>, 0, T >, public ActorCallback< IncrementalBroadcastActor1<T>, 1, Void >, public FastAllocated<IncrementalBroadcastActor1<T>>, public IncrementalBroadcastActor1State<T, IncrementalBroadcastActor1<T>> {
															#line 5139 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<IncrementalBroadcastActor1<T>>::operator new;
	using FastAllocated<IncrementalBroadcastActor1<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12096545462705738752UL, 12135200417365164288UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< IncrementalBroadcastActor1<T>, 0, T >;
friend struct ActorCallback< IncrementalBroadcastActor1<T>, 1, Void >;
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastActor1(Future<T> const& input,std::vector<ReplyPromise<T>> const& output,int const& batchSize) 
															#line 5157 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   IncrementalBroadcastActor1State<T, IncrementalBroadcastActor1<T>>(input, output, batchSize),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("incrementalBroadcast", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(4281544153242063104UL, 8050982773658596352UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastActor1*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("incrementalBroadcast");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("incrementalBroadcast", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< IncrementalBroadcastActor1<T>, 0, T >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< IncrementalBroadcastActor1<T>, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> incrementalBroadcast( Future<T> const& input, std::vector<ReplyPromise<T>> const& output, int const& batchSize ) {
															#line 270 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new IncrementalBroadcastActor1<T>(input, output, batchSize));
															#line 5193 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 282 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 5198 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via incrementalBroadcastWithError()
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class IncrementalBroadcastWithErrorActor>
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastWithErrorActorState {
															#line 5205 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastWithErrorActorState(Future<T> const& input,std::vector<Promise<T>> const& output,int const& batchSize) 
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : input(input),
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   output(output),
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   batchSize(batchSize),
															#line 285 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   i(0)
															#line 5218 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this));

	}
	~IncrementalBroadcastWithErrorActorState() 
	{
		fdb_probe_actor_destroy("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 287 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<T> __when_expr_0 = input;
															#line 287 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 5236 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 1;
															#line 287 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastWithErrorActor, 0, T >*>(static_cast<IncrementalBroadcastWithErrorActor*>(this)));
															#line 5241 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~IncrementalBroadcastWithErrorActorState();
		static_cast<IncrementalBroadcastWithErrorActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 306 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<IncrementalBroadcastWithErrorActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~IncrementalBroadcastWithErrorActorState(); static_cast<IncrementalBroadcastWithErrorActor*>(this)->destroy(); return 0; }
															#line 5270 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<IncrementalBroadcastWithErrorActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~IncrementalBroadcastWithErrorActorState();
		static_cast<IncrementalBroadcastWithErrorActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& _e,int loopDepth=0) 
	{
		try {
															#line 295 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (_e.code() == error_code_operation_cancelled)
															#line 5283 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 296 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(_e, loopDepth);
															#line 5287 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 298 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			e = _e;
															#line 299 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 5293 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = a_body1Catch2loopHead1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(int loopDepth) 
	{
															#line 288 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		;
															#line 5308 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2loopHead1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T const& __value,int loopDepth) 
	{
															#line 287 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		value = __value;
															#line 5317 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when1(T && __value,int loopDepth) 
	{
		value = std::move(__value);
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastWithErrorActor*>(this)->ActorCallback< IncrementalBroadcastWithErrorActor, 0, T >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 0, T >*,T const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 0, T >*,T && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastWithErrorActor, 0, T >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont3(int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont2loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1cont2loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1cont2loopBody1(int loopDepth) 
	{
															#line 288 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!(i < output.size()))
															#line 5409 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
			return a_body1cont2break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 289 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output[i].send(value);
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if ((i + 1) % batchSize == 0)
															#line 5417 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = delay(0);
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 5423 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch2(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1cont2loopBody1when1(__when_expr_1.get(), loopDepth); };
			static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 2;
															#line 291 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastWithErrorActor, 1, Void >*>(static_cast<IncrementalBroadcastWithErrorActor*>(this)));
															#line 5428 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		else
		{
			loopDepth = a_body1cont2loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2break1(int loopDepth) 
	{
		try {
			return a_body1cont3(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch2(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch2(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2loopBody1cont1(int loopDepth) 
	{
															#line 288 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i++;
															#line 5455 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (loopDepth == 0) return a_body1cont2loopHead1(0);

		return loopDepth;
	}
	int a_body1cont2loopBody1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont2loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont2loopBody1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont2loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont2loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont2loopBody1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont2loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont2loopBody1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastWithErrorActor*>(this)->ActorCallback< IncrementalBroadcastWithErrorActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont2loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont2loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastWithErrorActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 1);

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
	int a_body1Catch2cont1(int loopDepth) 
	{
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1Catch2loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2loopBody1(int loopDepth) 
	{
															#line 299 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!(i < output.size()))
															#line 5577 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
			return a_body1Catch2break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 300 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		output[i].sendError(e);
															#line 301 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if ((i + 1) % batchSize == 0)
															#line 5585 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 302 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_2 = delay(0);
															#line 302 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 5591 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1Catch2loopBody1when1(__when_expr_2.get(), loopDepth); };
			static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 3;
															#line 302 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< IncrementalBroadcastWithErrorActor, 2, Void >*>(static_cast<IncrementalBroadcastWithErrorActor*>(this)));
															#line 5596 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		else
		{
			loopDepth = a_body1Catch2loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch2break1(int loopDepth) 
	{
		try {
			return a_body1Catch2cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch2loopBody1cont1(int loopDepth) 
	{
															#line 299 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		i++;
															#line 5623 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (loopDepth == 0) return a_body1Catch2loopHead1(0);

		return loopDepth;
	}
	int a_body1Catch2loopBody1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2loopBody1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2loopBody1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1Catch2loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2loopBody1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state > 0) static_cast<IncrementalBroadcastWithErrorActor*>(this)->actor_wait_state = 0;
		static_cast<IncrementalBroadcastWithErrorActor*>(this)->ActorCallback< IncrementalBroadcastWithErrorActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch2loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< IncrementalBroadcastWithErrorActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch2loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< IncrementalBroadcastWithErrorActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<T> input;
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	std::vector<Promise<T>> output;
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int batchSize;
															#line 285 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	int i;
															#line 287 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	T value;
															#line 298 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Error e;
															#line 5727 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via incrementalBroadcastWithError()
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class IncrementalBroadcastWithErrorActor final : public Actor<Void>, public ActorCallback< IncrementalBroadcastWithErrorActor<T>, 0, T >, public ActorCallback< IncrementalBroadcastWithErrorActor<T>, 1, Void >, public ActorCallback< IncrementalBroadcastWithErrorActor<T>, 2, Void >, public FastAllocated<IncrementalBroadcastWithErrorActor<T>>, public IncrementalBroadcastWithErrorActorState<T, IncrementalBroadcastWithErrorActor<T>> {
															#line 5734 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<IncrementalBroadcastWithErrorActor<T>>::operator new;
	using FastAllocated<IncrementalBroadcastWithErrorActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(10282498128378925568UL, 12059662882818415104UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< IncrementalBroadcastWithErrorActor<T>, 0, T >;
friend struct ActorCallback< IncrementalBroadcastWithErrorActor<T>, 1, Void >;
friend struct ActorCallback< IncrementalBroadcastWithErrorActor<T>, 2, Void >;
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	IncrementalBroadcastWithErrorActor(Future<T> const& input,std::vector<Promise<T>> const& output,int const& batchSize) 
															#line 5753 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<Void>(),
		   IncrementalBroadcastWithErrorActorState<T, IncrementalBroadcastWithErrorActor<T>>(input, output, batchSize),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(1390551743455648768UL, 13225986501383641088UL);
		ActorExecutionContextHelper __helper(static_cast<IncrementalBroadcastWithErrorActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("incrementalBroadcastWithError");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("incrementalBroadcastWithError", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< IncrementalBroadcastWithErrorActor<T>, 0, T >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< IncrementalBroadcastWithErrorActor<T>, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< IncrementalBroadcastWithErrorActor<T>, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<Void> incrementalBroadcastWithError( Future<T> const& input, std::vector<Promise<T>> const& output, int const& batchSize ) {
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<Void>(new IncrementalBroadcastWithErrorActor<T>(input, output, batchSize));
															#line 5790 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 308 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

// Needed for the call to endpointNotFound()
#include "fdbrpc/FailureMonitor.h"

struct PeerHolder {
	Reference<Peer> peer;
	explicit PeerHolder(Reference<Peer> peer) : peer(peer) {
		if (peer) {
			peer->outstandingReplies++;
		}
	}
	~PeerHolder() {
		if (peer) {
			peer->outstandingReplies--;
		}
	}
};

// Implements getReplyStream, this a void actor with the same lifetime as the input ReplyPromiseStream.
// Because this actor holds a reference to the stream, normally it would be impossible to know when there are no other
// references. To get around this, there is a SAV inside the stream that has one less promise reference than it should
// (caused by getErrorFutureAndDelPromiseRef()). When that SAV gets a broken promise because no one besides this void
// actor is referencing it, this void actor will get a broken_promise dropping the final reference to the full
// ReplyPromiseStream
															#line 5818 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via endStreamOnDisconnect()
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X, class EndStreamOnDisconnectActor>
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class EndStreamOnDisconnectActorState {
															#line 5825 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	EndStreamOnDisconnectActorState(Future<Void> const& signal,ReplyPromiseStream<X> const& stream,Endpoint const& endpoint,Reference<Peer> const& peer = Reference<Peer>()) 
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : signal(signal),
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   stream(stream),
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   endpoint(endpoint),
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   peer(peer),
															#line 337 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   holder(PeerHolder(peer))
															#line 5840 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this));

	}
	~EndStreamOnDisconnectActorState() 
	{
		fdb_probe_actor_destroy("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			stream.setRequestStreamEndpoint(endpoint);
															#line 5855 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			try {
															#line 341 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_0 = signal;
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 344 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_1 = peer.isValid() ? peer->disconnect.getFuture() : Never();
															#line 5863 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch2(__when_expr_1.getError(), loopDepth); else return a_body1when2(__when_expr_1.get(), loopDepth); };
															#line 347 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_2 = stream.getErrorFutureAndDelPromiseRef();
															#line 5867 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch2(__when_expr_2.getError(), loopDepth); else return a_body1when3(__when_expr_2.get(), loopDepth); };
				static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state = 1;
															#line 341 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< EndStreamOnDisconnectActor, 0, Void >*>(static_cast<EndStreamOnDisconnectActor*>(this)));
															#line 344 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< EndStreamOnDisconnectActor, 1, Void >*>(static_cast<EndStreamOnDisconnectActor*>(this)));
															#line 347 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< EndStreamOnDisconnectActor, 2, Void >*>(static_cast<EndStreamOnDisconnectActor*>(this)));
															#line 5876 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		delete static_cast<EndStreamOnDisconnectActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() == error_code_broken_promise)
															#line 5911 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 352 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (!stream.connected())
															#line 5915 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				{
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
					StrictFuture<Void> __when_expr_3 = signal || stream.onConnected();
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
					if (__when_expr_3.isReady()) { if (__when_expr_3.isError()) return a_body1Catch1(__when_expr_3.getError(), loopDepth); else return a_body1Catch2when1(__when_expr_3.get(), loopDepth); };
															#line 5921 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
					static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state = 2;
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
					__when_expr_3.addCallbackAndClear(static_cast<ActorCallback< EndStreamOnDisconnectActor, 3, Void >*>(static_cast<EndStreamOnDisconnectActor*>(this)));
															#line 5925 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
					loopDepth = 0;
				}
				else
				{
					loopDepth = a_body1Catch2cont2(loopDepth);
				}
			}
			else
			{
				loopDepth = a_body1Catch2cont1(loopDepth);
			}
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void const& _,int loopDepth) 
	{
															#line 342 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		stream.sendError(connection_failed());
															#line 5956 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void && _,int loopDepth) 
	{
															#line 342 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		stream.sendError(connection_failed());
															#line 5965 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when2(Void const& _,int loopDepth) 
	{
															#line 345 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		stream.sendError(connection_failed());
															#line 5974 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when2(Void && _,int loopDepth) 
	{
															#line 345 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		stream.sendError(connection_failed());
															#line 5983 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1when3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state > 0) static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state = 0;
		static_cast<EndStreamOnDisconnectActor*>(this)->ActorCallback< EndStreamOnDisconnectActor, 0, Void >::remove();
		static_cast<EndStreamOnDisconnectActor*>(this)->ActorCallback< EndStreamOnDisconnectActor, 1, Void >::remove();
		static_cast<EndStreamOnDisconnectActor*>(this)->ActorCallback< EndStreamOnDisconnectActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< EndStreamOnDisconnectActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< EndStreamOnDisconnectActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when3(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1when3(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< EndStreamOnDisconnectActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 2);

	}
	int a_body1cont3(int loopDepth) 
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
	int a_body1Catch2cont1(int loopDepth) 
	{
															#line 357 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		stream.notifyFailed();
															#line 6196 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2cont2(int loopDepth) 
	{
		loopDepth = a_body1Catch2cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont2(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont2(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1Catch2when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state > 0) static_cast<EndStreamOnDisconnectActor*>(this)->actor_wait_state = 0;
		static_cast<EndStreamOnDisconnectActor*>(this)->ActorCallback< EndStreamOnDisconnectActor, 3, Void >::remove();

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 3, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_fire(ActorCallback< EndStreamOnDisconnectActor, 3, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_error(ActorCallback< EndStreamOnDisconnectActor, 3, Void >*,Error err) 
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), 3);

	}
	int a_body1cont4(int loopDepth) 
	{
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		delete static_cast<EndStreamOnDisconnectActor*>(this);
															#line 6298 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<Void> signal;
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReplyPromiseStream<X> stream;
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Endpoint endpoint;
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Reference<Peer> peer;
															#line 337 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	PeerHolder holder;
															#line 6313 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via endStreamOnDisconnect()
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class EndStreamOnDisconnectActor final : public Actor<void>, public ActorCallback< EndStreamOnDisconnectActor<X>, 0, Void >, public ActorCallback< EndStreamOnDisconnectActor<X>, 1, Void >, public ActorCallback< EndStreamOnDisconnectActor<X>, 2, Void >, public ActorCallback< EndStreamOnDisconnectActor<X>, 3, Void >, public FastAllocated<EndStreamOnDisconnectActor<X>>, public EndStreamOnDisconnectActorState<X, EndStreamOnDisconnectActor<X>> {
															#line 6320 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<EndStreamOnDisconnectActor<X>>::operator new;
	using FastAllocated<EndStreamOnDisconnectActor<X>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(12365732247398988288UL, 16925862612825946368UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< EndStreamOnDisconnectActor<X>, 0, Void >;
friend struct ActorCallback< EndStreamOnDisconnectActor<X>, 1, Void >;
friend struct ActorCallback< EndStreamOnDisconnectActor<X>, 2, Void >;
friend struct ActorCallback< EndStreamOnDisconnectActor<X>, 3, Void >;
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	EndStreamOnDisconnectActor(Future<Void> const& signal,ReplyPromiseStream<X> const& stream,Endpoint const& endpoint,Reference<Peer> const& peer = Reference<Peer>()) 
															#line 6340 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<void>(),
		   EndStreamOnDisconnectActorState<X, EndStreamOnDisconnectActor<X>>(signal, stream, endpoint, peer),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(8081630550668594688UL, 16244017713865151488UL);
		ActorExecutionContextHelper __helper(static_cast<EndStreamOnDisconnectActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("endStreamOnDisconnect");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("endStreamOnDisconnect", reinterpret_cast<unsigned long>(this), -1);

	}
};
} // namespace
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
void endStreamOnDisconnect( Future<Void> const& signal, ReplyPromiseStream<X> const& stream, Endpoint const& endpoint, Reference<Peer> const& peer = Reference<Peer>() ) {
															#line 332 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	new EndStreamOnDisconnectActor<X>(signal, stream, endpoint, peer);
															#line 6366 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 360 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

// Implements tryGetReply, getReplyUnlessFailedFor
															#line 6372 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via waitValueOrSignal()
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X, class WaitValueOrSignalActor>
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class WaitValueOrSignalActorState {
															#line 6379 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WaitValueOrSignalActorState(Future<X> const& value,Future<Void> const& signal,Endpoint const& endpoint,ReplyPromise<X> const& holdme = ReplyPromise<X>(),Reference<Peer> const& peer = Reference<Peer>()) 
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : value(value),
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   signal(signal),
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   endpoint(endpoint),
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   holdme(holdme),
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   peer(peer),
															#line 368 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   holder(PeerHolder(peer))
															#line 6396 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("waitValueOrSignal", reinterpret_cast<unsigned long>(this));

	}
	~WaitValueOrSignalActorState() 
	{
		fdb_probe_actor_destroy("waitValueOrSignal", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 369 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			;
															#line 6411 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~WaitValueOrSignalActorState();
		static_cast<WaitValueOrSignalActor*>(this)->sendErrorAndDelPromiseRef(error);
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
		try {
															#line 372 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<X> __when_expr_0 = value;
															#line 371 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (static_cast<WaitValueOrSignalActor*>(this)->actor_wait_state < 0) return a_body1loopBody1Catch1(actor_cancelled(), loopDepth);
															#line 6444 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1loopBody1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
															#line 375 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			StrictFuture<Void> __when_expr_1 = signal;
															#line 6448 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1loopBody1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1loopBody1when2(__when_expr_1.get(), loopDepth); };
			static_cast<WaitValueOrSignalActor*>(this)->actor_wait_state = 1;
															#line 372 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< WaitValueOrSignalActor, 0, X >*>(static_cast<WaitValueOrSignalActor*>(this)));
															#line 375 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< WaitValueOrSignalActor, 1, Void >*>(static_cast<WaitValueOrSignalActor*>(this)));
															#line 6455 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1loopBody1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1loopBody1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 382 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (signal.isError())
															#line 6477 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 383 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				TraceEvent(SevError, "WaitValueOrSignalError").error(signal.getError());
															#line 384 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(ErrorOr<X>(internal_error())); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6483 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(ErrorOr<X>(internal_error()));
				this->~WaitValueOrSignalActorState();
				static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
				return 0;
			}
															#line 387 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() == error_code_actor_cancelled)
															#line 6491 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 388 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch1(e, std::max(0, loopDepth - 1));
															#line 6495 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 392 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() != error_code_broken_promise || signal.isError())
															#line 6499 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 393 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(ErrorOr<X>(e)); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6503 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(ErrorOr<X>(e));
				this->~WaitValueOrSignalActorState();
				static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
				return 0;
			}
															#line 394 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			IFailureMonitor::failureMonitor().endpointNotFound(endpoint);
															#line 395 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			value = Never();
															#line 6513 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			loopDepth = a_body1loopBody1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1when1(X const& x,int loopDepth) 
	{
															#line 373 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(x); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6528 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(x);
		this->~WaitValueOrSignalActorState();
		static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when1(X && x,int loopDepth) 
	{
															#line 373 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(x); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6540 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(x);
		this->~WaitValueOrSignalActorState();
		static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when2(Void const& _,int loopDepth) 
	{
															#line 376 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(ErrorOr<X>(IFailureMonitor::failureMonitor().knownUnauthorized(endpoint) ? unauthorized_attempt() : request_maybe_delivered())); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6552 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(ErrorOr<X>(IFailureMonitor::failureMonitor().knownUnauthorized(endpoint) ? unauthorized_attempt() : request_maybe_delivered()));
		this->~WaitValueOrSignalActorState();
		static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1when2(Void && _,int loopDepth) 
	{
															#line 376 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<WaitValueOrSignalActor*>(this)->SAV<ErrorOr<X>>::futures) { (void)(ErrorOr<X>(IFailureMonitor::failureMonitor().knownUnauthorized(endpoint) ? unauthorized_attempt() : request_maybe_delivered())); this->~WaitValueOrSignalActorState(); static_cast<WaitValueOrSignalActor*>(this)->destroy(); return 0; }
															#line 6564 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<WaitValueOrSignalActor*>(this)->SAV< ErrorOr<X> >::value()) ErrorOr<X>(ErrorOr<X>(IFailureMonitor::failureMonitor().knownUnauthorized(endpoint) ? unauthorized_attempt() : request_maybe_delivered()));
		this->~WaitValueOrSignalActorState();
		static_cast<WaitValueOrSignalActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<WaitValueOrSignalActor*>(this)->actor_wait_state > 0) static_cast<WaitValueOrSignalActor*>(this)->actor_wait_state = 0;
		static_cast<WaitValueOrSignalActor*>(this)->ActorCallback< WaitValueOrSignalActor, 0, X >::remove();
		static_cast<WaitValueOrSignalActor*>(this)->ActorCallback< WaitValueOrSignalActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< WaitValueOrSignalActor, 0, X >*,X const& value) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< WaitValueOrSignalActor, 0, X >*,X && value) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< WaitValueOrSignalActor, 0, X >*,Error err) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< WaitValueOrSignalActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when2(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< WaitValueOrSignalActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< WaitValueOrSignalActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<X> value;
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<Void> signal;
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Endpoint endpoint;
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReplyPromise<X> holdme;
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Reference<Peer> peer;
															#line 368 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	PeerHolder holder;
															#line 6705 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via waitValueOrSignal()
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class WaitValueOrSignalActor final : public Actor<ErrorOr<X>>, public ActorCallback< WaitValueOrSignalActor<X>, 0, X >, public ActorCallback< WaitValueOrSignalActor<X>, 1, Void >, public FastAllocated<WaitValueOrSignalActor<X>>, public WaitValueOrSignalActorState<X, WaitValueOrSignalActor<X>> {
															#line 6712 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<WaitValueOrSignalActor<X>>::operator new;
	using FastAllocated<WaitValueOrSignalActor<X>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(963672891372916992UL, 2539131630716541184UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<ErrorOr<X>>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< WaitValueOrSignalActor<X>, 0, X >;
friend struct ActorCallback< WaitValueOrSignalActor<X>, 1, Void >;
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	WaitValueOrSignalActor(Future<X> const& value,Future<Void> const& signal,Endpoint const& endpoint,ReplyPromise<X> const& holdme = ReplyPromise<X>(),Reference<Peer> const& peer = Reference<Peer>()) 
															#line 6730 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<ErrorOr<X>>(),
		   WaitValueOrSignalActorState<X, WaitValueOrSignalActor<X>>(value, signal, endpoint, holdme, peer),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("waitValueOrSignal", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(10394841400439412224UL, 14551502886970699264UL);
		ActorExecutionContextHelper __helper(static_cast<WaitValueOrSignalActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("waitValueOrSignal");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("waitValueOrSignal", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< WaitValueOrSignalActor<X>, 0, X >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<ErrorOr<X>> waitValueOrSignal( Future<X> const& value, Future<Void> const& signal, Endpoint const& endpoint, ReplyPromise<X> const& holdme = ReplyPromise<X>(), Reference<Peer> const& peer = Reference<Peer>() ) {
															#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<ErrorOr<X>>(new WaitValueOrSignalActor<X>(value, signal, endpoint, holdme, peer));
															#line 6765 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 399 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 6770 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via sendCanceler()
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T, class SendCancelerActor>
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class SendCancelerActorState {
															#line 6777 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	SendCancelerActorState(ReplyPromise<T> const& reply,ReliablePacket* const& send,Endpoint const& endpoint) 
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : reply(reply),
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   send(send),
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   endpoint(endpoint),
															#line 402 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   didCancelReliable(false)
															#line 6790 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("sendCanceler", reinterpret_cast<unsigned long>(this));

	}
	~SendCancelerActorState() 
	{
		fdb_probe_actor_destroy("sendCanceler", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 404 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				;
															#line 6806 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				loopDepth = a_body1loopHead1(loopDepth);
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
		this->~SendCancelerActorState();
		static_cast<SendCancelerActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 424 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (!didCancelReliable)
															#line 6836 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 425 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				FlowTransport::transport().cancelReliable(send);
															#line 6840 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 427 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() == error_code_broken_promise)
															#line 6844 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 428 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				IFailureMonitor::failureMonitor().endpointNotFound(endpoint);
															#line 6848 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 430 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			return a_body1Catch1(e, loopDepth);
															#line 6852 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

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
															#line 405 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (IFailureMonitor::failureMonitor().permanentlyFailed(endpoint))
															#line 6873 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		{
															#line 406 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			FlowTransport::transport().cancelReliable(send);
															#line 407 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			didCancelReliable = true;
															#line 408 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (IFailureMonitor::failureMonitor().knownUnauthorized(endpoint))
															#line 6881 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 409 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				return a_body1Catch2(unauthorized_attempt(), std::max(0, loopDepth - 1));
															#line 6885 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
			else
			{
															#line 411 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<Void> __when_expr_0 = Never();
															#line 411 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (static_cast<SendCancelerActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 6893 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
				static_cast<SendCancelerActor*>(this)->actor_wait_state = 1;
															#line 411 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< SendCancelerActor, 0, Void >*>(static_cast<SendCancelerActor*>(this)));
															#line 6898 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				loopDepth = 0;
			}
		}
		else
		{
			loopDepth = a_body1loopBody1cont1(loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
															#line 415 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<T> __when_expr_1 = reply.getFuture();
															#line 414 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (static_cast<SendCancelerActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 6915 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch2(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
															#line 420 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		StrictFuture<Void> __when_expr_2 = IFailureMonitor::failureMonitor().onStateChanged(endpoint);
															#line 6919 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch2(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when2(__when_expr_2.get(), loopDepth); };
		static_cast<SendCancelerActor*>(this)->actor_wait_state = 2;
															#line 415 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< SendCancelerActor, 1, T >*>(static_cast<SendCancelerActor*>(this)));
															#line 420 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< SendCancelerActor, 2, Void >*>(static_cast<SendCancelerActor*>(this)));
															#line 6926 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont2(int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont4(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont4(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<SendCancelerActor*>(this)->actor_wait_state > 0) static_cast<SendCancelerActor*>(this)->actor_wait_state = 0;
		static_cast<SendCancelerActor*>(this)->ActorCallback< SendCancelerActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< SendCancelerActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont5(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(T const& t,int loopDepth) 
	{
															#line 416 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		FlowTransport::transport().cancelReliable(send);
															#line 417 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		didCancelReliable = true;
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<SendCancelerActor*>(this)->SAV<T>::futures) { (void)(t); this->~SendCancelerActorState(); static_cast<SendCancelerActor*>(this)->destroy(); return 0; }
															#line 7038 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<SendCancelerActor*>(this)->SAV< T >::value()) T(t);
		this->~SendCancelerActorState();
		static_cast<SendCancelerActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(T && t,int loopDepth) 
	{
															#line 416 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		FlowTransport::transport().cancelReliable(send);
															#line 417 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		didCancelReliable = true;
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<SendCancelerActor*>(this)->SAV<T>::futures) { (void)(t); this->~SendCancelerActorState(); static_cast<SendCancelerActor*>(this)->destroy(); return 0; }
															#line 7054 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<SendCancelerActor*>(this)->SAV< T >::value()) T(t);
		this->~SendCancelerActorState();
		static_cast<SendCancelerActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1when2(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont5(loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<SendCancelerActor*>(this)->actor_wait_state > 0) static_cast<SendCancelerActor*>(this)->actor_wait_state = 0;
		static_cast<SendCancelerActor*>(this)->ActorCallback< SendCancelerActor, 1, T >::remove();
		static_cast<SendCancelerActor*>(this)->ActorCallback< SendCancelerActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 1, T >*,T const& value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 1, T >*,T && value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< SendCancelerActor, 1, T >*,Error err) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< SendCancelerActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< SendCancelerActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReplyPromise<T> reply;
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReliablePacket* send;
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Endpoint endpoint;
															#line 402 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	bool didCancelReliable;
															#line 7203 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via sendCanceler()
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class SendCancelerActor final : public Actor<T>, public ActorCallback< SendCancelerActor<T>, 0, Void >, public ActorCallback< SendCancelerActor<T>, 1, T >, public ActorCallback< SendCancelerActor<T>, 2, Void >, public FastAllocated<SendCancelerActor<T>>, public SendCancelerActorState<T, SendCancelerActor<T>> {
															#line 7210 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<SendCancelerActor<T>>::operator new;
	using FastAllocated<SendCancelerActor<T>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(8008723839166955520UL, 13848175332583992064UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<T>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< SendCancelerActor<T>, 0, Void >;
friend struct ActorCallback< SendCancelerActor<T>, 1, T >;
friend struct ActorCallback< SendCancelerActor<T>, 2, Void >;
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	SendCancelerActor(ReplyPromise<T> const& reply,ReliablePacket* const& send,Endpoint const& endpoint) 
															#line 7229 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<T>(),
		   SendCancelerActorState<T, SendCancelerActor<T>>(reply, send, endpoint),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("sendCanceler", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(14794441375181495296UL, 11283513300419985664UL);
		ActorExecutionContextHelper __helper(static_cast<SendCancelerActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("sendCanceler");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("sendCanceler", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< SendCancelerActor<T>, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< SendCancelerActor<T>, 1, T >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class T>
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<T> sendCanceler( ReplyPromise<T> const& reply, ReliablePacket* const& send, Endpoint const& endpoint ) {
															#line 400 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<T>(new SendCancelerActor<T>(reply, send, endpoint));
															#line 7265 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 433 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

															#line 7270 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
namespace {
// This generated class is to be used only via reportEndpointFailure()
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X, class ReportEndpointFailureActor>
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ReportEndpointFailureActorState {
															#line 7277 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReportEndpointFailureActorState(Future<X> const& value,Endpoint const& endpoint) 
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		 : value(value),
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		   endpoint(endpoint)
															#line 7286 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
	{
		fdb_probe_actor_create("reportEndpointFailure", reinterpret_cast<unsigned long>(this));

	}
	~ReportEndpointFailureActorState() 
	{
		fdb_probe_actor_destroy("reportEndpointFailure", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 437 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				StrictFuture<X> __when_expr_0 = value;
															#line 437 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				if (static_cast<ReportEndpointFailureActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 7304 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<ReportEndpointFailureActor*>(this)->actor_wait_state = 1;
															#line 437 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ReportEndpointFailureActor, 0, X >*>(static_cast<ReportEndpointFailureActor*>(this)));
															#line 7309 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
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
		this->~ReportEndpointFailureActorState();
		static_cast<ReportEndpointFailureActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			if (e.code() == error_code_broken_promise)
															#line 7339 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			{
															#line 441 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
				IFailureMonitor::failureMonitor().endpointNotFound(endpoint);
															#line 7343 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
			}
															#line 443 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
			return a_body1Catch1(e, loopDepth);
															#line 7347 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont2(X const& x,int loopDepth) 
	{
															#line 438 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<ReportEndpointFailureActor*>(this)->SAV<X>::futures) { (void)(x); this->~ReportEndpointFailureActorState(); static_cast<ReportEndpointFailureActor*>(this)->destroy(); return 0; }
															#line 7361 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<ReportEndpointFailureActor*>(this)->SAV< X >::value()) X(x);
		this->~ReportEndpointFailureActorState();
		static_cast<ReportEndpointFailureActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont2(X && x,int loopDepth) 
	{
															#line 438 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
		if (!static_cast<ReportEndpointFailureActor*>(this)->SAV<X>::futures) { (void)(x); this->~ReportEndpointFailureActorState(); static_cast<ReportEndpointFailureActor*>(this)->destroy(); return 0; }
															#line 7373 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		new (&static_cast<ReportEndpointFailureActor*>(this)->SAV< X >::value()) X(x);
		this->~ReportEndpointFailureActorState();
		static_cast<ReportEndpointFailureActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1when1(X const& x,int loopDepth) 
	{
		loopDepth = a_body1cont2(x, loopDepth);

		return loopDepth;
	}
	int a_body1when1(X && x,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(x), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ReportEndpointFailureActor*>(this)->actor_wait_state > 0) static_cast<ReportEndpointFailureActor*>(this)->actor_wait_state = 0;
		static_cast<ReportEndpointFailureActor*>(this)->ActorCallback< ReportEndpointFailureActor, 0, X >::remove();

	}
	void a_callback_fire(ActorCallback< ReportEndpointFailureActor, 0, X >*,X const& value) 
	{
		fdb_probe_actor_enter("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReportEndpointFailureActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ReportEndpointFailureActor, 0, X >*,X && value) 
	{
		fdb_probe_actor_enter("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReportEndpointFailureActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ReportEndpointFailureActor, 0, X >*,Error err) 
	{
		fdb_probe_actor_enter("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ReportEndpointFailureActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("reportEndpointFailure", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Future<X> value;
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	Endpoint endpoint;
															#line 7460 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
};
// This generated class is to be used only via reportEndpointFailure()
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
class ReportEndpointFailureActor final : public Actor<X>, public ActorCallback< ReportEndpointFailureActor<X>, 0, X >, public FastAllocated<ReportEndpointFailureActor<X>>, public ReportEndpointFailureActorState<X, ReportEndpointFailureActor<X>> {
															#line 7467 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
public:
	using FastAllocated<ReportEndpointFailureActor<X>>::operator new;
	using FastAllocated<ReportEndpointFailureActor<X>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(14967381961958091520UL, 1278052758567514880UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<X>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< ReportEndpointFailureActor<X>, 0, X >;
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	ReportEndpointFailureActor(Future<X> const& value,Endpoint const& endpoint) 
															#line 7484 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
		 : Actor<X>(),
		   ReportEndpointFailureActorState<X, ReportEndpointFailureActor<X>>(value, endpoint),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("reportEndpointFailure", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(13580180669355110656UL, 12552375509477596672UL);
		ActorExecutionContextHelper __helper(static_cast<ReportEndpointFailureActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("reportEndpointFailure");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("reportEndpointFailure", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< ReportEndpointFailureActor<X>, 0, X >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
template <class X>
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
[[nodiscard]] Future<X> reportEndpointFailure( Future<X> const& value, Endpoint const& endpoint ) {
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"
	return Future<X>(new ReportEndpointFailureActor<X>(value, endpoint));
															#line 7519 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/genericactors.actor.g.h"
}

#line 446 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/genericactors.actor.h"

#include "flow/unactorcompiler.h"

#endif
