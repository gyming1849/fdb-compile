#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
/*
 * AsyncFileReadAhead.actor.h
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
#if defined(NO_INTELLISENSE) && !defined(FDBRPC_ASYNCFILEREADAHEAD_ACTOR_G_H)
#define FDBRPC_ASYNCFILEREADAHEAD_ACTOR_G_H
#include "fdbrpc/AsyncFileReadAhead.actor.g.h"
#elif !defined(FDBRPC_ASYNCFILEREADAHEAD_ACTOR_H)
#define FDBRPC_ASYNCFILEREADAHEAD_ACTOR_H

#include "flow/flow.h"
#include "flow/IAsyncFile.h"
#include "flow/actorcompiler.h" // This must be the last #include.

// Read-only file type that wraps another file instance, reads in large blocks, and reads ahead of the actual range
// requested
class AsyncFileReadAheadCache final : public IAsyncFile, public ReferenceCounted<AsyncFileReadAheadCache> {
public:
	void addref() override { ReferenceCounted<AsyncFileReadAheadCache>::addref(); }
	void delref() override { ReferenceCounted<AsyncFileReadAheadCache>::delref(); }

	virtual StringRef getClassName() override { return "AsyncFileReadAheadCache"_sr; }

	struct CacheBlock : ReferenceCounted<CacheBlock> {
		CacheBlock(int size = 0) : data(new uint8_t[size]), len(size) {}
		~CacheBlock() { delete[] data; }
		uint8_t* data;
		int len;
	};

	// Read from the underlying file to a CacheBlock
																#line 54 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
// This generated class is to be used only via readBlock()
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
template <class ReadBlockActor>
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
class ReadBlockActorState {
															#line 60 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
public:
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	ReadBlockActorState(AsyncFileReadAheadCache* const& f,int const& length,int64_t const& offset) 
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		 : f(f),
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		   length(length),
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		   offset(offset)
															#line 71 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
	{
		fdb_probe_actor_create("readBlock", reinterpret_cast<unsigned long>(this));

	}
	~ReadBlockActorState() 
	{
		fdb_probe_actor_destroy("readBlock", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			StrictFuture<Void> __when_expr_0 = f->m_max_concurrent_reads.take();
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (static_cast<ReadBlockActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 88 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<ReadBlockActor*>(this)->actor_wait_state = 1;
															#line 53 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ReadBlockActor, 0, Void >*>(static_cast<ReadBlockActor*>(this)));
															#line 93 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
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
		this->~ReadBlockActorState();
		static_cast<ReadBlockActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void const& _,int loopDepth) 
	{
															#line 55 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		block = Reference<CacheBlock>(new CacheBlock(length));
															#line 116 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		try {
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			StrictFuture<int> __when_expr_1 = uncancellable(holdWhile(block, f->m_f->read(block->data, length, offset)));
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (static_cast<ReadBlockActor*>(this)->actor_wait_state < 0) return a_body1cont1Catch1(actor_cancelled(), loopDepth);
															#line 122 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
			static_cast<ReadBlockActor*>(this)->actor_wait_state = 2;
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< ReadBlockActor, 1, int >*>(static_cast<ReadBlockActor*>(this)));
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont1(Void && _,int loopDepth) 
	{
															#line 55 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		block = Reference<CacheBlock>(new CacheBlock(length));
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		try {
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			StrictFuture<int> __when_expr_1 = uncancellable(holdWhile(block, f->m_f->read(block->data, length, offset)));
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (static_cast<ReadBlockActor*>(this)->actor_wait_state < 0) return a_body1cont1Catch1(actor_cancelled(), loopDepth);
															#line 148 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
			static_cast<ReadBlockActor*>(this)->actor_wait_state = 2;
															#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< ReadBlockActor, 1, int >*>(static_cast<ReadBlockActor*>(this)));
															#line 153 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<ReadBlockActor*>(this)->actor_wait_state > 0) static_cast<ReadBlockActor*>(this)->actor_wait_state = 0;
		static_cast<ReadBlockActor*>(this)->ActorCallback< ReadBlockActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< ReadBlockActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ReadBlockActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ReadBlockActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 64 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		f->m_max_concurrent_reads.release(1);
															#line 65 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (!static_cast<ReadBlockActor*>(this)->SAV<Reference<CacheBlock>>::futures) { (void)(block); this->~ReadBlockActorState(); static_cast<ReadBlockActor*>(this)->destroy(); return 0; }
															#line 245 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		new (&static_cast<ReadBlockActor*>(this)->SAV< Reference<CacheBlock> >::value()) Reference<CacheBlock>(std::move(block)); // state_var_RVO
		this->~ReadBlockActorState();
		static_cast<ReadBlockActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 60 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			f->m_max_concurrent_reads.release(1);
															#line 61 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			return a_body1Catch1(e, loopDepth);
															#line 260 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont3(int const& len,int loopDepth) 
	{
															#line 58 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		block->len = len;
															#line 274 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		loopDepth = a_body1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1cont3(int && len,int loopDepth) 
	{
															#line 58 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		block->len = len;
															#line 283 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		loopDepth = a_body1cont5(loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(int const& len,int loopDepth) 
	{
		loopDepth = a_body1cont3(len, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(int && len,int loopDepth) 
	{
		loopDepth = a_body1cont3(std::move(len), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<ReadBlockActor*>(this)->actor_wait_state > 0) static_cast<ReadBlockActor*>(this)->actor_wait_state = 0;
		static_cast<ReadBlockActor*>(this)->ActorCallback< ReadBlockActor, 1, int >::remove();

	}
	void a_callback_fire(ActorCallback< ReadBlockActor, 1, int >*,int const& value) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1cont1Catch1(error, 0);
		} catch (...) {
			a_body1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< ReadBlockActor, 1, int >*,int && value) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1cont1Catch1(error, 0);
		} catch (...) {
			a_body1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< ReadBlockActor, 1, int >*,Error err) 
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1cont1Catch1(error, 0);
		} catch (...) {
			a_body1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont5(int loopDepth) 
	{
		try {
			loopDepth = a_body1cont2(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	AsyncFileReadAheadCache* f;
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int length;
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int64_t offset;
															#line 55 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	Reference<CacheBlock> block;
															#line 384 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
};
// This generated class is to be used only via readBlock()
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
class ReadBlockActor final : public Actor<Reference<CacheBlock>>, public ActorCallback< ReadBlockActor, 0, Void >, public ActorCallback< ReadBlockActor, 1, int >, public FastAllocated<ReadBlockActor>, public ReadBlockActorState<ReadBlockActor> {
															#line 389 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
public:
	using FastAllocated<ReadBlockActor>::operator new;
	using FastAllocated<ReadBlockActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(9319905832167211264UL, 8730818910714917376UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Reference<CacheBlock>>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< ReadBlockActor, 0, Void >;
friend struct ActorCallback< ReadBlockActor, 1, int >;
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	ReadBlockActor(AsyncFileReadAheadCache* const& f,int const& length,int64_t const& offset) 
															#line 407 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		 : Actor<Reference<CacheBlock>>(),
		   ReadBlockActorState<ReadBlockActor>(f, length, offset),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("readBlock", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(8789183085673993728UL, 4633063668185402624UL);
		ActorExecutionContextHelper __helper(static_cast<ReadBlockActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("readBlock");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("readBlock", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< ReadBlockActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< ReadBlockActor, 1, int >*)0, actor_cancelled()); break;
		}

	}
};
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
[[nodiscard]] static Future<Reference<CacheBlock>> readBlock( AsyncFileReadAheadCache* const& f, int const& length, int64_t const& offset ) {
															#line 52 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	return Future<Reference<CacheBlock>>(new ReadBlockActor(f, length, offset));
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
}

#line 67 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"

																#line 445 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
// This generated class is to be used only via read_impl()
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
template <class Read_implActor>
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
class Read_implActorState {
															#line 451 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
public:
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	Read_implActorState(Reference<AsyncFileReadAheadCache> const& f,void* const& data,int const& length,int64_t const& offset) 
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		 : f(f),
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		   data(data),
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		   length(length),
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		   offset(offset)
															#line 464 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
	{
		fdb_probe_actor_create("read_impl", reinterpret_cast<unsigned long>(this));

	}
	~Read_implActorState() 
	{
		fdb_probe_actor_destroy("read_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 70 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			StrictFuture<int64_t> __when_expr_0 = f->size();
															#line 70 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (static_cast<Read_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 481 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<Read_implActor*>(this)->actor_wait_state = 1;
															#line 70 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Read_implActor, 0, int64_t >*>(static_cast<Read_implActor*>(this)));
															#line 486 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
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
		this->~Read_implActorState();
		static_cast<Read_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int64_t const& fileSize,int loopDepth) 
	{
															#line 71 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (offset >= fileSize)
															#line 509 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 72 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(0); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 513 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(0);
			this->~Read_implActorState();
			static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 74 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (length == 0)
															#line 521 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 75 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(0); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 525 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(0);
			this->~Read_implActorState();
			static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (offset + length > fileSize)
															#line 533 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 80 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			length = fileSize - offset;
															#line 537 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		}
															#line 83 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		firstBlockNum = offset / f->m_block_size;
															#line 84 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(f->m_block_size > 0);
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		lastBlockNum = (offset + length - 1) / f->m_block_size;
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		localCache = std::map<int, Future<Reference<CacheBlock>>>();
															#line 94 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		lastBlockNumInFile = ((fileSize + f->m_block_size - 1) / f->m_block_size) - 1;
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(lastBlockNum <= lastBlockNumInFile);
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int lastBlockToStart = std::min<int>(lastBlockNum + f->m_read_ahead_blocks, lastBlockNumInFile);
															#line 98 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		blockNum = int();
															#line 99 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		for(blockNum = firstBlockNum;blockNum <= lastBlockToStart;++blockNum) {
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			Future<Reference<CacheBlock>> fblock;
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			auto i = f->m_blocks.find(blockNum);
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (i == f->m_blocks.end() || (i->second.isValid() && i->second.isError()))
															#line 563 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 107 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				fblock = readBlock(f.getPtr(), f->m_block_size, (int64_t)f->m_block_size * blockNum);
															#line 108 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				f->m_blocks[blockNum] = fblock;
															#line 569 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
			else
			{
															#line 110 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				fblock = i->second;
															#line 575 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
															#line 113 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (blockNum <= lastBlockNum)
															#line 579 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 114 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				localCache[blockNum] = fblock;
															#line 583 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
		}
															#line 118 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		wpos = 0;
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		blockNum = firstBlockNum;
															#line 590 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		loopDepth = a_body1cont1loopHead1(loopDepth);

		return loopDepth;
	}
	int a_body1cont1(int64_t && fileSize,int loopDepth) 
	{
															#line 71 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (offset >= fileSize)
															#line 599 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 72 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(0); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 603 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(0);
			this->~Read_implActorState();
			static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 74 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (length == 0)
															#line 611 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 75 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(0); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 615 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(0);
			this->~Read_implActorState();
			static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (offset + length > fileSize)
															#line 623 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 80 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			length = fileSize - offset;
															#line 627 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		}
															#line 83 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		firstBlockNum = offset / f->m_block_size;
															#line 84 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(f->m_block_size > 0);
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		lastBlockNum = (offset + length - 1) / f->m_block_size;
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		localCache = std::map<int, Future<Reference<CacheBlock>>>();
															#line 94 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		lastBlockNumInFile = ((fileSize + f->m_block_size - 1) / f->m_block_size) - 1;
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(lastBlockNum <= lastBlockNumInFile);
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int lastBlockToStart = std::min<int>(lastBlockNum + f->m_read_ahead_blocks, lastBlockNumInFile);
															#line 98 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		blockNum = int();
															#line 99 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		for(blockNum = firstBlockNum;blockNum <= lastBlockToStart;++blockNum) {
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			Future<Reference<CacheBlock>> fblock;
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			auto i = f->m_blocks.find(blockNum);
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (i == f->m_blocks.end() || (i->second.isValid() && i->second.isError()))
															#line 653 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 107 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				fblock = readBlock(f.getPtr(), f->m_block_size, (int64_t)f->m_block_size * blockNum);
															#line 108 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				f->m_blocks[blockNum] = fblock;
															#line 659 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
			else
			{
															#line 110 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				fblock = i->second;
															#line 665 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
															#line 113 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (blockNum <= lastBlockNum)
															#line 669 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 114 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				localCache[blockNum] = fblock;
															#line 673 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
		}
															#line 118 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		wpos = 0;
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		blockNum = firstBlockNum;
															#line 680 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		loopDepth = a_body1cont1loopHead1(loopDepth);

		return loopDepth;
	}
	int a_body1when1(int64_t const& fileSize,int loopDepth) 
	{
		loopDepth = a_body1cont1(fileSize, loopDepth);

		return loopDepth;
	}
	int a_body1when1(int64_t && fileSize,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(fileSize), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<Read_implActor*>(this)->actor_wait_state > 0) static_cast<Read_implActor*>(this)->actor_wait_state = 0;
		static_cast<Read_implActor*>(this)->ActorCallback< Read_implActor, 0, int64_t >::remove();

	}
	void a_callback_fire(ActorCallback< Read_implActor, 0, int64_t >*,int64_t const& value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Read_implActor, 0, int64_t >*,int64_t && value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Read_implActor, 0, int64_t >*,Error err) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 147 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(wpos == length);
															#line 148 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		ASSERT(localCache.empty());
															#line 158 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (f->m_blocks.size() > f->m_cache_block_limit)
															#line 768 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 159 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			auto i = f->m_blocks.begin();
															#line 160 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			for(;i != f->m_blocks.end();) {
															#line 161 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				if (i->second.getFutureReferenceCount() == 1)
															#line 776 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
				{
															#line 163 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
					i = f->m_blocks.erase(i);
															#line 164 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
					if (f->m_blocks.size() <= f->m_cache_block_limit)
															#line 782 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
					{
						break;
					}
				}
				else
				{
															#line 167 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
					++i;
															#line 791 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
				}
			}
		}
															#line 171 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(wpos); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 797 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(std::move(wpos)); // state_var_RVO
		this->~Read_implActorState();
		static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
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
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (!(blockNum <= lastBlockNum))
															#line 816 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
			return a_body1cont1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 121 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		StrictFuture<Reference<CacheBlock>> __when_expr_1 = localCache[blockNum];
															#line 121 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (static_cast<Read_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 824 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1cont1loopBody1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Read_implActor*>(this)->actor_wait_state = 2;
															#line 121 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Read_implActor, 1, Reference<CacheBlock> >*>(static_cast<Read_implActor*>(this)));
															#line 829 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		loopDepth = 0;

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
	int a_body1cont1loopBody1cont1(Reference<CacheBlock> const& block,int loopDepth) 
	{
															#line 126 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t blockStart = (int64_t)blockNum * f->m_block_size;
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t readStart = std::max<int64_t>(0, offset - blockStart);
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t readEnd = std::min<int64_t>(f->m_block_size, offset + length - blockStart);
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int rlen = readEnd - readStart;
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		memcpy((uint8_t*)data + wpos, block->data + readStart, rlen);
															#line 131 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		wpos += rlen;
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		localCache.erase(blockNum);
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (f->m_blocks.size() > f->m_cache_block_limit)
															#line 865 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 138 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			auto i = f->m_blocks.find(blockNum);
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			ASSERT(i != f->m_blocks.end() && i->first == blockNum);
															#line 140 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (i->second.getFutureReferenceCount() == 1)
															#line 873 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				i = f->m_blocks.erase(i);
															#line 877 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
		}
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		++blockNum;
															#line 882 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		if (loopDepth == 0) return a_body1cont1loopHead1(0);

		return loopDepth;
	}
	int a_body1cont1loopBody1cont1(Reference<CacheBlock> && block,int loopDepth) 
	{
															#line 126 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t blockStart = (int64_t)blockNum * f->m_block_size;
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t readStart = std::max<int64_t>(0, offset - blockStart);
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int64_t readEnd = std::min<int64_t>(f->m_block_size, offset + length - blockStart);
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		int rlen = readEnd - readStart;
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		memcpy((uint8_t*)data + wpos, block->data + readStart, rlen);
															#line 131 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		wpos += rlen;
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		localCache.erase(blockNum);
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		if (f->m_blocks.size() > f->m_cache_block_limit)
															#line 905 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		{
															#line 138 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			auto i = f->m_blocks.find(blockNum);
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			ASSERT(i != f->m_blocks.end() && i->first == blockNum);
															#line 140 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
			if (i->second.getFutureReferenceCount() == 1)
															#line 913 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			{
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
				i = f->m_blocks.erase(i);
															#line 917 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
			}
		}
															#line 119 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
		++blockNum;
															#line 922 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		if (loopDepth == 0) return a_body1cont1loopHead1(0);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Reference<CacheBlock> const& block,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(block, loopDepth);

		return loopDepth;
	}
	int a_body1cont1loopBody1when1(Reference<CacheBlock> && block,int loopDepth) 
	{
		loopDepth = a_body1cont1loopBody1cont1(std::move(block), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Read_implActor*>(this)->actor_wait_state > 0) static_cast<Read_implActor*>(this)->actor_wait_state = 0;
		static_cast<Read_implActor*>(this)->ActorCallback< Read_implActor, 1, Reference<CacheBlock> >::remove();

	}
	void a_callback_fire(ActorCallback< Read_implActor, 1, Reference<CacheBlock> >*,Reference<CacheBlock> const& value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Read_implActor, 1, Reference<CacheBlock> >*,Reference<CacheBlock> && value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Read_implActor, 1, Reference<CacheBlock> >*,Error err) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	Reference<AsyncFileReadAheadCache> f;
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	void* data;
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int length;
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int64_t offset;
															#line 83 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int firstBlockNum;
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int lastBlockNum;
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	std::map<int, Future<Reference<CacheBlock>>> localCache;
															#line 94 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int lastBlockNumInFile;
															#line 98 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int blockNum;
															#line 118 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	int wpos;
															#line 1022 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
};
// This generated class is to be used only via read_impl()
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
class Read_implActor final : public Actor<int>, public ActorCallback< Read_implActor, 0, int64_t >, public ActorCallback< Read_implActor, 1, Reference<CacheBlock> >, public FastAllocated<Read_implActor>, public Read_implActorState<Read_implActor> {
															#line 1027 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
public:
	using FastAllocated<Read_implActor>::operator new;
	using FastAllocated<Read_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(346789019039847936UL, 6076539501947555072UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<int>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Read_implActor, 0, int64_t >;
friend struct ActorCallback< Read_implActor, 1, Reference<CacheBlock> >;
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	Read_implActor(Reference<AsyncFileReadAheadCache> const& f,void* const& data,int const& length,int64_t const& offset) 
															#line 1045 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
		 : Actor<int>(),
		   Read_implActorState<Read_implActor>(f, data, length, offset),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(14671258362208945664UL, 7416941349097520384UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("read_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Read_implActor, 0, int64_t >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Read_implActor, 1, Reference<CacheBlock> >*)0, actor_cancelled()); break;
		}

	}
};
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
[[nodiscard]] static Future<int> read_impl( Reference<AsyncFileReadAheadCache> const& f, void* const& data, int const& length, int64_t const& offset ) {
															#line 68 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"
	return Future<int>(new Read_implActor(f, data, length, offset));
															#line 1078 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.g.h"
}

#line 173 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileReadAhead.actor.h"

	Future<int> read(void* data, int length, int64_t offset) override {
		return read_impl(Reference<AsyncFileReadAheadCache>::addRef(this), data, length, offset);
	}

	Future<Void> write(void const* data, int length, int64_t offset) override { throw file_not_writable(); }
	Future<Void> truncate(int64_t size) override { throw file_not_writable(); }

	Future<Void> sync() override { return Void(); }
	Future<Void> flush() override { return Void(); }

	Future<int64_t> size() const override { return m_f->size(); }

	Future<Void> readZeroCopy(void** data, int* length, int64_t offset) override {
		TraceEvent(SevError, "ReadZeroCopyNotSupported").detail("FileType", "ReadAheadCache");
		return platform_error();
	}
	void releaseZeroCopy(void* data, int length, int64_t offset) override {}

	int64_t debugFD() const override { return -1; }

	std::string getFilename() const override { return m_f->getFilename(); }

	~AsyncFileReadAheadCache() override {
		for (auto& it : m_blocks) {
			it.second.cancel();
		}
	}

	Reference<IAsyncFile> m_f;
	int m_block_size;
	int m_read_ahead_blocks;
	int m_cache_block_limit;
	FlowLock m_max_concurrent_reads;

	// Map block numbers to future
	std::map<int, Future<Reference<CacheBlock>>> m_blocks;

	AsyncFileReadAheadCache(Reference<IAsyncFile> f,
	                        int blockSize,
	                        int readAheadBlocks,
	                        int maxConcurrentReads,
	                        int cacheSizeBlocks)
	  : m_f(f), m_block_size(blockSize), m_read_ahead_blocks(readAheadBlocks),
	    m_cache_block_limit(std::max<int>(1, cacheSizeBlocks)), m_max_concurrent_reads(maxConcurrentReads) {}
};

#include "flow/unactorcompiler.h"
#endif
