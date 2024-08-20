#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
/*
 * AsyncFileEIO.actor.h
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

#if defined(__unixish__)

#define Net2AsyncFile AsyncFileEIO

// When actually compiled (NO_INTELLISENSE), include the generated version of this file.  In intellisense use the source
// version.
#if defined(NO_INTELLISENSE) && !defined(FLOW_ASYNCFILEEIO_ACTOR_G_H)
#define FLOW_ASYNCFILEEIO_ACTOR_G_H
#include "fdbrpc/AsyncFileEIO.actor.g.h"
#elif !defined(FLOW_ASYNCFILEEIO_ACTOR_H)
#define FLOW_ASYNCFILEEIO_ACTOR_H

#include <fcntl.h>
#include <sys/stat.h>

#include "eio.h"
#include "flow/flow.h"
#include "flow/ThreadHelper.actor.h"
#include "flow/IAsyncFile.h"
#include "flow/TDMetric.actor.h"
#include "flow/actorcompiler.h" // This must be the last #include.

class AsyncFileEIO : public IAsyncFile, public ReferenceCounted<AsyncFileEIO> {

public:
	virtual StringRef getClassName() override { return "AsyncFileDetachable"_sr; }

	static void init() {
		eio_set_max_parallel(FLOW_KNOBS->EIO_MAX_PARALLELISM);
		if (eio_init(&eio_want_poll, nullptr)) {
			TraceEvent("EioInitError").detail("ErrorNo", errno);
			throw platform_error();
		}
	}

	static void stop() { eio_set_max_parallel(0); }

	static bool should_poll() { return want_poll; }

	static bool lock_fd(int fd) {
		// Acquire a "write" lock for the entire file
		struct flock lockDesc;
		lockDesc.l_type = F_WRLCK;
		lockDesc.l_whence = SEEK_SET;
		lockDesc.l_start = 0;
		lockDesc.l_len =
		    0; // "Specifying 0 for l_len has the special meaning: lock all bytes starting at the location specified by
		       // l_whence and l_start through to the end of file, no matter how large the file grows."
		lockDesc.l_pid = 0;
		if (fcntl(fd, F_SETLK, &lockDesc) == -1) {
			return false;
		}
		return true;
	}

																#line 80 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via open()
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class OpenActor>
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class OpenActorState {
															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	OpenActorState(std::string const& filename,int const& flags,int const& mode,void* const& ignore) 
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : filename(filename),
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   flags(flags),
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   mode(mode),
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   ignore(ignore)
															#line 99 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("open", reinterpret_cast<unsigned long>(this));

	}
	~OpenActorState() 
	{
		fdb_probe_actor_destroy("open", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 79 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			std::string open_filename = filename;
															#line 80 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (flags & OPEN_ATOMIC_WRITE_AND_CREATE)
															#line 116 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			{
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				ASSERT((flags & OPEN_CREATE) && (flags & OPEN_READWRITE) && !(flags & OPEN_EXCLUSIVE));
															#line 82 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				open_filename = filename + ".part";
															#line 122 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			}
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			p = Promise<Void>();
															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			r = eio_open(open_filename.c_str(), openFlags(flags), mode, 0, eio_callback, &p);
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			try {
															#line 88 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 88 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<OpenActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<OpenActor*>(this)->actor_wait_state = 1;
															#line 88 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< OpenActor, 0, Void >*>(static_cast<OpenActor*>(this)));
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~OpenActorState();
		static_cast<OpenActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 93 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result < 0)
															#line 168 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 94 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			errno = r->errorno;
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			bool notFound = errno == ENOENT;
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			Error e = notFound ? file_not_found() : io_error();
															#line 97 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			TraceEvent(notFound ? SevWarn : SevWarnAlways, "FileOpenError") .error(e) .GetLastError() .detail("File", filename) .detail("Flags", flags) .detail("Mode", mode);
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(e, loopDepth);
															#line 180 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		TraceEvent("AsyncFileOpened") .suppressFor(1.0) .detail("Filename", filename) .detail("Fd", r->result) .detail("Flags", flags);
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if ((flags & OPEN_LOCK) && !lock_fd(r->result))
															#line 186 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 112 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			TraceEvent(SevWarn, "UnableToLockFile").detail("Filename", filename).GetLastError();
															#line 113 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(lock_file_failure(), loopDepth);
															#line 192 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 116 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<OpenActor*>(this)->SAV<Reference<IAsyncFile>>::futures) { (void)(Reference<IAsyncFile>(new AsyncFileEIO(r->result, flags, filename))); this->~OpenActorState(); static_cast<OpenActor*>(this)->destroy(); return 0; }
															#line 196 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<OpenActor*>(this)->SAV< Reference<IAsyncFile> >::value()) Reference<IAsyncFile>(Reference<IAsyncFile>(new AsyncFileEIO(r->result, flags, filename)));
		this->~OpenActorState();
		static_cast<OpenActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<OpenActor*>(this)->actor_wait_state > 0) static_cast<OpenActor*>(this)->actor_wait_state = 0;
		static_cast<OpenActor*>(this)->ActorCallback< OpenActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< OpenActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("open", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<OpenActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("open", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< OpenActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("open", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<OpenActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("open", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< OpenActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("open", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<OpenActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("open", reinterpret_cast<unsigned long>(this), 0);

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
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string filename;
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int flags;
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int mode;
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	void* ignore;
															#line 85 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 333 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via open()
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class OpenActor final : public Actor<Reference<IAsyncFile>>, public ActorCallback< OpenActor, 0, Void >, public FastAllocated<OpenActor>, public OpenActorState<OpenActor> {
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<OpenActor>::operator new;
	using FastAllocated<OpenActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(4077006912302226432UL, 15761235982841856512UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Reference<IAsyncFile>>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< OpenActor, 0, Void >;
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	OpenActor(std::string const& filename,int const& flags,int const& mode,void* const& ignore) 
															#line 355 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Reference<IAsyncFile>>(),
		   OpenActorState<OpenActor>(filename, flags, mode, ignore),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("open", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(18052177269143302656UL, 9966696032264802048UL);
		ActorExecutionContextHelper __helper(static_cast<OpenActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("open");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("open", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< OpenActor, 0, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Reference<IAsyncFile>> open( std::string const& filename, int const& flags, int const& mode, void* const& ignore ) {
															#line 78 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Reference<IAsyncFile>>(new OpenActor(filename, flags, mode, ignore));
															#line 387 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 118 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	static Future<Void> deleteFile(std::string filename, bool mustBeDurable) {
		::deleteFile(filename);
		if (mustBeDurable) {
			CODE_PROBE(true, "deleteFile and fsync parent dir", probe::decoration::rare);
			return async_fsync_parent(filename);
		} else
			return Void();
	}

																#line 400 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via renameFile()
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class RenameFileActor>
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class RenameFileActorState {
															#line 406 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	RenameFileActorState(std::string const& from,std::string const& to) 
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : from(from),
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   to(to),
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_rename(from.c_str(), to.c_str(), 0, eio_callback, &p))
															#line 421 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("renameFile", reinterpret_cast<unsigned long>(this));

	}
	~RenameFileActorState() 
	{
		fdb_probe_actor_destroy("renameFile", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<RenameFileActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 439 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<RenameFileActor*>(this)->actor_wait_state = 1;
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RenameFileActor, 0, Void >*>(static_cast<RenameFileActor*>(this)));
															#line 444 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~RenameFileActorState();
		static_cast<RenameFileActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		try {
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			result = r->result;
															#line 140 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (result == -1)
															#line 476 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			{
															#line 141 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				TraceEvent(SevError, "FileRenameError").detail("Errno", r->errorno);
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				return a_body1cont1Catch1(internal_error(), loopDepth);
															#line 482 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			}
			else
			{
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<RenameFileActor*>(this)->actor_wait_state < 0) return a_body1cont1Catch1(actor_cancelled(), loopDepth);
															#line 490 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
				static_cast<RenameFileActor*>(this)->actor_wait_state = 2;
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RenameFileActor, 1, Void >*>(static_cast<RenameFileActor*>(this)));
															#line 495 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				loopDepth = 0;
			}
		}
		catch (Error& error) {
			loopDepth = a_body1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 136 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 516 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<RenameFileActor*>(this)->actor_wait_state > 0) static_cast<RenameFileActor*>(this)->actor_wait_state = 0;
		static_cast<RenameFileActor*>(this)->ActorCallback< RenameFileActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RenameFileActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 148 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			_e = e;
															#line 149 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_2 = delay(0, taskID);
															#line 149 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<RenameFileActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 635 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), loopDepth); else return a_body1cont1Catch1when1(__when_expr_2.get(), loopDepth); };
			static_cast<RenameFileActor*>(this)->actor_wait_state = 3;
															#line 149 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< RenameFileActor, 2, Void >*>(static_cast<RenameFileActor*>(this)));
															#line 640 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont7(Void const& _,int loopDepth) 
	{
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<RenameFileActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~RenameFileActorState(); static_cast<RenameFileActor*>(this)->destroy(); return 0; }
															#line 655 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<RenameFileActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~RenameFileActorState();
		static_cast<RenameFileActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont7(Void && _,int loopDepth) 
	{
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<RenameFileActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~RenameFileActorState(); static_cast<RenameFileActor*>(this)->destroy(); return 0; }
															#line 667 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<RenameFileActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~RenameFileActorState();
		static_cast<RenameFileActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont7(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont7(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RenameFileActor*>(this)->actor_wait_state > 0) static_cast<RenameFileActor*>(this)->actor_wait_state = 0;
		static_cast<RenameFileActor*>(this)->ActorCallback< RenameFileActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RenameFileActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont1Catch1cont1(Void const& _,int loopDepth) 
	{
															#line 150 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(_e, loopDepth);
															#line 754 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1cont1(Void && _,int loopDepth) 
	{
															#line 150 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(_e, loopDepth);
															#line 762 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<RenameFileActor*>(this)->actor_wait_state > 0) static_cast<RenameFileActor*>(this)->actor_wait_state = 0;
		static_cast<RenameFileActor*>(this)->ActorCallback< RenameFileActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< RenameFileActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< RenameFileActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string from;
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string to;
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int result;
															#line 148 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Error _e;
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via renameFile()
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class RenameFileActor final : public Actor<Void>, public ActorCallback< RenameFileActor, 0, Void >, public ActorCallback< RenameFileActor, 1, Void >, public ActorCallback< RenameFileActor, 2, Void >, public FastAllocated<RenameFileActor>, public RenameFileActorState<RenameFileActor> {
															#line 860 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<RenameFileActor>::operator new;
	using FastAllocated<RenameFileActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(3092033689839030528UL, 9646607625236026368UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RenameFileActor, 0, Void >;
friend struct ActorCallback< RenameFileActor, 1, Void >;
friend struct ActorCallback< RenameFileActor, 2, Void >;
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	RenameFileActor(std::string const& from,std::string const& to) 
															#line 879 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   RenameFileActorState<RenameFileActor>(from, to),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("renameFile", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(10325873508974904832UL, 1635430092948665344UL);
		ActorExecutionContextHelper __helper(static_cast<RenameFileActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("renameFile");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("renameFile", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RenameFileActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RenameFileActor, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< RenameFileActor, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> renameFile( std::string const& from, std::string const& to ) {
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new RenameFileActor(from, to));
															#line 913 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 153 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 918 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via lastWriteTime()
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class LastWriteTimeActor>
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class LastWriteTimeActorState {
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	LastWriteTimeActorState(std::string const& filename) 
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : filename(filename)
															#line 931 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("lastWriteTime", reinterpret_cast<unsigned long>(this));

	}
	~LastWriteTimeActorState() 
	{
		fdb_probe_actor_destroy("lastWriteTime", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 155 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<EIO_STRUCT_STAT> __when_expr_0 = stat_impl(filename);
															#line 155 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<LastWriteTimeActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 948 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<LastWriteTimeActor*>(this)->actor_wait_state = 1;
															#line 155 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >*>(static_cast<LastWriteTimeActor*>(this)));
															#line 953 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~LastWriteTimeActorState();
		static_cast<LastWriteTimeActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(EIO_STRUCT_STAT const& statdata,int loopDepth) 
	{
															#line 156 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<LastWriteTimeActor*>(this)->SAV<std::time_t>::futures) { (void)(statdata.st_mtime); this->~LastWriteTimeActorState(); static_cast<LastWriteTimeActor*>(this)->destroy(); return 0; }
															#line 976 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<LastWriteTimeActor*>(this)->SAV< std::time_t >::value()) std::time_t(statdata.st_mtime);
		this->~LastWriteTimeActorState();
		static_cast<LastWriteTimeActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1(EIO_STRUCT_STAT && statdata,int loopDepth) 
	{
															#line 156 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<LastWriteTimeActor*>(this)->SAV<std::time_t>::futures) { (void)(statdata.st_mtime); this->~LastWriteTimeActorState(); static_cast<LastWriteTimeActor*>(this)->destroy(); return 0; }
															#line 988 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<LastWriteTimeActor*>(this)->SAV< std::time_t >::value()) std::time_t(statdata.st_mtime);
		this->~LastWriteTimeActorState();
		static_cast<LastWriteTimeActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1when1(EIO_STRUCT_STAT const& statdata,int loopDepth) 
	{
		loopDepth = a_body1cont1(statdata, loopDepth);

		return loopDepth;
	}
	int a_body1when1(EIO_STRUCT_STAT && statdata,int loopDepth) 
	{
		loopDepth = a_body1cont1(std::move(statdata), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<LastWriteTimeActor*>(this)->actor_wait_state > 0) static_cast<LastWriteTimeActor*>(this)->actor_wait_state = 0;
		static_cast<LastWriteTimeActor*>(this)->ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >::remove();

	}
	void a_callback_fire(ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >*,EIO_STRUCT_STAT const& value) 
	{
		fdb_probe_actor_enter("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LastWriteTimeActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >*,EIO_STRUCT_STAT && value) 
	{
		fdb_probe_actor_enter("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LastWriteTimeActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >*,Error err) 
	{
		fdb_probe_actor_enter("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LastWriteTimeActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("lastWriteTime", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string filename;
															#line 1073 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via lastWriteTime()
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class LastWriteTimeActor final : public Actor<std::time_t>, public ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >, public FastAllocated<LastWriteTimeActor>, public LastWriteTimeActorState<LastWriteTimeActor> {
															#line 1078 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<LastWriteTimeActor>::operator new;
	using FastAllocated<LastWriteTimeActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17449331873573465600UL, 15311628470620419328UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<std::time_t>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >;
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	LastWriteTimeActor(std::string const& filename) 
															#line 1095 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<std::time_t>(),
		   LastWriteTimeActorState<LastWriteTimeActor>(filename),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("lastWriteTime", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(15420077433704294400UL, 1109468627602666496UL);
		ActorExecutionContextHelper __helper(static_cast<LastWriteTimeActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("lastWriteTime");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("lastWriteTime", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< LastWriteTimeActor, 0, EIO_STRUCT_STAT >*)0, actor_cancelled()); break;
		}

	}
};
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<std::time_t> lastWriteTime( std::string const& filename ) {
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<std::time_t>(new LastWriteTimeActor(filename));
															#line 1127 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 158 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	void addref() override { ReferenceCounted<AsyncFileEIO>::addref(); }
	void delref() override { ReferenceCounted<AsyncFileEIO>::delref(); }

	int64_t debugFD() const override { return fd; }

	Future<int> read(void* data, int length, int64_t offset) override {
		++countFileLogicalReads;
		++countLogicalReads;
		return read_impl(fd, data, length, offset);
	}
	Future<Void> write(void const* data, int length, int64_t offset) override // Copies data synchronously
	{
		++countFileLogicalWrites;
		++countLogicalWrites;
		// Standalone<StringRef> copy = StringRef((const uint8_t*)data, length);
		return write_impl(fd, err, StringRef((const uint8_t*)data, length), offset);
	}
	Future<Void> truncate(int64_t size) override {
		++countFileLogicalWrites;
		++countLogicalWrites;
		return truncate_impl(fd, err, size);
	}
	Future<Void> sync() override {
		++countFileLogicalWrites;
		++countLogicalWrites;
		auto fsync = sync_impl(fd, err);

		if (flags & OPEN_ATOMIC_WRITE_AND_CREATE) {
			flags &= ~OPEN_ATOMIC_WRITE_AND_CREATE;

			return waitAndAtomicRename(fsync, filename + ".part", filename);
		}

		return fsync;
	}
	Future<int64_t> size() const override {
		++countFileLogicalReads;
		++countLogicalReads;
		return size_impl(fd);
	}
	std::string getFilename() const override { return filename; }

																#line 1174 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via async_fsync_parent()
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Async_fsync_parentActor>
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Async_fsync_parentActorState {
															#line 1180 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Async_fsync_parentActorState(std::string const& filename) 
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : filename(filename)
															#line 1187 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("async_fsync_parent", reinterpret_cast<unsigned long>(this));

	}
	~Async_fsync_parentActorState() 
	{
		fdb_probe_actor_destroy("async_fsync_parent", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 202 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			std::string folder = parentDirectory(filename);
															#line 203 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			TraceEvent("FSyncParentDir").detail("Folder", folder).detail("File", filename);
															#line 204 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			folderFD = ::open(folder.c_str(), O_DIRECTORY | O_CLOEXEC, 0);
															#line 205 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (folderFD < 0)
															#line 1208 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			{
															#line 206 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				return a_body1Catch1(io_error(), loopDepth);
															#line 1212 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			}
			try {
															#line 208 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = async_fsync(folderFD);
															#line 208 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Async_fsync_parentActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 1219 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Async_fsync_parentActor*>(this)->actor_wait_state = 1;
															#line 208 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Async_fsync_parentActor, 0, Void >*>(static_cast<Async_fsync_parentActor*>(this)));
															#line 1224 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Async_fsync_parentActorState();
		static_cast<Async_fsync_parentActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 213 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		close(folderFD);
															#line 214 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Async_fsync_parentActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Async_fsync_parentActorState(); static_cast<Async_fsync_parentActor*>(this)->destroy(); return 0; }
															#line 1255 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Async_fsync_parentActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Async_fsync_parentActorState();
		static_cast<Async_fsync_parentActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 210 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			close(folderFD);
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 1270 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<Async_fsync_parentActor*>(this)->actor_wait_state > 0) static_cast<Async_fsync_parentActor*>(this)->actor_wait_state = 0;
		static_cast<Async_fsync_parentActor*>(this)->ActorCallback< Async_fsync_parentActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Async_fsync_parentActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Async_fsync_parentActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Async_fsync_parentActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Async_fsync_parentActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Async_fsync_parentActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Async_fsync_parentActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("async_fsync_parent", reinterpret_cast<unsigned long>(this), 0);

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
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string filename;
															#line 204 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int folderFD;
															#line 1384 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via async_fsync_parent()
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Async_fsync_parentActor final : public Actor<Void>, public ActorCallback< Async_fsync_parentActor, 0, Void >, public FastAllocated<Async_fsync_parentActor>, public Async_fsync_parentActorState<Async_fsync_parentActor> {
															#line 1389 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Async_fsync_parentActor>::operator new;
	using FastAllocated<Async_fsync_parentActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(9125774739611245568UL, 8163786167780248064UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Async_fsync_parentActor, 0, Void >;
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Async_fsync_parentActor(std::string const& filename) 
															#line 1406 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   Async_fsync_parentActorState<Async_fsync_parentActor>(filename),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("async_fsync_parent", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(1936605860382210048UL, 12629818433626009344UL);
		ActorExecutionContextHelper __helper(static_cast<Async_fsync_parentActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("async_fsync_parent");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("async_fsync_parent", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Async_fsync_parentActor, 0, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> async_fsync_parent( std::string const& filename ) {
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new Async_fsync_parentActor(filename));
															#line 1438 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 216 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	static Future<Void> async_fdatasync(int fd) {
		// Used by AsyncFileKAIO, since kernel AIO doesn't really implement fdatasync yet
		return sync_impl(fd, makeReference<ErrorInfo>());
	}
	static Future<Void> async_fsync(int fd) {
		// Used by AsyncFileKAIO, since kernel AIO doesn't really implement fsync yet
		return sync_impl(fd, makeReference<ErrorInfo>(), true);
	}
																#line 1451 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via waitAndAtomicRename()
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class WaitAndAtomicRenameActor>
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class WaitAndAtomicRenameActorState {
															#line 1457 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	WaitAndAtomicRenameActorState(Future<Void> const& fsync,std::string const& part_filename,std::string const& final_filename) 
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fsync(fsync),
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   part_filename(part_filename),
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   final_filename(final_filename)
															#line 1468 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("waitAndAtomicRename", reinterpret_cast<unsigned long>(this));

	}
	~WaitAndAtomicRenameActorState() 
	{
		fdb_probe_actor_destroy("waitAndAtomicRename", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 229 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_0 = fsync;
															#line 229 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1485 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state = 1;
															#line 229 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< WaitAndAtomicRenameActor, 0, Void >*>(static_cast<WaitAndAtomicRenameActor*>(this)));
															#line 1490 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~WaitAndAtomicRenameActorState();
		static_cast<WaitAndAtomicRenameActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void const& _,int loopDepth) 
	{
															#line 232 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (rename(part_filename.c_str(), final_filename.c_str()))
															#line 1513 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 233 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			TraceEvent("AsyncFileEIORenameError").detail("Filename", final_filename).GetLastError();
															#line 234 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(io_error(), loopDepth);
															#line 1519 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = async_fsync_parent(final_filename);
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1525 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state = 2;
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< WaitAndAtomicRenameActor, 1, Void >*>(static_cast<WaitAndAtomicRenameActor*>(this)));
															#line 1530 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void && _,int loopDepth) 
	{
															#line 232 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (rename(part_filename.c_str(), final_filename.c_str()))
															#line 1539 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 233 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			TraceEvent("AsyncFileEIORenameError").detail("Filename", final_filename).GetLastError();
															#line 234 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(io_error(), loopDepth);
															#line 1545 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = async_fsync_parent(final_filename);
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 1551 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state = 2;
															#line 238 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< WaitAndAtomicRenameActor, 1, Void >*>(static_cast<WaitAndAtomicRenameActor*>(this)));
															#line 1556 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

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
		if (static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state > 0) static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state = 0;
		static_cast<WaitAndAtomicRenameActor*>(this)->ActorCallback< WaitAndAtomicRenameActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< WaitAndAtomicRenameActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< WaitAndAtomicRenameActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< WaitAndAtomicRenameActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont2(Void const& _,int loopDepth) 
	{
															#line 240 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<WaitAndAtomicRenameActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~WaitAndAtomicRenameActorState(); static_cast<WaitAndAtomicRenameActor*>(this)->destroy(); return 0; }
															#line 1640 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<WaitAndAtomicRenameActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~WaitAndAtomicRenameActorState();
		static_cast<WaitAndAtomicRenameActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
															#line 240 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<WaitAndAtomicRenameActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~WaitAndAtomicRenameActorState(); static_cast<WaitAndAtomicRenameActor*>(this)->destroy(); return 0; }
															#line 1652 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<WaitAndAtomicRenameActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~WaitAndAtomicRenameActorState();
		static_cast<WaitAndAtomicRenameActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont2(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont2(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state > 0) static_cast<WaitAndAtomicRenameActor*>(this)->actor_wait_state = 0;
		static_cast<WaitAndAtomicRenameActor*>(this)->ActorCallback< WaitAndAtomicRenameActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< WaitAndAtomicRenameActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< WaitAndAtomicRenameActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< WaitAndAtomicRenameActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Future<Void> fsync;
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string part_filename;
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string final_filename;
															#line 1741 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via waitAndAtomicRename()
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class WaitAndAtomicRenameActor final : public Actor<Void>, public ActorCallback< WaitAndAtomicRenameActor, 0, Void >, public ActorCallback< WaitAndAtomicRenameActor, 1, Void >, public FastAllocated<WaitAndAtomicRenameActor>, public WaitAndAtomicRenameActorState<WaitAndAtomicRenameActor> {
															#line 1746 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<WaitAndAtomicRenameActor>::operator new;
	using FastAllocated<WaitAndAtomicRenameActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17250981288669912832UL, 1300470955598973696UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< WaitAndAtomicRenameActor, 0, Void >;
friend struct ActorCallback< WaitAndAtomicRenameActor, 1, Void >;
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	WaitAndAtomicRenameActor(Future<Void> const& fsync,std::string const& part_filename,std::string const& final_filename) 
															#line 1764 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   WaitAndAtomicRenameActorState<WaitAndAtomicRenameActor>(fsync, part_filename, final_filename),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(16072481452882551552UL, 14945215521557436672UL);
		ActorExecutionContextHelper __helper(static_cast<WaitAndAtomicRenameActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("waitAndAtomicRename");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("waitAndAtomicRename", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< WaitAndAtomicRenameActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< WaitAndAtomicRenameActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> waitAndAtomicRename( Future<Void> const& fsync, std::string const& part_filename, std::string const& final_filename ) {
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new WaitAndAtomicRenameActor(fsync, part_filename, final_filename));
															#line 1797 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 242 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	// Run the given function on the EIO thread pool and return its result
	template <class R>
	static Future<R> dispatch(std::function<R()> const& func) {
		return dispatch_impl(func);
	}

	~AsyncFileEIO() override { close_impl(fd); }

private:
	struct ErrorInfo : ReferenceCounted<ErrorInfo>, FastAllocated<ErrorInfo> {
		Error err;
		void set(const Error& e) {
			if (err.code() == invalid_error_code)
				err = e;
		}
		void report() {
			if (err.code() != invalid_error_code)
				throw err;
		}
	};

	template <class R>
	struct Dispatch {
		std::function<R()> func;
		ErrorOr<R> result;
		Promise<Void> done;
		explicit Dispatch(std::function<R()> const& func) : func(func) {}
	};

	int fd, flags;
	Reference<ErrorInfo> err;
	std::string filename;
	mutable Int64MetricHandle countFileLogicalWrites;
	mutable Int64MetricHandle countFileLogicalReads;

	mutable Int64MetricHandle countLogicalWrites;
	mutable Int64MetricHandle countLogicalReads;

	AsyncFileEIO(int fd, int flags, std::string const& filename)
	  : fd(fd), flags(flags), err(new ErrorInfo), filename(filename) {
		if (!g_network->isSimulated()) {
			countFileLogicalWrites.init("AsyncFile.CountFileLogicalWrites"_sr, filename);
			countFileLogicalReads.init("AsyncFile.CountFileLogicalReads"_sr, filename);

			countLogicalWrites.init("AsyncFile.CountLogicalWrites"_sr);
			countLogicalReads.init("AsyncFile.CountLogicalReads"_sr);
		}
	}

	static int openFlags(int flags) {
		int oflags = O_CLOEXEC;
		ASSERT(bool(flags & OPEN_READONLY) != bool(flags & OPEN_READWRITE)); // readonly xor readwrite
		if (flags & OPEN_EXCLUSIVE)
			oflags |= O_EXCL;
		if (flags & OPEN_CREATE)
			oflags |= O_CREAT;
		if (flags & OPEN_READONLY)
			oflags |= O_RDONLY;
		if (flags & OPEN_READWRITE)
			oflags |= O_RDWR;
		if (flags & OPEN_ATOMIC_WRITE_AND_CREATE)
			oflags |= O_TRUNC;
#if defined(__linux__)
		if (flags & OPEN_UNBUFFERED && FLOW_KNOBS->EIO_USE_ODIRECT)
			oflags |= O_DIRECT;
#endif
		return oflags;
	}

	static void error(const char* context,
	                  int fd,
	                  eio_req* r,
	                  Reference<ErrorInfo> const& err = Reference<ErrorInfo>()) {
		Error e = io_error();
		errno = r->errorno;
		TraceEvent(context).error(e).detail("Fd", fd).detail("Result", r->result).GetLastError();
		if (err)
			err->set(e);
		else
			throw e;
	}

																#line 1884 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via close_impl()
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Close_implActor>
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Close_implActorState {
															#line 1890 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Close_implActorState(int const& fd) 
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 326 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 327 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_close(fd, 0, eio_callback, &p))
															#line 1901 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("close_impl", reinterpret_cast<unsigned long>(this));

	}
	~Close_implActorState() 
	{
		fdb_probe_actor_destroy("close_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 328 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 328 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 1918 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			static_cast<Close_implActor*>(this)->actor_wait_state = 1;
															#line 328 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Close_implActor, 0, Void >*>(static_cast<Close_implActor*>(this)));
															#line 1922 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		delete static_cast<Close_implActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void const& _,int loopDepth) 
	{
															#line 329 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result)
															#line 1944 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 330 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("CloseError", fd, r);
															#line 1948 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 331 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		TraceEvent("AsyncFileClosed").suppressFor(1.0).detail("Fd", fd);
															#line 1952 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1cont1(Void && _,int loopDepth) 
	{
															#line 329 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result)
															#line 1961 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 330 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("CloseError", fd, r);
															#line 1965 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 331 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		TraceEvent("AsyncFileClosed").suppressFor(1.0).detail("Fd", fd);
															#line 1969 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = a_body1cont4(loopDepth);

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
		if (static_cast<Close_implActor*>(this)->actor_wait_state > 0) static_cast<Close_implActor*>(this)->actor_wait_state = 0;
		static_cast<Close_implActor*>(this)->ActorCallback< Close_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Close_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("close_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Close_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("close_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Close_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("close_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Close_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("close_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Close_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("close_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Close_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("close_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont4(int loopDepth) 
	{
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		delete static_cast<Close_implActor*>(this);
															#line 2053 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 326 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 327 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 2064 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via close_impl()
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Close_implActor final : public Actor<void>, public ActorCallback< Close_implActor, 0, Void >, public FastAllocated<Close_implActor>, public Close_implActorState<Close_implActor> {
															#line 2069 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Close_implActor>::operator new;
	using FastAllocated<Close_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17199878003761670144UL, 6333954041431110912UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< Close_implActor, 0, Void >;
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Close_implActor(int const& fd) 
															#line 2086 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<void>(),
		   Close_implActorState<Close_implActor>(fd),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("close_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(6271020131787971584UL, 6497838218989491200UL);
		ActorExecutionContextHelper __helper(static_cast<Close_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("close_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("close_impl", reinterpret_cast<unsigned long>(this), -1);

	}
};
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
static void close_impl( int const& fd ) {
															#line 325 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	new Close_implActor(fd);
															#line 2109 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 333 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 2114 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via read_impl()
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Read_implActor>
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Read_implActorState {
															#line 2120 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Read_implActorState(int const& fd,void* const& data,int const& length,int64_t const& offset) 
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   data(data),
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   length(length),
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   offset(offset),
															#line 335 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 336 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_read(fd, data, length, offset, 0, eio_callback, &p))
															#line 2139 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
			try {
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Read_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2157 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Read_implActor*>(this)->actor_wait_state = 1;
															#line 340 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Read_implActor, 0, Void >*>(static_cast<Read_implActor*>(this)));
															#line 2162 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Read_implActorState();
		static_cast<Read_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		try {
															#line 347 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			result = r->result;
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (result == -1)
															#line 2194 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			{
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				error("ReadError", fd, r);
															#line 351 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				return a_body1cont1Catch1(internal_error(), loopDepth);
															#line 2200 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			}
			else
			{
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Read_implActor*>(this)->actor_wait_state < 0) return a_body1cont1Catch1(actor_cancelled(), loopDepth);
															#line 2208 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
				static_cast<Read_implActor*>(this)->actor_wait_state = 2;
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Read_implActor, 1, Void >*>(static_cast<Read_implActor*>(this)));
															#line 2213 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				loopDepth = 0;
			}
		}
		catch (Error& error) {
			loopDepth = a_body1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 342 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 343 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 344 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 2234 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Read_implActor*>(this)->actor_wait_state > 0) static_cast<Read_implActor*>(this)->actor_wait_state = 0;
		static_cast<Read_implActor*>(this)->ActorCallback< Read_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Read_implActor, 0, Void >*,Void const& value) 
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
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Read_implActor, 0, Void >*,Void && value) 
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
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Read_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont1Catch1(const Error& _e,int loopDepth=0) 
	{
		try {
															#line 357 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			e = _e;
															#line 358 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_2 = delay(0, taskID);
															#line 358 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<Read_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 2353 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), loopDepth); else return a_body1cont1Catch1when1(__when_expr_2.get(), loopDepth); };
			static_cast<Read_implActor*>(this)->actor_wait_state = 3;
															#line 358 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< Read_implActor, 2, Void >*>(static_cast<Read_implActor*>(this)));
															#line 2358 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont7(Void const& _,int loopDepth) 
	{
															#line 354 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(result); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 2373 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(std::move(result)); // state_var_RVO
		this->~Read_implActorState();
		static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont7(Void && _,int loopDepth) 
	{
															#line 354 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Read_implActor*>(this)->SAV<int>::futures) { (void)(result); this->~Read_implActorState(); static_cast<Read_implActor*>(this)->destroy(); return 0; }
															#line 2385 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Read_implActor*>(this)->SAV< int >::value()) int(std::move(result)); // state_var_RVO
		this->~Read_implActorState();
		static_cast<Read_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont7(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont7(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Read_implActor*>(this)->actor_wait_state > 0) static_cast<Read_implActor*>(this)->actor_wait_state = 0;
		static_cast<Read_implActor*>(this)->ActorCallback< Read_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Read_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Read_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Read_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont1Catch1cont1(Void const& _,int loopDepth) 
	{
															#line 359 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(e, loopDepth);
															#line 2472 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1cont1(Void && _,int loopDepth) 
	{
															#line 359 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(e, loopDepth);
															#line 2480 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<Read_implActor*>(this)->actor_wait_state > 0) static_cast<Read_implActor*>(this)->actor_wait_state = 0;
		static_cast<Read_implActor*>(this)->ActorCallback< Read_implActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Read_implActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< Read_implActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< Read_implActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("read_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Read_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("read_impl", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	void* data;
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int length;
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int64_t offset;
															#line 335 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 336 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 338 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 347 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int result;
															#line 357 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Error e;
															#line 2577 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via read_impl()
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Read_implActor final : public Actor<int>, public ActorCallback< Read_implActor, 0, Void >, public ActorCallback< Read_implActor, 1, Void >, public ActorCallback< Read_implActor, 2, Void >, public FastAllocated<Read_implActor>, public Read_implActorState<Read_implActor> {
															#line 2582 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Read_implActor>::operator new;
	using FastAllocated<Read_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(13312174219536168704UL, 15323311850853197568UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<int>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Read_implActor, 0, Void >;
friend struct ActorCallback< Read_implActor, 1, Void >;
friend struct ActorCallback< Read_implActor, 2, Void >;
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Read_implActor(int const& fd,void* const& data,int const& length,int64_t const& offset) 
															#line 2601 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<int>(),
		   Read_implActorState<Read_implActor>(fd, data, length, offset),
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
		case 1: this->a_callback_error((ActorCallback< Read_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Read_implActor, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< Read_implActor, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<int> read_impl( int const& fd, void* const& data, int const& length, int64_t const& offset ) {
															#line 334 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<int>(new Read_implActor(fd, data, length, offset));
															#line 2635 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 362 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 2640 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via write_impl()
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Write_implActor>
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Write_implActorState {
															#line 2646 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Write_implActorState(int const& fd,Reference<ErrorInfo> const& err,StringRef const& data,int64_t const& offset) 
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   err(err),
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   data(data),
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   offset(offset),
															#line 364 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 365 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 366 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_write(fd, (void*)data.begin(), data.size(), offset, 0, eio_callback, &p))
															#line 2665 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("write_impl", reinterpret_cast<unsigned long>(this));

	}
	~Write_implActorState() 
	{
		fdb_probe_actor_destroy("write_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 368 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 368 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Write_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2683 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Write_implActor*>(this)->actor_wait_state = 1;
															#line 368 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Write_implActor, 0, Void >*>(static_cast<Write_implActor*>(this)));
															#line 2688 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Write_implActorState();
		static_cast<Write_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 374 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result != data.size())
															#line 2717 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 375 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("WriteError", fd, r, err);
															#line 2721 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 376 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 376 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<Write_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 2727 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Write_implActor*>(this)->actor_wait_state = 2;
															#line 376 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Write_implActor, 1, Void >*>(static_cast<Write_implActor*>(this)));
															#line 2732 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 370 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 371 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 372 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 2746 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Write_implActor*>(this)->actor_wait_state > 0) static_cast<Write_implActor*>(this)->actor_wait_state = 0;
		static_cast<Write_implActor*>(this)->ActorCallback< Write_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Write_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Write_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Write_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 377 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Write_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Write_implActorState(); static_cast<Write_implActor*>(this)->destroy(); return 0; }
															#line 2860 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Write_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Write_implActorState();
		static_cast<Write_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 377 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Write_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Write_implActorState(); static_cast<Write_implActor*>(this)->destroy(); return 0; }
															#line 2872 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Write_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Write_implActorState();
		static_cast<Write_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Write_implActor*>(this)->actor_wait_state > 0) static_cast<Write_implActor*>(this)->actor_wait_state = 0;
		static_cast<Write_implActor*>(this)->ActorCallback< Write_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Write_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Write_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Write_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Reference<ErrorInfo> err;
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	StringRef data;
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int64_t offset;
															#line 364 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 365 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 366 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 2969 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via write_impl()
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Write_implActor final : public Actor<Void>, public ActorCallback< Write_implActor, 0, Void >, public ActorCallback< Write_implActor, 1, Void >, public FastAllocated<Write_implActor>, public Write_implActorState<Write_implActor> {
															#line 2974 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Write_implActor>::operator new;
	using FastAllocated<Write_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(2742823152337762560UL, 12224083049495610368UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Write_implActor, 0, Void >;
friend struct ActorCallback< Write_implActor, 1, Void >;
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Write_implActor(int const& fd,Reference<ErrorInfo> const& err,StringRef const& data,int64_t const& offset) 
															#line 2992 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   Write_implActorState<Write_implActor>(fd, err, data, offset),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("write_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9097952400270967040UL, 7491439827751099648UL);
		ActorExecutionContextHelper __helper(static_cast<Write_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("write_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("write_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Write_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Write_implActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> write_impl( int const& fd, Reference<ErrorInfo> const& err, StringRef const& data, int64_t const& offset ) {
															#line 363 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new Write_implActor(fd, err, data, offset));
															#line 3025 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 379 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 3030 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via truncate_impl()
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Truncate_implActor>
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Truncate_implActorState {
															#line 3036 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Truncate_implActorState(int const& fd,Reference<ErrorInfo> const& err,int64_t const& size) 
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   err(err),
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   size(size),
															#line 381 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 382 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 383 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_ftruncate(fd, size, 0, eio_callback, &p))
															#line 3053 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("truncate_impl", reinterpret_cast<unsigned long>(this));

	}
	~Truncate_implActorState() 
	{
		fdb_probe_actor_destroy("truncate_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 385 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 385 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Truncate_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 3071 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Truncate_implActor*>(this)->actor_wait_state = 1;
															#line 385 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Truncate_implActor, 0, Void >*>(static_cast<Truncate_implActor*>(this)));
															#line 3076 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Truncate_implActorState();
		static_cast<Truncate_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 391 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result)
															#line 3105 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 392 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("TruncateError", fd, r, err);
															#line 3109 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 393 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 393 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<Truncate_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 3115 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Truncate_implActor*>(this)->actor_wait_state = 2;
															#line 393 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Truncate_implActor, 1, Void >*>(static_cast<Truncate_implActor*>(this)));
															#line 3120 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 387 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 388 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 389 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 3134 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Truncate_implActor*>(this)->actor_wait_state > 0) static_cast<Truncate_implActor*>(this)->actor_wait_state = 0;
		static_cast<Truncate_implActor*>(this)->ActorCallback< Truncate_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Truncate_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Truncate_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Truncate_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 394 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Truncate_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Truncate_implActorState(); static_cast<Truncate_implActor*>(this)->destroy(); return 0; }
															#line 3248 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Truncate_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Truncate_implActorState();
		static_cast<Truncate_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 394 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Truncate_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Truncate_implActorState(); static_cast<Truncate_implActor*>(this)->destroy(); return 0; }
															#line 3260 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Truncate_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Truncate_implActorState();
		static_cast<Truncate_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Truncate_implActor*>(this)->actor_wait_state > 0) static_cast<Truncate_implActor*>(this)->actor_wait_state = 0;
		static_cast<Truncate_implActor*>(this)->ActorCallback< Truncate_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Truncate_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Truncate_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Truncate_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Reference<ErrorInfo> err;
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int64_t size;
															#line 381 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 382 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 383 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 3355 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via truncate_impl()
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Truncate_implActor final : public Actor<Void>, public ActorCallback< Truncate_implActor, 0, Void >, public ActorCallback< Truncate_implActor, 1, Void >, public FastAllocated<Truncate_implActor>, public Truncate_implActorState<Truncate_implActor> {
															#line 3360 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Truncate_implActor>::operator new;
	using FastAllocated<Truncate_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(67888842991849216UL, 14432819653648995072UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Truncate_implActor, 0, Void >;
friend struct ActorCallback< Truncate_implActor, 1, Void >;
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Truncate_implActor(int const& fd,Reference<ErrorInfo> const& err,int64_t const& size) 
															#line 3378 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   Truncate_implActorState<Truncate_implActor>(fd, err, size),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("truncate_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(3199853103707522816UL, 8057207306250003968UL);
		ActorExecutionContextHelper __helper(static_cast<Truncate_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("truncate_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("truncate_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Truncate_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Truncate_implActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> truncate_impl( int const& fd, Reference<ErrorInfo> const& err, int64_t const& size ) {
															#line 380 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new Truncate_implActor(fd, err, size));
															#line 3411 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 396 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	static eio_req* start_fsync(int fd, Promise<Void>& p, bool sync_metadata) {
#ifdef __APPLE__
		// Neither fsync() nor fdatasync() do the right thing on OS X!
		eio_req* req = (eio_req*)calloc(1, sizeof *req);
		req->type = EIO_CUSTOM;
		req->pri = 0;
		req->finish = eio_callback;
		req->data = &p;
		req->destroy = free_req;
		req->int1 = fd;
		req->feed = apple_fsync;
		eio_submit(req);
		return req;
#else
		if (sync_metadata)
			return eio_fsync(fd, 0, eio_callback, &p);
		else
			return eio_fdatasync(fd, 0, eio_callback, &p);
#endif
	}

																#line 3437 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via sync_impl()
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Sync_implActor>
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Sync_implActorState {
															#line 3443 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Sync_implActorState(int const& fd,Reference<ErrorInfo> const& err,bool const& sync_metadata = false) 
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   err(err),
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   sync_metadata(sync_metadata),
															#line 419 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 420 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 421 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(start_fsync(fd, p, sync_metadata))
															#line 3460 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("sync_impl", reinterpret_cast<unsigned long>(this));

	}
	~Sync_implActorState() 
	{
		fdb_probe_actor_destroy("sync_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 424 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 424 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Sync_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 3478 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Sync_implActor*>(this)->actor_wait_state = 1;
															#line 424 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Sync_implActor, 0, Void >*>(static_cast<Sync_implActor*>(this)));
															#line 3483 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Sync_implActorState();
		static_cast<Sync_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
		try {
															#line 432 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			err->report();
															#line 434 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (r->result)
															#line 3515 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			{
															#line 435 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				error("SyncError", fd, r);
															#line 3519 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			}
															#line 436 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 436 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<Sync_implActor*>(this)->actor_wait_state < 0) return a_body1cont1Catch1(actor_cancelled(), loopDepth);
															#line 3525 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
			static_cast<Sync_implActor*>(this)->actor_wait_state = 2;
															#line 436 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Sync_implActor, 1, Void >*>(static_cast<Sync_implActor*>(this)));
															#line 3530 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 426 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 427 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 428 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 3550 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Sync_implActor*>(this)->actor_wait_state > 0) static_cast<Sync_implActor*>(this)->actor_wait_state = 0;
		static_cast<Sync_implActor*>(this)->ActorCallback< Sync_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Sync_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont1Catch1(const Error& _e,int loopDepth=0) 
	{
		try {
															#line 439 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			e = _e;
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			StrictFuture<Void> __when_expr_2 = delay(0, taskID);
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			if (static_cast<Sync_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 3669 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), loopDepth); else return a_body1cont1Catch1when1(__when_expr_2.get(), loopDepth); };
			static_cast<Sync_implActor*>(this)->actor_wait_state = 3;
															#line 440 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< Sync_implActor, 2, Void >*>(static_cast<Sync_implActor*>(this)));
															#line 3674 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1cont5(Void const& _,int loopDepth) 
	{
															#line 437 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Sync_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Sync_implActorState(); static_cast<Sync_implActor*>(this)->destroy(); return 0; }
															#line 3689 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Sync_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Sync_implActorState();
		static_cast<Sync_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont5(Void && _,int loopDepth) 
	{
															#line 437 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Sync_implActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~Sync_implActorState(); static_cast<Sync_implActor*>(this)->destroy(); return 0; }
															#line 3701 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Sync_implActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~Sync_implActorState();
		static_cast<Sync_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont5(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont5(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Sync_implActor*>(this)->actor_wait_state > 0) static_cast<Sync_implActor*>(this)->actor_wait_state = 0;
		static_cast<Sync_implActor*>(this)->ActorCallback< Sync_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Sync_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont1Catch1cont1(Void const& _,int loopDepth) 
	{
															#line 441 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(e, loopDepth);
															#line 3788 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1cont1(Void && _,int loopDepth) 
	{
															#line 441 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		return a_body1Catch1(e, loopDepth);
															#line 3796 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1Catch1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1Catch1cont1(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<Sync_implActor*>(this)->actor_wait_state > 0) static_cast<Sync_implActor*>(this)->actor_wait_state = 0;
		static_cast<Sync_implActor*>(this)->ActorCallback< Sync_implActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< Sync_implActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont1Catch1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< Sync_implActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Reference<ErrorInfo> err;
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	bool sync_metadata;
															#line 419 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 420 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 421 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 439 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Error e;
															#line 3889 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via sync_impl()
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Sync_implActor final : public Actor<Void>, public ActorCallback< Sync_implActor, 0, Void >, public ActorCallback< Sync_implActor, 1, Void >, public ActorCallback< Sync_implActor, 2, Void >, public FastAllocated<Sync_implActor>, public Sync_implActorState<Sync_implActor> {
															#line 3894 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Sync_implActor>::operator new;
	using FastAllocated<Sync_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(2363058769441225216UL, 6551727349109277696UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Sync_implActor, 0, Void >;
friend struct ActorCallback< Sync_implActor, 1, Void >;
friend struct ActorCallback< Sync_implActor, 2, Void >;
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Sync_implActor(int const& fd,Reference<ErrorInfo> const& err,bool const& sync_metadata = false) 
															#line 3913 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<Void>(),
		   Sync_implActorState<Sync_implActor>(fd, err, sync_metadata),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("sync_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(10886912329178930944UL, 8336431624958947328UL);
		ActorExecutionContextHelper __helper(static_cast<Sync_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("sync_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("sync_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Sync_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Sync_implActor, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< Sync_implActor, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<Void> sync_impl( int const& fd, Reference<ErrorInfo> const& err, bool const& sync_metadata = false ) {
															#line 418 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<Void>(new Sync_implActor(fd, err, sync_metadata));
															#line 3947 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 444 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 3952 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via size_impl()
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Size_implActor>
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Size_implActorState {
															#line 3958 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Size_implActorState(int const& fd) 
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : fd(fd),
															#line 446 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 447 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 448 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_fstat(fd, 0, eio_callback, &p))
															#line 3971 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("size_impl", reinterpret_cast<unsigned long>(this));

	}
	~Size_implActorState() 
	{
		fdb_probe_actor_destroy("size_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 450 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 450 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Size_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 3989 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Size_implActor*>(this)->actor_wait_state = 1;
															#line 450 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Size_implActor, 0, Void >*>(static_cast<Size_implActor*>(this)));
															#line 3994 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Size_implActorState();
		static_cast<Size_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 456 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result)
															#line 4023 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 457 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("FStatError", fd, r);
															#line 4027 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 458 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		EIO_STRUCT_STAT* statdata = (EIO_STRUCT_STAT*)r->ptr2;
															#line 459 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!statdata)
															#line 4033 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 460 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("FStatBufferError", fd, r);
															#line 4037 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 461 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		size = statdata->st_size;
															#line 462 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 462 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<Size_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4045 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Size_implActor*>(this)->actor_wait_state = 2;
															#line 462 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Size_implActor, 1, Void >*>(static_cast<Size_implActor*>(this)));
															#line 4050 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 452 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 453 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 454 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 4064 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Size_implActor*>(this)->actor_wait_state > 0) static_cast<Size_implActor*>(this)->actor_wait_state = 0;
		static_cast<Size_implActor*>(this)->ActorCallback< Size_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Size_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Size_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Size_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 463 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Size_implActor*>(this)->SAV<int64_t>::futures) { (void)(size); this->~Size_implActorState(); static_cast<Size_implActor*>(this)->destroy(); return 0; }
															#line 4178 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Size_implActor*>(this)->SAV< int64_t >::value()) int64_t(std::move(size)); // state_var_RVO
		this->~Size_implActorState();
		static_cast<Size_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 463 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Size_implActor*>(this)->SAV<int64_t>::futures) { (void)(size); this->~Size_implActorState(); static_cast<Size_implActor*>(this)->destroy(); return 0; }
															#line 4190 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Size_implActor*>(this)->SAV< int64_t >::value()) int64_t(std::move(size)); // state_var_RVO
		this->~Size_implActorState();
		static_cast<Size_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Size_implActor*>(this)->actor_wait_state > 0) static_cast<Size_implActor*>(this)->actor_wait_state = 0;
		static_cast<Size_implActor*>(this)->ActorCallback< Size_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Size_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Size_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Size_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int fd;
															#line 446 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 447 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 448 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 461 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	int64_t size;
															#line 4283 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via size_impl()
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Size_implActor final : public Actor<int64_t>, public ActorCallback< Size_implActor, 0, Void >, public ActorCallback< Size_implActor, 1, Void >, public FastAllocated<Size_implActor>, public Size_implActorState<Size_implActor> {
															#line 4288 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Size_implActor>::operator new;
	using FastAllocated<Size_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(7809643399276066048UL, 10419302747464321536UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<int64_t>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Size_implActor, 0, Void >;
friend struct ActorCallback< Size_implActor, 1, Void >;
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Size_implActor(int const& fd) 
															#line 4306 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<int64_t>(),
		   Size_implActorState<Size_implActor>(fd),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("size_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(13963998856406735616UL, 9853565154799702528UL);
		ActorExecutionContextHelper __helper(static_cast<Size_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("size_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("size_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Size_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Size_implActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<int64_t> size_impl( int const& fd ) {
															#line 445 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<int64_t>(new Size_implActor(fd));
															#line 4339 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 465 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 4344 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via stat_impl()
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Stat_implActor>
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Stat_implActorState {
															#line 4350 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Stat_implActorState(std::string const& filename) 
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : filename(filename),
															#line 467 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 468 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   p(),
															#line 469 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   statdata(),
															#line 470 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_stat(filename.c_str(), 0, eio_callback, &p))
															#line 4365 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("stat_impl", reinterpret_cast<unsigned long>(this));

	}
	~Stat_implActorState() 
	{
		fdb_probe_actor_destroy("stat_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 472 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = p.getFuture();
															#line 472 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Stat_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 4383 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Stat_implActor*>(this)->actor_wait_state = 1;
															#line 472 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Stat_implActor, 0, Void >*>(static_cast<Stat_implActor*>(this)));
															#line 4388 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Stat_implActorState();
		static_cast<Stat_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 478 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (r->result)
															#line 4417 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 479 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("StatError", 0, r);
															#line 4421 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 480 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!r->ptr2)
															#line 4425 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 481 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			error("StatBufferError", 0, r);
															#line 4429 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 482 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		statdata = *EIO_STAT_BUF(r);
															#line 483 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 483 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<Stat_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4437 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Stat_implActor*>(this)->actor_wait_state = 2;
															#line 483 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Stat_implActor, 1, Void >*>(static_cast<Stat_implActor*>(this)));
															#line 4442 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 474 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 475 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 476 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 4456 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Stat_implActor*>(this)->actor_wait_state > 0) static_cast<Stat_implActor*>(this)->actor_wait_state = 0;
		static_cast<Stat_implActor*>(this)->ActorCallback< Stat_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Stat_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Stat_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Stat_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 484 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Stat_implActor*>(this)->SAV<EIO_STRUCT_STAT>::futures) { (void)(statdata); this->~Stat_implActorState(); static_cast<Stat_implActor*>(this)->destroy(); return 0; }
															#line 4570 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Stat_implActor*>(this)->SAV< EIO_STRUCT_STAT >::value()) EIO_STRUCT_STAT(std::move(statdata)); // state_var_RVO
		this->~Stat_implActorState();
		static_cast<Stat_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 484 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Stat_implActor*>(this)->SAV<EIO_STRUCT_STAT>::futures) { (void)(statdata); this->~Stat_implActorState(); static_cast<Stat_implActor*>(this)->destroy(); return 0; }
															#line 4582 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Stat_implActor*>(this)->SAV< EIO_STRUCT_STAT >::value()) EIO_STRUCT_STAT(std::move(statdata)); // state_var_RVO
		this->~Stat_implActorState();
		static_cast<Stat_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Stat_implActor*>(this)->actor_wait_state > 0) static_cast<Stat_implActor*>(this)->actor_wait_state = 0;
		static_cast<Stat_implActor*>(this)->ActorCallback< Stat_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Stat_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Stat_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Stat_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::string filename;
															#line 467 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 468 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Promise<Void> p;
															#line 469 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	EIO_STRUCT_STAT statdata;
															#line 470 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 4675 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via stat_impl()
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Stat_implActor final : public Actor<EIO_STRUCT_STAT>, public ActorCallback< Stat_implActor, 0, Void >, public ActorCallback< Stat_implActor, 1, Void >, public FastAllocated<Stat_implActor>, public Stat_implActorState<Stat_implActor> {
															#line 4680 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Stat_implActor>::operator new;
	using FastAllocated<Stat_implActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(1882620417012950272UL, 16552226181567399424UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<EIO_STRUCT_STAT>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Stat_implActor, 0, Void >;
friend struct ActorCallback< Stat_implActor, 1, Void >;
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Stat_implActor(std::string const& filename) 
															#line 4698 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<EIO_STRUCT_STAT>(),
		   Stat_implActorState<Stat_implActor>(filename),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("stat_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(12528077674310728704UL, 17290640926637803520UL);
		ActorExecutionContextHelper __helper(static_cast<Stat_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("stat_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("stat_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Stat_implActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Stat_implActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<EIO_STRUCT_STAT> stat_impl( std::string const& filename ) {
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<EIO_STRUCT_STAT>(new Stat_implActor(filename));
															#line 4731 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 486 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

																#line 4736 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via dispatch_impl()
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class R, class Dispatch_implActor>
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Dispatch_implActorState {
															#line 4742 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Dispatch_implActorState(std::function<R()> const& func) 
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		 : func(func),
															#line 489 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   data(func),
															#line 490 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   taskID(g_network->getCurrentTask()),
															#line 492 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		   r(eio_custom( [](eio_req* req) { auto data = reinterpret_cast<Dispatch<R>*>(req->data); try { data->result = data->func(); req->result = 0; } catch (Error& e) { data->result = e; req->result = -1; } catch (...) { data->result = unknown_error(); req->result = -1; } }, 0, [](eio_req* req) { if (EIO_CANCELLED(req)) return 0; auto data = reinterpret_cast<Dispatch<R>*>(req->data); Promise<Void> p = std::move(data->done); p.send(Void()); return 0; }, &data))
															#line 4755 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
	{
		fdb_probe_actor_create("dispatch_impl", reinterpret_cast<unsigned long>(this));

	}
	~Dispatch_implActorState() 
	{
		fdb_probe_actor_destroy("dispatch_impl", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
			try {
															#line 519 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				StrictFuture<Void> __when_expr_0 = data.done.getFuture();
															#line 519 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				if (static_cast<Dispatch_implActor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 4773 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
				static_cast<Dispatch_implActor*>(this)->actor_wait_state = 1;
															#line 519 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Dispatch_implActor, 0, Void >*>(static_cast<Dispatch_implActor*>(this)));
															#line 4778 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		this->~Dispatch_implActorState();
		static_cast<Dispatch_implActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 526 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, taskID);
															#line 526 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (static_cast<Dispatch_implActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 4809 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1cont1when1(__when_expr_1.get(), loopDepth); };
		static_cast<Dispatch_implActor*>(this)->actor_wait_state = 2;
															#line 526 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< Dispatch_implActor, 1, Void >*>(static_cast<Dispatch_implActor*>(this)));
															#line 4814 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& __current_error,int loopDepth=0) 
	{
		try {
															#line 521 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			g_network->setCurrentTask(taskID);
															#line 522 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			eio_cancel(r);
															#line 523 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(__current_error, loopDepth);
															#line 4828 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		loopDepth = a_body1cont3(loopDepth);

		return loopDepth;
	}
	int a_body1cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont3(loopDepth);

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
		if (static_cast<Dispatch_implActor*>(this)->actor_wait_state > 0) static_cast<Dispatch_implActor*>(this)->actor_wait_state = 0;
		static_cast<Dispatch_implActor*>(this)->ActorCallback< Dispatch_implActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Dispatch_implActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Dispatch_implActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Dispatch_implActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 0);

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
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 527 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (data.result.isError())
															#line 4942 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 528 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(data.result.getError(), loopDepth);
															#line 4946 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 529 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Dispatch_implActor*>(this)->SAV<R>::futures) { (void)(data.result.get()); this->~Dispatch_implActorState(); static_cast<Dispatch_implActor*>(this)->destroy(); return 0; }
															#line 4950 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Dispatch_implActor*>(this)->SAV< R >::value()) R(data.result.get());
		this->~Dispatch_implActorState();
		static_cast<Dispatch_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 527 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (data.result.isError())
															#line 4962 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
															#line 528 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			return a_body1Catch1(data.result.getError(), loopDepth);
															#line 4966 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		}
															#line 529 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!static_cast<Dispatch_implActor*>(this)->SAV<R>::futures) { (void)(data.result.get()); this->~Dispatch_implActorState(); static_cast<Dispatch_implActor*>(this)->destroy(); return 0; }
															#line 4970 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		new (&static_cast<Dispatch_implActor*>(this)->SAV< R >::value()) R(data.result.get());
		this->~Dispatch_implActorState();
		static_cast<Dispatch_implActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<Dispatch_implActor*>(this)->actor_wait_state > 0) static_cast<Dispatch_implActor*>(this)->actor_wait_state = 0;
		static_cast<Dispatch_implActor*>(this)->ActorCallback< Dispatch_implActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Dispatch_implActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< Dispatch_implActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< Dispatch_implActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	std::function<R()> func;
															#line 489 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Dispatch<R> data;
															#line 490 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	TaskPriority taskID;
															#line 492 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	eio_req* r;
															#line 5061 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
};
// This generated class is to be used only via dispatch_impl()
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class R>
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Dispatch_implActor final : public Actor<R>, public ActorCallback< Dispatch_implActor<R>, 0, Void >, public ActorCallback< Dispatch_implActor<R>, 1, Void >, public FastAllocated<Dispatch_implActor<R>>, public Dispatch_implActorState<R, Dispatch_implActor<R>> {
															#line 5068 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Dispatch_implActor<R>>::operator new;
	using FastAllocated<Dispatch_implActor<R>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(4354953553492963328UL, 3026836115753423104UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<R>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< Dispatch_implActor<R>, 0, Void >;
friend struct ActorCallback< Dispatch_implActor<R>, 1, Void >;
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Dispatch_implActor(std::function<R()> const& func) 
															#line 5086 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<R>(),
		   Dispatch_implActorState<R, Dispatch_implActor<R>>(func),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("dispatch_impl", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(13154703477795427840UL, 11301453103480774912UL);
		ActorExecutionContextHelper __helper(static_cast<Dispatch_implActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("dispatch_impl");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("dispatch_impl", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< Dispatch_implActor<R>, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< Dispatch_implActor<R>, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class R>
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
[[nodiscard]] static Future<R> dispatch_impl( std::function<R()> const& func ) {
															#line 487 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	return Future<R>(new Dispatch_implActor<R>(func));
															#line 5121 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	static std::atomic<int32_t> want_poll;

																#line 5128 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
// This generated class is to be used only via poll_eio()
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
template <class Poll_eioActor>
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Poll_eioActorState {
															#line 5134 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Poll_eioActorState() 
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	{
															#line 5140 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		fdb_probe_actor_create("poll_eio", reinterpret_cast<unsigned long>(this));

	}
	~Poll_eioActorState() 
	{
		fdb_probe_actor_destroy("poll_eio", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 535 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
			;
															#line 5154 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
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
		delete static_cast<Poll_eioActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 537 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		want_poll = 0;
															#line 5176 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = a_body1cont3(loopDepth);

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
															#line 535 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (!(eio_poll() == -1))
															#line 5192 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		StrictFuture<Void> __when_expr_0 = yield();
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
															#line 5200 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		static_cast<Poll_eioActor*>(this)->actor_wait_state = 1;
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< Poll_eioActor, 0, Void >*>(static_cast<Poll_eioActor*>(this)));
															#line 5204 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		loopDepth = 0;

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
	int a_body1loopBody1cont1(Void const& _,int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont1(Void && _,int loopDepth) 
	{
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
		if (static_cast<Poll_eioActor*>(this)->actor_wait_state > 0) static_cast<Poll_eioActor*>(this)->actor_wait_state = 0;
		static_cast<Poll_eioActor*>(this)->ActorCallback< Poll_eioActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< Poll_eioActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("poll_eio", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Poll_eioActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll_eio", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< Poll_eioActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("poll_eio", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<Poll_eioActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll_eio", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< Poll_eioActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("poll_eio", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<Poll_eioActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll_eio", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont3(int loopDepth) 
	{
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
		delete static_cast<Poll_eioActor*>(this);
															#line 5313 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		return 0;

		return loopDepth;
	}
};
// This generated class is to be used only via poll_eio()
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
class Poll_eioActor final : public Actor<void>, public ActorCallback< Poll_eioActor, 0, Void >, public FastAllocated<Poll_eioActor>, public Poll_eioActorState<Poll_eioActor> {
															#line 5322 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
public:
	using FastAllocated<Poll_eioActor>::operator new;
	using FastAllocated<Poll_eioActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17101149272843743744UL, 13628116299282784000UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< Poll_eioActor, 0, Void >;
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	Poll_eioActor() 
															#line 5339 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
		 : Actor<void>(),
		   Poll_eioActorState<Poll_eioActor>(),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("poll_eio", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(10018161409103912192UL, 14017243007186177024UL);
		ActorExecutionContextHelper __helper(static_cast<Poll_eioActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("poll_eio");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("poll_eio", reinterpret_cast<unsigned long>(this), -1);

	}
};
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
static void poll_eio(  ) {
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"
	new Poll_eioActor();
															#line 5362 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.g.h"
}

#line 539 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileEIO.actor.h"

	static void eio_want_poll() {
		want_poll = 1;
		// SOMEDAY: nullptr for deferred error, no analysis of correctness (itp)
		onMainThreadVoid([]() { poll_eio(); }, TaskPriority::PollEIO);
	}

	static int eio_callback(eio_req* req) {
		if (EIO_CANCELLED(req))
			return 0;
		Promise<Void> p = std::move(*(Promise<Void>*)req->data);
		p.send(Void());
		return 0;
	}

#ifdef __APPLE__
	static void apple_fsync(eio_req* req) { req->result = fcntl(req->int1, F_FULLFSYNC, 0); }
	static void free_req(eio_req* req) { free(req); }
#endif
};

#ifdef FILESYSTEM_IMPL
std::atomic<int32_t> AsyncFileEIO::want_poll = 0;
#endif

#include "flow/unactorcompiler.h"
#endif
#endif
