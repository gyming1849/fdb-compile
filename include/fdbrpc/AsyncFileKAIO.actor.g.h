#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
/*
 * AsyncFileKAIO.actor.h
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
#ifdef __linux__

// When actually compiled (NO_INTELLISENSE), include the generated version of this file.  In intellisense use the source
// version.
#if defined(NO_INTELLISENSE) && !defined(FLOW_ASYNCFILEKAIO_ACTOR_G_H)
#define FLOW_ASYNCFILEKAIO_ACTOR_G_H
#include "fdbrpc/AsyncFileKAIO.actor.g.h"
#elif !defined(FLOW_ASYNCFILEKAIO_ACTOR_H)
#define FLOW_ASYNCFILEKAIO_ACTOR_H

#include "flow/IAsyncFile.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include "fdbrpc/linux_kaio.h"
#include "flow/Knobs.h"
#include "fdbrpc/Stats.h"
#include "flow/UnitTest.h"
#include "crc32/crc32c.h"
#include "flow/genericactors.actor.h"
#include "flow/actorcompiler.h" // This must be the last #include.

// Set this to true to enable detailed KAIO request logging, which currently is written to a hardcoded location
// /data/v7/fdb/
#define KAIO_LOGGING 0

template<> struct Descriptor<struct SlowAioSubmit> {
	static StringRef typeName() { return "SlowAioSubmit"_sr; }
	typedef SlowAioSubmit type;
	struct submitDurationDescriptor {
		static StringRef name() { return "submitDuration"_sr; }
		static StringRef typeName() { return "int64_t"_sr; }
		static StringRef comment() { return " ns"_sr; }
		typedef int64_t type;
		static inline type get(SlowAioSubmit& from);
	};
	struct truncateDurationDescriptor {
		static StringRef name() { return "truncateDuration"_sr; }
		static StringRef typeName() { return "int64_t"_sr; }
		static StringRef comment() { return " ns"_sr; }
		typedef int64_t type;
		static inline type get(SlowAioSubmit& from);
	};
	struct numTruncatesDescriptor {
		static StringRef name() { return "numTruncates"_sr; }
		static StringRef typeName() { return "int64_t"_sr; }
		static StringRef comment() { return ""_sr; }
		typedef int64_t type;
		static inline type get(SlowAioSubmit& from);
	};
	struct truncateBytesDescriptor {
		static StringRef name() { return "truncateBytes"_sr; }
		static StringRef typeName() { return "int64_t"_sr; }
		static StringRef comment() { return ""_sr; }
		typedef int64_t type;
		static inline type get(SlowAioSubmit& from);
	};
	struct largestTruncateDescriptor {
		static StringRef name() { return "largestTruncate"_sr; }
		static StringRef typeName() { return "int64_t"_sr; }
		static StringRef comment() { return ""_sr; }
		typedef int64_t type;
		static inline type get(SlowAioSubmit& from);
	};
	typedef std::tuple<submitDurationDescriptor,truncateDurationDescriptor,numTruncatesDescriptor,truncateBytesDescriptor,largestTruncateDescriptor> fields;
	typedef make_index_sequence_impl<0, index_sequence<>, std::tuple_size<fields>::value>::type field_indexes;
};
struct SlowAioSubmit {
	int64_t submitDuration; // ns
	int64_t truncateDuration; // ns
	int64_t numTruncates; //
	int64_t truncateBytes; //
	int64_t largestTruncate; //
};
int64_t Descriptor<SlowAioSubmit>::submitDurationDescriptor::get(SlowAioSubmit& from) { return from.submitDuration; }
int64_t Descriptor<SlowAioSubmit>::truncateDurationDescriptor::get(SlowAioSubmit& from) { return from.truncateDuration; }
int64_t Descriptor<SlowAioSubmit>::numTruncatesDescriptor::get(SlowAioSubmit& from) { return from.numTruncates; }
int64_t Descriptor<SlowAioSubmit>::truncateBytesDescriptor::get(SlowAioSubmit& from) { return from.truncateBytes; }
int64_t Descriptor<SlowAioSubmit>::largestTruncateDescriptor::get(SlowAioSubmit& from) { return from.largestTruncate; }
#line 57 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"


class AsyncFileKAIO final : public IAsyncFile, public ReferenceCounted<AsyncFileKAIO> {
public:
	virtual StringRef getClassName() override { return "AsyncFileKAIO"_sr; }

	struct AsyncFileKAIOMetrics {
		LatencySample readLatencySample = { "AsyncFileKAIOReadLatency",
			                                UID(),
			                                FLOW_KNOBS->KAIO_LATENCY_LOGGING_INTERVAL,
			                                FLOW_KNOBS->KAIO_LATENCY_SKETCH_ACCURACY };
		LatencySample writeLatencySample = { "AsyncFileKAIOWriteLatency",
			                                 UID(),
			                                 FLOW_KNOBS->KAIO_LATENCY_LOGGING_INTERVAL,
			                                 FLOW_KNOBS->KAIO_LATENCY_SKETCH_ACCURACY };
		LatencySample syncLatencySample = { "AsyncFileKAIOSyncLatency",
			                                UID(),
			                                FLOW_KNOBS->KAIO_LATENCY_LOGGING_INTERVAL,
			                                FLOW_KNOBS->KAIO_LATENCY_SKETCH_ACCURACY };
	};

	static AsyncFileKAIOMetrics& getMetrics() {
		static AsyncFileKAIOMetrics metrics;
		return metrics;
	}

#if KAIO_LOGGING
private:
#pragma pack(push, 1)
	struct OpLogEntry {
		OpLogEntry() : result(0) {}
		enum EOperation{ READ = 1, WRITE = 2, SYNC = 3, TRUNCATE = 4 };
		enum EStage{ START = 1, LAUNCH = 2, REQUEUE = 3, COMPLETE = 4, READY = 5 };
		int64_t timestamp;
		uint32_t id;
		uint32_t checksum;
		uint32_t pageOffset;
		uint8_t pageCount;
		uint8_t op;
		uint8_t stage;
		uint32_t result;

		static uint32_t nextID() {
			static uint32_t last = 0;
			return ++last;
		}

		void log(FILE* file) {
			if (ftell(file) > (int64_t)50 * 1e9)
				fseek(file, 0, SEEK_SET);
			if (!fwrite(this, sizeof(OpLogEntry), 1, file))
				throw io_error();
		}
	};
#pragma pop

	FILE* logFile;
	struct IOBlock;
	static void KAIOLogBlockEvent(IOBlock* ioblock, OpLogEntry::EStage stage, uint32_t result = 0);
	static void KAIOLogBlockEvent(FILE* logFile, IOBlock* ioblock, OpLogEntry::EStage stage, uint32_t result = 0);
	static void KAIOLogEvent(FILE* logFile,
	                         uint32_t id,
	                         OpLogEntry::EOperation op,
	                         OpLogEntry::EStage stage,
	                         uint32_t pageOffset = 0,
	                         uint32_t result = 0);

public:
#else
#define KAIOLogBlockEvent(...)
#define KAIOLogEvent(...)
#endif

	static Future<Reference<IAsyncFile>> open(std::string filename, int flags, int mode, void* ignore) {
		ASSERT(!FLOW_KNOBS->DISABLE_POSIX_KERNEL_AIO);
		ASSERT(flags & OPEN_UNBUFFERED);

		if (flags & OPEN_LOCK)
			mode |= 02000; // Enable mandatory locking for this file if it is supported by the filesystem

		std::string open_filename = filename;
		if (flags & OPEN_ATOMIC_WRITE_AND_CREATE) {
			ASSERT((flags & OPEN_CREATE) && (flags & OPEN_READWRITE) && !(flags & OPEN_EXCLUSIVE));
			open_filename = filename + ".part";
		}

		int fd = ::open(open_filename.c_str(), openFlags(flags), mode);
		if (fd < 0) {
			Error e = errno == ENOENT ? file_not_found() : io_error();
			int ecode = errno; // Save errno in case it is modified before it is used below
			TraceEvent ev("AsyncFileKAIOOpenFailed");
			ev.error(e)
			    .detail("Filename", filename)
			    .detailf("Flags", "%x", flags)
			    .detailf("OSFlags", "%x", openFlags(flags))
			    .detailf("Mode", "0%o", mode)
			    .GetLastError();
			if (ecode == EINVAL)
				ev.detail("Description", "Invalid argument - Does the target filesystem support KAIO?");
			return e;
		} else {
			TraceEvent("AsyncFileKAIOOpen")
			    .detail("Filename", filename)
			    .detail("Flags", flags)
			    .detail("Mode", mode)
			    .detail("Fd", fd);
		}

		Reference<AsyncFileKAIO> r(new AsyncFileKAIO(fd, flags, filename));

		if (flags & OPEN_LOCK) {
			// Acquire a "write" lock for the entire file
			flock lockDesc;
			lockDesc.l_type = F_WRLCK;
			lockDesc.l_whence = SEEK_SET;
			lockDesc.l_start = 0;
			lockDesc.l_len =
			    0; // "Specifying 0 for l_len has the special meaning: lock all bytes starting at the location specified
			       // by l_whence and l_start through to the end of file, no matter how large the file grows."
			lockDesc.l_pid = 0;
			if (fcntl(fd, F_SETLK, &lockDesc) == -1) {
				TraceEvent(SevWarn, "UnableToLockFile").detail("Filename", filename).GetLastError();
				return lock_file_failure();
			}
		}

		struct stat buf;
		if (fstat(fd, &buf)) {
			TraceEvent("AsyncFileKAIOFStatError").detail("Fd", fd).detail("Filename", filename).GetLastError();
			return io_error();
		}

		r->lastFileSize = r->nextFileSize = buf.st_size;
		return Reference<IAsyncFile>(std::move(r));
	}

	static void init(Reference<IEventFD> ev, double ioTimeout) {
		ASSERT(!FLOW_KNOBS->DISABLE_POSIX_KERNEL_AIO);
		if (!g_network->isSimulated()) {
			ctx.countAIOSubmit.init("AsyncFile.CountAIOSubmit"_sr);
			ctx.countAIOCollect.init("AsyncFile.CountAIOCollect"_sr);
			ctx.submitMetric.init("AsyncFile.Submit"_sr);
			ctx.countPreSubmitTruncate.init("AsyncFile.CountPreAIOSubmitTruncate"_sr);
			ctx.preSubmitTruncateBytes.init("AsyncFile.PreAIOSubmitTruncateBytes"_sr);
			ctx.slowAioSubmitMetric.init("AsyncFile.SlowAIOSubmit"_sr);
		}

		int rc = io_setup(FLOW_KNOBS->MAX_OUTSTANDING, &ctx.iocx);
		if (rc < 0) {
			TraceEvent("IOSetupError").GetLastError();
			throw io_error();
		}
		setTimeout(ioTimeout);
		ctx.evfd = ev->getFD();
		poll(ev);

		g_network->setGlobal(INetwork::enRunCycleFunc, (flowGlobalType)&AsyncFileKAIO::launch);
	}

	static int get_eventfd() { return ctx.evfd; }
	static void setTimeout(double ioTimeout) { ctx.setIOTimeout(ioTimeout); }

	void addref() override { ReferenceCounted<AsyncFileKAIO>::addref(); }
	void delref() override { ReferenceCounted<AsyncFileKAIO>::delref(); }
	Future<int> read(void* data, int length, int64_t offset) override {
		++countFileLogicalReads;
		++countLogicalReads;
		// printf("%p Begin logical read\n", getCurrentCoro());

		if (failed) {
			return io_timeout();
		}

		IOBlock* io = new IOBlock(IO_CMD_PREAD, fd);
		io->buf = data;
		io->nbytes = length;
		io->offset = offset;

		enqueue(io, "read", this);
		Future<int> result = io->result.getFuture();

#if KAIO_LOGGING
		// result = map(result, [=](int r) mutable { KAIOLogBlockEvent(io, OpLogEntry::READY, r); return r; });
#endif

		return result;
	}
	Future<Void> write(void const* data, int length, int64_t offset) override {
		++countFileLogicalWrites;
		++countLogicalWrites;
		// printf("%p Begin logical write\n", getCurrentCoro());

		if (failed) {
			return io_timeout();
		}

		IOBlock* io = new IOBlock(IO_CMD_PWRITE, fd);
		io->buf = (void*)data;
		io->nbytes = length;
		io->offset = offset;

		nextFileSize = std::max(nextFileSize, offset + length);

		enqueue(io, "write", this);
		Future<int> result = io->result.getFuture();

#if KAIO_LOGGING
		// result = map(result, [=](int r) mutable { KAIOLogBlockEvent(io, OpLogEntry::READY, r); return r; });
#endif

		// auto& actorLineageSet = IAsyncFileSystem::filesystem()->getActorLineageSet();
		// auto index = actorLineageSet.insert(*currentLineage);
		// ASSERT(index != ActorLineageSet::npos);
		Future<Void> res = success(result);
		// actorLineageSet.erase(index);
		return res;
	}
// TODO(alexmiller): Remove when we upgrade the dev docker image to >14.10
#ifndef FALLOC_FL_ZERO_RANGE
#define FALLOC_FL_ZERO_RANGE 0x10
#endif
	Future<Void> zeroRange(int64_t offset, int64_t length) override {
		bool success = false;
		if (ctx.fallocateZeroSupported) {
			int rc = fallocate(fd, FALLOC_FL_ZERO_RANGE, offset, length);
			if (rc == EOPNOTSUPP) {
				ctx.fallocateZeroSupported = false;
			}
			if (rc == 0) {
				success = true;
			}
		}
		return success ? Void() : IAsyncFile::zeroRange(offset, length);
	}
	Future<Void> truncate(int64_t size) override {
		++countFileLogicalWrites;
		++countLogicalWrites;

		if (failed) {
			return io_timeout();
		}

#if KAIO_LOGGING
		uint32_t id = OpLogEntry::nextID();
#endif
		int result = -1;
		KAIOLogEvent(logFile, id, OpLogEntry::TRUNCATE, OpLogEntry::START, size / 4096);
		bool completed = false;
		double begin = timer_monotonic();

		if (ctx.fallocateSupported && size >= lastFileSize) {
			result = fallocate(fd, 0, 0, size);
			if (result != 0) {
				int fallocateErrCode = errno;
				TraceEvent("AsyncFileKAIOAllocateError")
				    .detail("Fd", fd)
				    .detail("Filename", filename)
				    .detail("Size", size)
				    .GetLastError();
				if (fallocateErrCode == EOPNOTSUPP) {
					// Mark fallocate as unsupported. Try again with truncate.
					ctx.fallocateSupported = false;
				} else {
					KAIOLogEvent(logFile, id, OpLogEntry::TRUNCATE, OpLogEntry::COMPLETE, size / 4096, result);
					return io_error();
				}
			} else {
				completed = true;
			}
		}
		if (!completed)
			result = ftruncate(fd, size);

		double end = timer_monotonic();
		if (nondeterministicRandom()->random01() < end - begin) {
			TraceEvent("SlowKAIOTruncate")
			    .detail("TruncateTime", end - begin)
			    .detail("TruncateBytes", size - lastFileSize);
		}
		KAIOLogEvent(logFile, id, OpLogEntry::TRUNCATE, OpLogEntry::COMPLETE, size / 4096, result);

		if (result != 0) {
			TraceEvent("AsyncFileKAIOTruncateError").detail("Fd", fd).detail("Filename", filename).GetLastError();
			return io_error();
		}

		lastFileSize = nextFileSize = size;

		return Void();
	}

																#line 398 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
// This generated class is to be used only via throwErrorIfFailed()
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
template <class ThrowErrorIfFailedActor>
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class ThrowErrorIfFailedActorState {
															#line 404 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	ThrowErrorIfFailedActorState(Reference<AsyncFileKAIO> const& self,Future<Void> const& sync) 
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		 : self(self),
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   sync(sync)
															#line 413 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
	{
		fdb_probe_actor_create("throwErrorIfFailed", reinterpret_cast<unsigned long>(this));

	}
	~ThrowErrorIfFailedActorState() 
	{
		fdb_probe_actor_destroy("throwErrorIfFailed", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			StrictFuture<Void> __when_expr_0 = sync;
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (static_cast<ThrowErrorIfFailedActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 430 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
			static_cast<ThrowErrorIfFailedActor*>(this)->actor_wait_state = 1;
															#line 349 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< ThrowErrorIfFailedActor, 0, Void >*>(static_cast<ThrowErrorIfFailedActor*>(this)));
															#line 435 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
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
		this->~ThrowErrorIfFailedActorState();
		static_cast<ThrowErrorIfFailedActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void const& _,int loopDepth) 
	{
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (self->failed)
															#line 458 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 351 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			return a_body1Catch1(io_timeout(), loopDepth);
															#line 462 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!static_cast<ThrowErrorIfFailedActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~ThrowErrorIfFailedActorState(); static_cast<ThrowErrorIfFailedActor*>(this)->destroy(); return 0; }
															#line 466 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		new (&static_cast<ThrowErrorIfFailedActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~ThrowErrorIfFailedActorState();
		static_cast<ThrowErrorIfFailedActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont1(Void && _,int loopDepth) 
	{
															#line 350 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (self->failed)
															#line 478 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 351 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			return a_body1Catch1(io_timeout(), loopDepth);
															#line 482 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 353 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!static_cast<ThrowErrorIfFailedActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~ThrowErrorIfFailedActorState(); static_cast<ThrowErrorIfFailedActor*>(this)->destroy(); return 0; }
															#line 486 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		new (&static_cast<ThrowErrorIfFailedActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~ThrowErrorIfFailedActorState();
		static_cast<ThrowErrorIfFailedActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

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
		if (static_cast<ThrowErrorIfFailedActor*>(this)->actor_wait_state > 0) static_cast<ThrowErrorIfFailedActor*>(this)->actor_wait_state = 0;
		static_cast<ThrowErrorIfFailedActor*>(this)->ActorCallback< ThrowErrorIfFailedActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< ThrowErrorIfFailedActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ThrowErrorIfFailedActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< ThrowErrorIfFailedActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<ThrowErrorIfFailedActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< ThrowErrorIfFailedActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<ThrowErrorIfFailedActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), 0);

	}
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Reference<AsyncFileKAIO> self;
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Future<Void> sync;
															#line 573 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
};
// This generated class is to be used only via throwErrorIfFailed()
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class ThrowErrorIfFailedActor final : public Actor<Void>, public ActorCallback< ThrowErrorIfFailedActor, 0, Void >, public FastAllocated<ThrowErrorIfFailedActor>, public ThrowErrorIfFailedActorState<ThrowErrorIfFailedActor> {
															#line 578 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
	using FastAllocated<ThrowErrorIfFailedActor>::operator new;
	using FastAllocated<ThrowErrorIfFailedActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(2980099400130720000UL, 15267606292230944512UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< ThrowErrorIfFailedActor, 0, Void >;
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	ThrowErrorIfFailedActor(Reference<AsyncFileKAIO> const& self,Future<Void> const& sync) 
															#line 595 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		 : Actor<Void>(),
		   ThrowErrorIfFailedActorState<ThrowErrorIfFailedActor>(self, sync),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(2179313009156488448UL, 17446081094529194496UL);
		ActorExecutionContextHelper __helper(static_cast<ThrowErrorIfFailedActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("throwErrorIfFailed");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("throwErrorIfFailed", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< ThrowErrorIfFailedActor, 0, Void >*)0, actor_cancelled()); break;
		}

	}
};
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
[[nodiscard]] static Future<Void> throwErrorIfFailed( Reference<AsyncFileKAIO> const& self, Future<Void> const& sync ) {
															#line 348 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	return Future<Void>(new ThrowErrorIfFailedActor(self, sync));
															#line 627 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
}

#line 355 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"

	Future<Void> sync() override {
		++countFileLogicalWrites;
		++countLogicalWrites;

		if (failed) {
			return io_timeout();
		}

#if KAIO_LOGGING
		uint32_t id = OpLogEntry::nextID();
#endif

		KAIOLogEvent(logFile, id, OpLogEntry::SYNC, OpLogEntry::START);
		double start_time = timer();

		Future<Void> fsync = throwErrorIfFailed(
		    Reference<AsyncFileKAIO>::addRef(this),
		    AsyncFileEIO::async_fdatasync(fd)); // Don't close the file until the asynchronous thing is done
		// Alas, AIO f(data)sync doesn't seem to actually be implemented by the kernel
		/*IOBlock *io = new IOBlock(IO_CMD_FDSYNC, fd);
		submit(io, "write");
		fsync=success(io->result.getFuture());*/

		fsync = map(fsync, [=](Void r) mutable {
			KAIOLogEvent(logFile, id, OpLogEntry::SYNC, OpLogEntry::COMPLETE);
			getMetrics().syncLatencySample.addMeasurement(timer() - start_time);
			return r;
		});

		if (flags & OPEN_ATOMIC_WRITE_AND_CREATE) {
			flags &= ~OPEN_ATOMIC_WRITE_AND_CREATE;

			return AsyncFileEIO::waitAndAtomicRename(fsync, filename + ".part", filename);
		}

		return fsync;
	}
	Future<int64_t> size() const override { return nextFileSize; }
	int64_t debugFD() const override { return fd; }
	std::string getFilename() const override { return filename; }
	~AsyncFileKAIO() override {
		close(fd);

#if KAIO_LOGGING
		if (logFile != nullptr)
			fclose(logFile);
#endif
	}

	static void launch() {
		if (ctx.queue.size() && ctx.outstanding < FLOW_KNOBS->MAX_OUTSTANDING - FLOW_KNOBS->MIN_SUBMIT) {
			ctx.submitMetric = true;

			double begin = timer_monotonic();
			if (!ctx.outstanding)
				ctx.ioStallBegin = begin;

			IOBlock* toStart[FLOW_KNOBS->MAX_OUTSTANDING];
			int n = std::min<size_t>(FLOW_KNOBS->MAX_OUTSTANDING - ctx.outstanding, ctx.queue.size());

			int64_t previousTruncateCount = ctx.countPreSubmitTruncate;
			int64_t previousTruncateBytes = ctx.preSubmitTruncateBytes;
			int64_t largestTruncate = 0;

			double start = timer();
			for (int i = 0; i < n; i++) {
				auto io = ctx.queue.top();

				KAIOLogBlockEvent(io, OpLogEntry::LAUNCH);

				ctx.queue.pop();
				toStart[i] = io;
				io->startTime = start;

				if (ctx.ioTimeout > 0) {
					ctx.appendToRequestList(io);
				}

				if (io->owner->lastFileSize != io->owner->nextFileSize) {
					++ctx.countPreSubmitTruncate;
					int64_t truncateSize = io->owner->nextFileSize - io->owner->lastFileSize;
					ASSERT(truncateSize > 0);
					ctx.preSubmitTruncateBytes += truncateSize;
					largestTruncate = std::max(largestTruncate, truncateSize);
					io->owner->truncate(io->owner->nextFileSize);
				}
			}
			double truncateComplete = timer_monotonic();
			int rc = io_submit(ctx.iocx, n, (linux_iocb**)toStart);
			double end = timer_monotonic();

			if (end - begin > FLOW_KNOBS->SLOW_LOOP_CUTOFF) {
				ctx.slowAioSubmitMetric->submitDuration = end - truncateComplete;
				ctx.slowAioSubmitMetric->truncateDuration = truncateComplete - begin;
				ctx.slowAioSubmitMetric->numTruncates = ctx.countPreSubmitTruncate - previousTruncateCount;
				ctx.slowAioSubmitMetric->truncateBytes = ctx.preSubmitTruncateBytes - previousTruncateBytes;
				ctx.slowAioSubmitMetric->largestTruncate = largestTruncate;
				ctx.slowAioSubmitMetric->log();

				if (nondeterministicRandom()->random01() < end - begin) {
					TraceEvent("SlowKAIOLaunch")
					    .detail("IOSubmitTime", end - truncateComplete)
					    .detail("TruncateTime", truncateComplete - begin)
					    .detail("TruncateCount", ctx.countPreSubmitTruncate - previousTruncateCount)
					    .detail("TruncateBytes", ctx.preSubmitTruncateBytes - previousTruncateBytes)
					    .detail("LargestTruncate", largestTruncate);
				}
			}

			ctx.submitMetric = false;
			++ctx.countAIOSubmit;

			double elapsed = timer_monotonic() - begin;
			g_network->networkInfo.metrics.secSquaredSubmit += elapsed * elapsed / 2;

			//TraceEvent("Launched").detail("N", rc).detail("Queued", ctx.queue.size()).detail("Elapsed", elapsed).detail("Outstanding", ctx.outstanding+rc);
			// printf("launched: %d/%d in %f us (%d outstanding; lowest prio %d)\n", rc, ctx.queue.size(), elapsed*1e6,
			// ctx.outstanding + rc, toStart[n-1]->getTask());
			if (rc < 0) {
				if (errno == EAGAIN) {
					rc = 0;
				} else {
					KAIOLogBlockEvent(toStart[0], OpLogEntry::COMPLETE, errno ? -errno : -1000000);
					// Other errors are assumed to represent failure to issue the first I/O in the list
					toStart[0]->setResult(errno ? -errno : -1000000);
					rc = 1;
				}
			} else
				ctx.outstanding += rc;
			// Any unsubmitted I/Os need to be requeued
			for (int i = rc; i < n; i++) {
				KAIOLogBlockEvent(toStart[i], OpLogEntry::REQUEUE);
				ctx.queue.push(toStart[i]);
			}
		}
	}

	bool failed;

private:
	int fd, flags;
	int64_t lastFileSize, nextFileSize;
	std::string filename;
	Int64MetricHandle countFileLogicalWrites;
	Int64MetricHandle countFileLogicalReads;

	Int64MetricHandle countLogicalWrites;
	Int64MetricHandle countLogicalReads;

	struct IOBlock : linux_iocb, FastAllocated<IOBlock> {
		Promise<int> result;
		Reference<AsyncFileKAIO> owner;
		int64_t prio;
		IOBlock* prev;
		IOBlock* next;
		double startTime;
#if KAIO_LOGGING
		int32_t iolog_id;
#endif

		struct indirect_order_by_priority {
			bool operator()(IOBlock* a, IOBlock* b) { return a->prio < b->prio; }
		};

		IOBlock(int op, int fd) : prev(nullptr), next(nullptr), startTime(0) {
			memset((linux_iocb*)this, 0, sizeof(linux_iocb));
			aio_lio_opcode = op;
			aio_fildes = fd;
#if KAIO_LOGGING
			iolog_id = 0;
#endif
		}

		TaskPriority getTask() const { return static_cast<TaskPriority>((prio >> 32) + 1); }

																	#line 807 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
// This generated class is to be used only via deliver()
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
template <class DeliverActor>
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class DeliverActorState {
															#line 813 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	DeliverActorState(Promise<int> const& result,bool const& failed,int const& r,TaskPriority const& task) 
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		 : result(result),
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   failed(failed),
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   r(r),
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   task(task)
															#line 826 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
	{
		fdb_probe_actor_create("deliver", reinterpret_cast<unsigned long>(this));

	}
	~DeliverActorState() 
	{
		fdb_probe_actor_destroy("deliver", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 532 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			StrictFuture<Void> __when_expr_0 = delay(0, task);
															#line 532 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
															#line 843 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			static_cast<DeliverActor*>(this)->actor_wait_state = 1;
															#line 532 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< DeliverActor, 0, Void >*>(static_cast<DeliverActor*>(this)));
															#line 847 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
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
		delete static_cast<DeliverActor*>(this);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(Void const& _,int loopDepth) 
	{
															#line 533 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (failed)
															#line 869 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			result.sendError(io_timeout());
															#line 873 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
		else
		{
															#line 535 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (r < 0)
															#line 879 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				result.sendError(io_error());
															#line 883 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
			else
			{
															#line 538 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				result.send(r);
															#line 889 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
		}
		loopDepth = a_body1cont7(loopDepth);

		return loopDepth;
	}
	int a_body1cont1(Void && _,int loopDepth) 
	{
															#line 533 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (failed)
															#line 900 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 534 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			result.sendError(io_timeout());
															#line 904 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
		else
		{
															#line 535 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (r < 0)
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				result.sendError(io_error());
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
			else
			{
															#line 538 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				result.send(r);
															#line 920 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
		}
		loopDepth = a_body1cont7(loopDepth);

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
		if (static_cast<DeliverActor*>(this)->actor_wait_state > 0) static_cast<DeliverActor*>(this)->actor_wait_state = 0;
		static_cast<DeliverActor*>(this)->ActorCallback< DeliverActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< DeliverActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("deliver", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<DeliverActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("deliver", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< DeliverActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("deliver", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<DeliverActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("deliver", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< DeliverActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("deliver", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<DeliverActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("deliver", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont7(int loopDepth) 
	{
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		delete static_cast<DeliverActor*>(this);
															#line 1006 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		return 0;

		return loopDepth;
	}
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Promise<int> result;
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	bool failed;
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int r;
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	TaskPriority task;
															#line 1019 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
};
// This generated class is to be used only via deliver()
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class DeliverActor final : public Actor<void>, public ActorCallback< DeliverActor, 0, Void >, public FastAllocated<DeliverActor>, public DeliverActorState<DeliverActor> {
															#line 1024 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
	using FastAllocated<DeliverActor>::operator new;
	using FastAllocated<DeliverActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(1648040803021728256UL, 6710641680181878528UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< DeliverActor, 0, Void >;
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	DeliverActor(Promise<int> const& result,bool const& failed,int const& r,TaskPriority const& task) 
															#line 1041 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		 : Actor<void>(),
		   DeliverActorState<DeliverActor>(result, failed, r, task),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("deliver", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5177313518531985152UL, 17881294458268590080UL);
		ActorExecutionContextHelper __helper(static_cast<DeliverActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("deliver");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("deliver", reinterpret_cast<unsigned long>(this), -1);

	}
};
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
static void deliver( Promise<int> const& result, bool const& failed, int const& r, TaskPriority const& task ) {
															#line 531 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	new DeliverActor(result, failed, r, task);
															#line 1064 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
}

#line 540 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"

		void setResult(int r) {
			if (r < 0) {
				struct stat fst;
				fstat(aio_fildes, &fst);

				errno = -r;
				TraceEvent("AsyncFileKAIOIOError")
				    .GetLastError()
				    .detail("Fd", aio_fildes)
				    .detail("Op", aio_lio_opcode)
				    .detail("Nbytes", nbytes)
				    .detail("Offset", offset)
				    .detail("Ptr", int64_t(buf))
				    .detail("Size", fst.st_size)
				    .detail("Filename", owner->filename);
			}
			deliver(result, owner->failed, r, getTask());
			delete this;
		}

		void timeout(bool warnOnly) {
			TraceEvent(SevWarnAlways, "AsyncFileKAIOTimeout")
			    .detail("Fd", aio_fildes)
			    .detail("Op", aio_lio_opcode)
			    .detail("Nbytes", nbytes)
			    .detail("Offset", offset)
			    .detail("Ptr", int64_t(buf))
			    .detail("Filename", owner->filename);
			g_network->setGlobal(INetwork::enASIOTimedOut, (flowGlobalType) true);

			if (!warnOnly)
				owner->failed = true;
		}
	};

	struct Context {
		io_context_t iocx;
		int evfd;
		int outstanding;
		double ioStallBegin;
		bool fallocateSupported;
		bool fallocateZeroSupported;
		std::priority_queue<IOBlock*, std::vector<IOBlock*>, IOBlock::indirect_order_by_priority> queue;
		Int64MetricHandle countAIOSubmit;
		Int64MetricHandle countAIOCollect;
		Int64MetricHandle submitMetric;

		double ioTimeout;
		bool timeoutWarnOnly;
		IOBlock* submittedRequestList;

		Int64MetricHandle countPreSubmitTruncate;
		Int64MetricHandle preSubmitTruncateBytes;

		EventMetricHandle<SlowAioSubmit> slowAioSubmitMetric;

		uint32_t opsIssued;
		Context()
		  : iocx(0), evfd(-1), outstanding(0), ioStallBegin(0), fallocateSupported(true), fallocateZeroSupported(true),
		    submittedRequestList(nullptr), opsIssued(0) {
			setIOTimeout(0);
		}

		void setIOTimeout(double timeout) {
			ioTimeout = fabs(timeout);
			timeoutWarnOnly = timeout < 0;
		}

		void appendToRequestList(IOBlock* io) {
			ASSERT(!io->next && !io->prev);

			if (submittedRequestList) {
				io->prev = submittedRequestList->prev;
				io->prev->next = io;

				submittedRequestList->prev = io;
				io->next = submittedRequestList;
			} else {
				submittedRequestList = io;
				io->next = io->prev = io;
			}
		}

		void removeFromRequestList(IOBlock* io) {
			if (io->next == nullptr) {
				ASSERT(io->prev == nullptr);
				return;
			}

			ASSERT(io->prev != nullptr);

			if (io == io->next) {
				ASSERT(io == submittedRequestList && io == io->prev);
				submittedRequestList = nullptr;
			} else {
				io->next->prev = io->prev;
				io->prev->next = io->next;

				if (submittedRequestList == io) {
					submittedRequestList = io->next;
				}
			}

			io->next = io->prev = nullptr;
		}
	};
	static Context ctx;

	explicit AsyncFileKAIO(int fd, int flags, std::string const& filename)
	  : failed(false), fd(fd), flags(flags), filename(filename) {
		ASSERT(!FLOW_KNOBS->DISABLE_POSIX_KERNEL_AIO);
		if (!g_network->isSimulated()) {
			countFileLogicalWrites.init("AsyncFile.CountFileLogicalWrites"_sr, filename);
			countFileLogicalReads.init("AsyncFile.CountFileLogicalReads"_sr, filename);
			countLogicalWrites.init("AsyncFile.CountLogicalWrites"_sr);
			countLogicalReads.init("AsyncFile.CountLogicalReads"_sr);
		}

#if KAIO_LOGGING
		logFile = nullptr;
		// TODO:  Don't do this hacky investigation-specific thing
		StringRef fname(filename);
		if (fname.endsWith(".sqlite"_sr) || fname.endsWith(".sqlite-wal"_sr)) {
			std::string logFileName = basename(filename);
			while (logFileName.find("/") != std::string::npos)
				logFileName = logFileName.substr(logFileName.find("/") + 1);
			if (!logFileName.empty()) {
				// TODO: don't hardcode this path
				std::string logPath("/data/v7/fdb/");
				try {
					platform::createDirectory(logPath);
					logFileName = logPath + format("%s.iolog", logFileName.c_str());
					logFile = fopen(logFileName.c_str(), "r+");
					if (logFile == nullptr)
						logFile = fopen(logFileName.c_str(), "w");
					if (logFile != nullptr)
						TraceEvent("KAIOLogOpened").detail("File", filename).detail("LogFile", logFileName);
					else {
						TraceEvent(SevWarn, "KAIOLogOpenFailure")
						    .detail("File", filename)
						    .detail("LogFile", logFileName)
						    .detail("ErrorCode", errno)
						    .detail("ErrorDesc", strerror(errno));
					}
				} catch (Error& e) {
					TraceEvent(SevError, "KAIOLogOpenFailure").error(e);
				}
			}
		}
#endif
	}

	void enqueue(IOBlock* io, const char* op, AsyncFileKAIO* owner) {
		ASSERT(int64_t(io->buf) % 4096 == 0 && io->offset % 4096 == 0 && io->nbytes % 4096 == 0);

		KAIOLogBlockEvent(owner->logFile, io, OpLogEntry::START);

		io->flags |= 1;
		io->eventfd = ctx.evfd;
		io->prio = (int64_t(g_network->getCurrentTask()) << 32) - (++ctx.opsIssued);
		// io->prio = - (++ctx.opsIssued);
		io->owner = Reference<AsyncFileKAIO>::addRef(owner);

		ctx.queue.push(io);
	}

	static int openFlags(int flags) {
		int oflags = O_DIRECT | O_CLOEXEC;
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
		return oflags;
	}

																#line 1251 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
// This generated class is to be used only via poll()
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
template <class PollActor>
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class PollActorState {
															#line 1257 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	PollActorState(Reference<IEventFD> const& ev) 
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		 : ev(ev)
															#line 1264 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
	{
		fdb_probe_actor_create("poll", reinterpret_cast<unsigned long>(this));

	}
	~PollActorState() 
	{
		fdb_probe_actor_destroy("poll", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 724 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			;
															#line 1279 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
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
		delete static_cast<PollActor*>(this);
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
															#line 725 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_0 = success(ev->read());
															#line 725 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
															#line 1310 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		static_cast<PollActor*>(this)->actor_wait_state = 1;
															#line 725 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< PollActor, 0, Void >*>(static_cast<PollActor*>(this)));
															#line 1314 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(Void const& _,int loopDepth) 
	{
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, TaskPriority::DiskIOComplete);
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
															#line 1325 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		static_cast<PollActor*>(this)->actor_wait_state = 2;
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< PollActor, 1, Void >*>(static_cast<PollActor*>(this)));
															#line 1329 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont1(Void && _,int loopDepth) 
	{
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_1 = delay(0, TaskPriority::DiskIOComplete);
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
															#line 1340 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		static_cast<PollActor*>(this)->actor_wait_state = 2;
															#line 727 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< PollActor, 1, Void >*>(static_cast<PollActor*>(this)));
															#line 1344 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

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
		if (static_cast<PollActor*>(this)->actor_wait_state > 0) static_cast<PollActor*>(this)->actor_wait_state = 0;
		static_cast<PollActor*>(this)->ActorCallback< PollActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< PollActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< PollActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< PollActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont2(Void const& _,int loopDepth) 
	{
															#line 729 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		linux_ioresult ev[FLOW_KNOBS->MAX_OUTSTANDING];
															#line 730 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		timespec tm;
															#line 731 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		tm.tv_sec = 0;
															#line 732 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		tm.tv_nsec = 0;
															#line 734 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		int n;
															#line 736 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		for(;;) {
															#line 737 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			n = io_getevents(ctx.iocx, 0, FLOW_KNOBS->MAX_OUTSTANDING, ev, &tm);
															#line 738 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (n >= 0 || errno != EINTR)
															#line 1442 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
				break;
			}
		}
															#line 742 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		double currentTime = timer();
															#line 744 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		++ctx.countAIOCollect;
															#line 747 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (n < 0)
															#line 1453 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 749 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			TraceEvent("IOGetEventsError").GetLastError();
															#line 750 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			return a_body1Catch1(io_error(), std::max(0, loopDepth - 1));
															#line 1459 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 752 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (n)
															#line 1463 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 753 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			double t = timer_monotonic();
															#line 754 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			double elapsed = t - ctx.ioStallBegin;
															#line 755 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			ctx.ioStallBegin = t;
															#line 756 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			g_network->networkInfo.metrics.secSquaredDiskStall += elapsed * elapsed / 2;
															#line 1473 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 759 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ctx.outstanding -= n;
															#line 761 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (ctx.ioTimeout > 0)
															#line 1479 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 762 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			for(;ctx.submittedRequestList && currentTime - ctx.submittedRequestList->startTime > ctx.ioTimeout;) {
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.submittedRequestList->timeout(ctx.timeoutWarnOnly);
															#line 764 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.removeFromRequestList(ctx.submittedRequestList);
															#line 1487 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
		}
															#line 768 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		for(int i = 0;i < n;i++) {
															#line 769 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			IOBlock* iob = static_cast<IOBlock*>(ev[i].iocb);
															#line 771 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			KAIOLogBlockEvent(iob, OpLogEntry::COMPLETE, ev[i].result);
															#line 773 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (ctx.ioTimeout > 0)
															#line 1498 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 774 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.removeFromRequestList(iob);
															#line 1502 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
															#line 777 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			switch (iob->aio_lio_opcode) { case IO_CMD_PREAD: getMetrics().readLatencySample.addMeasurement(currentTime - iob->startTime); break; case IO_CMD_PWRITE: getMetrics().writeLatencySample.addMeasurement(currentTime - iob->startTime); break; };
															#line 786 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			iob->setResult(ev[i].result);
															#line 1508 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont2(Void && _,int loopDepth) 
	{
															#line 729 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		linux_ioresult ev[FLOW_KNOBS->MAX_OUTSTANDING];
															#line 730 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		timespec tm;
															#line 731 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		tm.tv_sec = 0;
															#line 732 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		tm.tv_nsec = 0;
															#line 734 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		int n;
															#line 736 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		for(;;) {
															#line 737 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			n = io_getevents(ctx.iocx, 0, FLOW_KNOBS->MAX_OUTSTANDING, ev, &tm);
															#line 738 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (n >= 0 || errno != EINTR)
															#line 1532 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
				break;
			}
		}
															#line 742 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		double currentTime = timer();
															#line 744 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		++ctx.countAIOCollect;
															#line 747 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (n < 0)
															#line 1543 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 749 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			TraceEvent("IOGetEventsError").GetLastError();
															#line 750 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			return a_body1Catch1(io_error(), std::max(0, loopDepth - 1));
															#line 1549 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 752 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (n)
															#line 1553 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 753 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			double t = timer_monotonic();
															#line 754 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			double elapsed = t - ctx.ioStallBegin;
															#line 755 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			ctx.ioStallBegin = t;
															#line 756 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			g_network->networkInfo.metrics.secSquaredDiskStall += elapsed * elapsed / 2;
															#line 1563 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
															#line 759 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ctx.outstanding -= n;
															#line 761 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (ctx.ioTimeout > 0)
															#line 1569 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
															#line 762 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			for(;ctx.submittedRequestList && currentTime - ctx.submittedRequestList->startTime > ctx.ioTimeout;) {
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.submittedRequestList->timeout(ctx.timeoutWarnOnly);
															#line 764 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.removeFromRequestList(ctx.submittedRequestList);
															#line 1577 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
		}
															#line 768 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		for(int i = 0;i < n;i++) {
															#line 769 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			IOBlock* iob = static_cast<IOBlock*>(ev[i].iocb);
															#line 771 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			KAIOLogBlockEvent(iob, OpLogEntry::COMPLETE, ev[i].result);
															#line 773 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (ctx.ioTimeout > 0)
															#line 1588 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 774 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				ctx.removeFromRequestList(iob);
															#line 1592 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
															#line 777 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			switch (iob->aio_lio_opcode) { case IO_CMD_PREAD: getMetrics().readLatencySample.addMeasurement(currentTime - iob->startTime); break; case IO_CMD_PWRITE: getMetrics().writeLatencySample.addMeasurement(currentTime - iob->startTime); break; };
															#line 786 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			iob->setResult(ev[i].result);
															#line 1598 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		}
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont2(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<PollActor*>(this)->actor_wait_state > 0) static_cast<PollActor*>(this)->actor_wait_state = 0;
		static_cast<PollActor*>(this)->ActorCallback< PollActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< PollActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< PollActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< PollActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), 1);

	}
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Reference<IEventFD> ev;
															#line 1681 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
};
// This generated class is to be used only via poll()
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class PollActor final : public Actor<void>, public ActorCallback< PollActor, 0, Void >, public ActorCallback< PollActor, 1, Void >, public FastAllocated<PollActor>, public PollActorState<PollActor> {
															#line 1686 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
	using FastAllocated<PollActor>::operator new;
	using FastAllocated<PollActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(3109674305735312128UL, 14201825383066576384UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() {{
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<void>*>(this)->~Actor();
        operator delete(this);
    }}
#pragma clang diagnostic pop
friend struct ActorCallback< PollActor, 0, Void >;
friend struct ActorCallback< PollActor, 1, Void >;
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	PollActor(Reference<IEventFD> const& ev) 
															#line 1704 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		 : Actor<void>(),
		   PollActorState<PollActor>(ev),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("poll", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(16014281592487113216UL, 13936416671654658816UL);
		ActorExecutionContextHelper __helper(static_cast<PollActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("poll");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("poll", reinterpret_cast<unsigned long>(this), -1);

	}
};
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
static void poll( Reference<IEventFD> const& ev ) {
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	new PollActor(ev);
															#line 1727 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
}

#line 790 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
};

#if KAIO_LOGGING
// Call from contexts where only an ioblock is available, log if its owner is set
void AsyncFileKAIO::KAIOLogBlockEvent(IOBlock* ioblock, OpLogEntry::EStage stage, uint32_t result) {
	if (ioblock->owner)
		return KAIOLogBlockEvent(ioblock->owner->logFile, ioblock, stage, result);
}

void AsyncFileKAIO::KAIOLogBlockEvent(FILE* logFile, IOBlock* ioblock, OpLogEntry::EStage stage, uint32_t result) {
	if (logFile != nullptr) {
		// Figure out what type of operation this is
		OpLogEntry::EOperation op;
		if (ioblock->aio_lio_opcode == IO_CMD_PREAD)
			op = OpLogEntry::READ;
		else if (ioblock->aio_lio_opcode == IO_CMD_PWRITE)
			op = OpLogEntry::WRITE;
		else
			return;

		// Assign this IO operation an io log id number if it doesn't already have one
		if (ioblock->iolog_id == 0)
			ioblock->iolog_id = OpLogEntry::nextID();

		OpLogEntry e;
		e.timestamp = timer_int();
		e.op = (uint8_t)op;
		e.id = ioblock->iolog_id;
		e.stage = (uint8_t)stage;
		e.pageOffset = (uint32_t)(ioblock->offset / 4096);
		e.pageCount = (uint8_t)(ioblock->nbytes / 4096);
		e.result = result;

		// Log a checksum for Writes up to the Complete stage or Reads starting from the Complete stage
		if ((op == OpLogEntry::WRITE && stage <= OpLogEntry::COMPLETE) ||
		    (op == OpLogEntry::READ && stage >= OpLogEntry::COMPLETE))
			e.checksum = crc32c_append(0xab12fd93, ioblock->buf, ioblock->nbytes);
		else
			e.checksum = 0;

		e.log(logFile);
	}
}

void AsyncFileKAIO::KAIOLogEvent(FILE* logFile,
                                 uint32_t id,
                                 OpLogEntry::EOperation op,
                                 OpLogEntry::EStage stage,
                                 uint32_t pageOffset,
                                 uint32_t result) {
	if (logFile != nullptr) {
		OpLogEntry e;
		e.timestamp = timer_int();
		e.id = id;
		e.op = (uint8_t)op;
		e.stage = (uint8_t)stage;
		e.pageOffset = pageOffset;
		e.pageCount = 0;
		e.checksum = 0;
		e.result = result;
		e.log(logFile);
	}
}
#endif

															#line 1796 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
namespace {
// This generated class is to be used only via runTestOps()
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
template <class RunTestOpsActor>
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class RunTestOpsActorState {
															#line 1803 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	RunTestOpsActorState(Reference<IAsyncFile> const& f,int const& numIterations,int const& fileSize,bool const& expectedToSucceed) 
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		 : f(f),
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   numIterations(numIterations),
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   fileSize(fileSize),
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   expectedToSucceed(expectedToSucceed),
															#line 856 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   buf(FastAllocator<4096>::allocate()),
															#line 858 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   iteration(0),
															#line 860 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		   opTimedOut(false)
															#line 1822 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
	{
		fdb_probe_actor_create("runTestOps", reinterpret_cast<unsigned long>(this));

	}
	~RunTestOpsActorState() 
	{
		fdb_probe_actor_destroy("runTestOps", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 862 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			;
															#line 1837 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
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
		this->~RunTestOpsActorState();
		static_cast<RunTestOpsActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 892 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		FastAllocator<4096>::release(buf);
															#line 894 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(expectedToSucceed || opTimedOut);
															#line 895 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!static_cast<RunTestOpsActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~RunTestOpsActorState(); static_cast<RunTestOpsActor*>(this)->destroy(); return 0; }
															#line 1864 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		new (&static_cast<RunTestOpsActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~RunTestOpsActorState();
		static_cast<RunTestOpsActor*>(this)->finishSendAndDelPromiseRef();
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
															#line 862 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!(iteration < numIterations))
															#line 1883 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
															#line 863 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		futures = std::vector<Future<Void>>();
															#line 864 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		numOps = deterministicRandom()->randomInt(1, 20);
															#line 865 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		for(;numOps > 0;--numOps) {
															#line 866 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (deterministicRandom()->coinflip())
															#line 1895 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 867 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				futures.push_back( success(f->read(buf, 4096, deterministicRandom()->randomInt(0, fileSize) / 4096 * 4096)));
															#line 1899 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
			else
			{
															#line 870 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				futures.push_back(f->write(buf, 4096, deterministicRandom()->randomInt(0, fileSize) / 4096 * 4096));
															#line 1905 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			}
		}
															#line 873 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		fIndex = 0;
															#line 874 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		;
															#line 1912 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = a_body1loopBody1loopHead1(loopDepth);

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
		try {
															#line 885 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			StrictFuture<Void> __when_expr_1 = f->sync() && delay(0.1);
															#line 885 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (static_cast<RunTestOpsActor*>(this)->actor_wait_state < 0) return a_body1loopBody1cont1Catch1(actor_cancelled(), loopDepth);
															#line 1937 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1loopBody1cont1Catch1(__when_expr_1.getError(), loopDepth); else return a_body1loopBody1cont1when1(__when_expr_1.get(), loopDepth); };
			static_cast<RunTestOpsActor*>(this)->actor_wait_state = 2;
															#line 885 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< RunTestOpsActor, 1, Void >*>(static_cast<RunTestOpsActor*>(this)));
															#line 1942 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1loopBody1cont1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1loopBody1cont1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1loopHead1(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1loopBody1loopBody1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1(int loopDepth) 
	{
															#line 874 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!(fIndex < futures.size()))
															#line 1964 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		{
			return a_body1loopBody1break1(loopDepth==0?0:loopDepth-1); // break
		}
		try {
															#line 876 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			StrictFuture<Void> __when_expr_0 = futures[fIndex];
															#line 876 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (static_cast<RunTestOpsActor*>(this)->actor_wait_state < 0) return a_body1loopBody1loopBody1Catch1(actor_cancelled(), loopDepth);
															#line 1973 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1loopBody1loopBody1Catch1(__when_expr_0.getError(), loopDepth); else return a_body1loopBody1loopBody1when1(__when_expr_0.get(), loopDepth); };
			static_cast<RunTestOpsActor*>(this)->actor_wait_state = 1;
															#line 876 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< RunTestOpsActor, 0, Void >*>(static_cast<RunTestOpsActor*>(this)));
															#line 1978 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			loopDepth = 0;
		}
		catch (Error& error) {
			loopDepth = a_body1loopBody1loopBody1Catch1(error, loopDepth);
		} catch (...) {
			loopDepth = a_body1loopBody1loopBody1Catch1(unknown_error(), loopDepth);
		}

		return loopDepth;
	}
	int a_body1loopBody1break1(int loopDepth) 
	{
		try {
			return a_body1loopBody1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1loopBody1cont1(int loopDepth) 
	{
															#line 874 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		++fIndex;
															#line 2006 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (loopDepth == 0) return a_body1loopBody1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 878 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			ASSERT(!expectedToSucceed);
															#line 879 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			ASSERT(e.code() == error_code_io_timeout);
															#line 880 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			opTimedOut = true;
															#line 2020 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			loopDepth = a_body1loopBody1loopBody1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 2));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 2));
		}

		return loopDepth;
	}
	int a_body1loopBody1loopBody1cont3(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1loopBody1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1cont3(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1loopBody1cont4(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1loopBody1cont3(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1loopBody1cont3(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<RunTestOpsActor*>(this)->actor_wait_state > 0) static_cast<RunTestOpsActor*>(this)->actor_wait_state = 0;
		static_cast<RunTestOpsActor*>(this)->ActorCallback< RunTestOpsActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RunTestOpsActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< RunTestOpsActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< RunTestOpsActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose1();
		try {
			a_body1loopBody1loopBody1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1loopBody1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1loopBody1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1loopBody1cont4(int loopDepth) 
	{
		try {
			loopDepth = a_body1loopBody1loopBody1cont1(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 2));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 2));
		}

		return loopDepth;
	}
	int a_body1loopBody1cont6(int loopDepth) 
	{
															#line 862 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		++iteration;
															#line 2135 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont1Catch1(const Error& e,int loopDepth=0) 
	{
		try {
															#line 888 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			ASSERT(!expectedToSucceed && e.code() == error_code_io_timeout);
															#line 2145 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			loopDepth = a_body1loopBody1cont6(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1cont7(Void const& _,int loopDepth) 
	{
															#line 886 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(expectedToSucceed);
															#line 2160 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = a_body1loopBody1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont7(Void && _,int loopDepth) 
	{
															#line 886 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(expectedToSucceed);
															#line 2169 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = a_body1loopBody1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont7(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont7(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<RunTestOpsActor*>(this)->actor_wait_state > 0) static_cast<RunTestOpsActor*>(this)->actor_wait_state = 0;
		static_cast<RunTestOpsActor*>(this)->ActorCallback< RunTestOpsActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< RunTestOpsActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(value, 0);
		}
		catch (Error& error) {
			a_body1loopBody1cont1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< RunTestOpsActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1loopBody1cont1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< RunTestOpsActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1cont1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1loopBody1cont1Catch1(error, 0);
		} catch (...) {
			a_body1loopBody1cont1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1loopBody1cont9(int loopDepth) 
	{
		try {
			loopDepth = a_body1loopBody1cont6(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Reference<IAsyncFile> f;
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int numIterations;
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int fileSize;
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	bool expectedToSucceed;
															#line 856 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	void* buf;
															#line 858 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int iteration;
															#line 860 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	bool opTimedOut;
															#line 863 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	std::vector<Future<Void>> futures;
															#line 864 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int numOps;
															#line 873 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int fIndex;
															#line 2282 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
};
// This generated class is to be used only via runTestOps()
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class RunTestOpsActor final : public Actor<Void>, public ActorCallback< RunTestOpsActor, 0, Void >, public ActorCallback< RunTestOpsActor, 1, Void >, public FastAllocated<RunTestOpsActor>, public RunTestOpsActorState<RunTestOpsActor> {
															#line 2287 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
	using FastAllocated<RunTestOpsActor>::operator new;
	using FastAllocated<RunTestOpsActor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(569188020691854848UL, 11372380555780046848UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< RunTestOpsActor, 0, Void >;
friend struct ActorCallback< RunTestOpsActor, 1, Void >;
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	RunTestOpsActor(Reference<IAsyncFile> const& f,int const& numIterations,int const& fileSize,bool const& expectedToSucceed) 
															#line 2305 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		 : Actor<Void>(),
		   RunTestOpsActorState<RunTestOpsActor>(f, numIterations, fileSize, expectedToSucceed),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("runTestOps", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9435527091077019136UL, 16829723036668749312UL);
		ActorExecutionContextHelper __helper(static_cast<RunTestOpsActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("runTestOps");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("runTestOps", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< RunTestOpsActor, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< RunTestOpsActor, 1, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
[[nodiscard]] Future<Void> runTestOps( Reference<IAsyncFile> const& f, int const& numIterations, int const& fileSize, bool const& expectedToSucceed ) {
															#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	return Future<Void>(new RunTestOpsActor(f, numIterations, fileSize, expectedToSucceed));
															#line 2339 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
}

#line 897 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"

															#line 2344 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
namespace {
// This generated class is to be used only via flowTestCase898()
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
template <class FlowTestCase898Actor>
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class FlowTestCase898ActorState {
															#line 2351 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	FlowTestCase898ActorState(UnitTestParameters const& params) 
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		 : params(params)
															#line 2358 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
	{
		fdb_probe_actor_create("flowTestCase898", reinterpret_cast<unsigned long>(this));

	}
	~FlowTestCase898ActorState() 
	{
		fdb_probe_actor_destroy("flowTestCase898", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 900 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (!g_network->isSimulated())
															#line 2373 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 901 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				f = Reference<IAsyncFile>();
															#line 2377 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
				try {
															#line 903 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
					StrictFuture<Reference<IAsyncFile>> __when_expr_0 = AsyncFileKAIO::open("/tmp/__KAIO_TEST_FILE__", IAsyncFile::OPEN_UNBUFFERED | IAsyncFile::OPEN_READWRITE | IAsyncFile::OPEN_CREATE, 0666, nullptr);
															#line 903 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
					if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2383 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
					if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch2(__when_expr_0.getError(), loopDepth); else return a_body1when1(__when_expr_0.get(), loopDepth); };
					static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 1;
															#line 903 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
					__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2388 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
					loopDepth = 0;
				}
				catch (Error& error) {
					loopDepth = a_body1Catch2(error, loopDepth);
				} catch (...) {
					loopDepth = a_body1Catch2(unknown_error(), loopDepth);
				}
			}
			else
			{
				loopDepth = a_body1cont1(loopDepth);
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
		this->~FlowTestCase898ActorState();
		static_cast<FlowTestCase898Actor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 937 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (!static_cast<FlowTestCase898Actor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~FlowTestCase898ActorState(); static_cast<FlowTestCase898Actor*>(this)->destroy(); return 0; }
															#line 2422 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		new (&static_cast<FlowTestCase898Actor*>(this)->SAV< Void >::value()) Void(Void());
		this->~FlowTestCase898ActorState();
		static_cast<FlowTestCase898Actor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont2(int loopDepth) 
	{
															#line 934 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_6 = AsyncFileEIO::deleteFile(f->getFilename(), true);
															#line 934 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 2436 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_6.isReady()) { if (__when_expr_6.isError()) return a_body1Catch1(__when_expr_6.getError(), loopDepth); else return a_body1cont2when1(__when_expr_6.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 7;
															#line 934 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_6.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 6, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2441 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1Catch2(const Error& e,int loopDepth=0) 
	{
		try {
															#line 927 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			err = e;
															#line 928 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
			if (f)
															#line 2453 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
			{
															#line 929 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				StrictFuture<Void> __when_expr_5 = AsyncFileEIO::deleteFile(f->getFilename(), true);
															#line 929 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 2459 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
				if (__when_expr_5.isReady()) { if (__when_expr_5.isError()) return a_body1Catch1(__when_expr_5.getError(), loopDepth); else return a_body1Catch2when1(__when_expr_5.get(), loopDepth); };
				static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 6;
															#line 929 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
				__when_expr_5.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 5, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2464 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
				loopDepth = 0;
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
	int a_body1cont3(Reference<IAsyncFile> const& f_,int loopDepth) 
	{
															#line 908 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		f = f_;
															#line 909 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		fileSize = 2 << 27;
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_1 = f->truncate(fileSize);
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2490 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch2(__when_expr_1.getError(), loopDepth); else return a_body1cont3when1(__when_expr_1.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 2;
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 1, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2495 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont3(Reference<IAsyncFile> && f_,int loopDepth) 
	{
															#line 908 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		f = f_;
															#line 909 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		fileSize = 2 << 27;
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_1 = f->truncate(fileSize);
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2510 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch2(__when_expr_1.getError(), loopDepth); else return a_body1cont3when1(__when_expr_1.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 2;
															#line 910 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 1, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2515 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1when1(Reference<IAsyncFile> const& f_,int loopDepth) 
	{
		loopDepth = a_body1cont3(f_, loopDepth);

		return loopDepth;
	}
	int a_body1when1(Reference<IAsyncFile> && f_,int loopDepth) 
	{
		loopDepth = a_body1cont3(std::move(f_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >*,Reference<IAsyncFile> const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >*,Reference<IAsyncFile> && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1cont4(Void const& _,int loopDepth) 
	{
															#line 913 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(0.0);
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_2 = runTestOps(f, 100, fileSize, true);
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2603 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch2(__when_expr_2.getError(), loopDepth); else return a_body1cont4when1(__when_expr_2.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 3;
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 2, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2608 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont4(Void && _,int loopDepth) 
	{
															#line 913 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(0.0);
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_2 = runTestOps(f, 100, fileSize, true);
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2621 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch2(__when_expr_2.getError(), loopDepth); else return a_body1cont4when1(__when_expr_2.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 3;
															#line 914 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 2, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2626 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont3when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont4(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont3when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont4(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont3when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1cont3when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont5(Void const& _,int loopDepth) 
	{
															#line 915 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(!((AsyncFileKAIO*)f.getPtr())->failed);
															#line 918 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(20.0);
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_3 = runTestOps(f, 100, fileSize, true);
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2716 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_3.isReady()) { if (__when_expr_3.isError()) return a_body1Catch2(__when_expr_3.getError(), loopDepth); else return a_body1cont5when1(__when_expr_3.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 4;
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_3.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 3, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2721 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont5(Void && _,int loopDepth) 
	{
															#line 915 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(!((AsyncFileKAIO*)f.getPtr())->failed);
															#line 918 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(20.0);
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_3 = runTestOps(f, 100, fileSize, true);
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2736 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_3.isReady()) { if (__when_expr_3.isError()) return a_body1Catch2(__when_expr_3.getError(), loopDepth); else return a_body1cont5when1(__when_expr_3.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 4;
															#line 919 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_3.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 3, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2741 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont4when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont5(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont4when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont5(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont4when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1cont4when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 2);

	}
	int a_body1cont6(Void const& _,int loopDepth) 
	{
															#line 920 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(!((AsyncFileKAIO*)f.getPtr())->failed);
															#line 923 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(0.0001);
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_4 = runTestOps(f, 10, fileSize, false);
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2831 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_4.isReady()) { if (__when_expr_4.isError()) return a_body1Catch2(__when_expr_4.getError(), loopDepth); else return a_body1cont6when1(__when_expr_4.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 5;
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_4.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 4, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2836 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont6(Void && _,int loopDepth) 
	{
															#line 920 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(!((AsyncFileKAIO*)f.getPtr())->failed);
															#line 923 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		AsyncFileKAIO::setTimeout(0.0001);
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		StrictFuture<Void> __when_expr_4 = runTestOps(f, 10, fileSize, false);
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state < 0) return a_body1Catch2(actor_cancelled(), loopDepth);
															#line 2851 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		if (__when_expr_4.isReady()) { if (__when_expr_4.isError()) return a_body1Catch2(__when_expr_4.getError(), loopDepth); else return a_body1cont6when1(__when_expr_4.get(), loopDepth); };
		static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 5;
															#line 924 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		__when_expr_4.addCallbackAndClear(static_cast<ActorCallback< FlowTestCase898Actor, 4, Void >*>(static_cast<FlowTestCase898Actor*>(this)));
															#line 2856 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont5when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont6(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont5when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont6(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose4() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 3, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 3, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1cont5when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 3, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1cont5when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 3, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 3);

	}
	int a_body1cont7(Void const& _,int loopDepth) 
	{
															#line 925 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(((AsyncFileKAIO*)f.getPtr())->failed);
															#line 2940 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = a_body1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1cont7(Void && _,int loopDepth) 
	{
															#line 925 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		ASSERT(((AsyncFileKAIO*)f.getPtr())->failed);
															#line 2949 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		loopDepth = a_body1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1cont6when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont7(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont6when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont7(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose5() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 4, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 4, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1cont6when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 4, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1cont6when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 4, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1Catch2(err, 0);
		}
		catch (Error& error) {
			a_body1Catch2(error, 0);
		} catch (...) {
			a_body1Catch2(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 4);

	}
	int a_body1cont9(int loopDepth) 
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
	int a_body1Catch2cont1(int loopDepth) 
	{
															#line 931 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
		return a_body1Catch1(err, loopDepth);
															#line 3046 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"

		return loopDepth;
	}
	int a_body1Catch2cont2(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2cont2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont1(loopDepth);

		return loopDepth;
	}
	int a_body1Catch2when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont2(_, loopDepth);

		return loopDepth;
	}
	int a_body1Catch2when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1Catch2cont2(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose6() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 5, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 5, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose6();
		try {
			a_body1Catch2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 5, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose6();
		try {
			a_body1Catch2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 5, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose6();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 5);

	}
	int a_body1cont10(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont10(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1cont2when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont10(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont2when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont10(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose7() 
	{
		if (static_cast<FlowTestCase898Actor*>(this)->actor_wait_state > 0) static_cast<FlowTestCase898Actor*>(this)->actor_wait_state = 0;
		static_cast<FlowTestCase898Actor*>(this)->ActorCallback< FlowTestCase898Actor, 6, Void >::remove();

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 6, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose7();
		try {
			a_body1cont2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);

	}
	void a_callback_fire(ActorCallback< FlowTestCase898Actor, 6, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose7();
		try {
			a_body1cont2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);

	}
	void a_callback_error(ActorCallback< FlowTestCase898Actor, 6, Void >*,Error err) 
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose7();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), 6);

	}
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	UnitTestParameters params;
															#line 901 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Reference<IAsyncFile> f;
															#line 909 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	int fileSize;
															#line 927 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	Error err;
															#line 3232 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
};
// This generated class is to be used only via flowTestCase898()
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
class FlowTestCase898Actor final : public Actor<Void>, public ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >, public ActorCallback< FlowTestCase898Actor, 1, Void >, public ActorCallback< FlowTestCase898Actor, 2, Void >, public ActorCallback< FlowTestCase898Actor, 3, Void >, public ActorCallback< FlowTestCase898Actor, 4, Void >, public ActorCallback< FlowTestCase898Actor, 5, Void >, public ActorCallback< FlowTestCase898Actor, 6, Void >, public FastAllocated<FlowTestCase898Actor>, public FlowTestCase898ActorState<FlowTestCase898Actor> {
															#line 3237 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
public:
	using FastAllocated<FlowTestCase898Actor>::operator new;
	using FastAllocated<FlowTestCase898Actor>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(4584394015669171712UL, 16355401431789971712UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >;
friend struct ActorCallback< FlowTestCase898Actor, 1, Void >;
friend struct ActorCallback< FlowTestCase898Actor, 2, Void >;
friend struct ActorCallback< FlowTestCase898Actor, 3, Void >;
friend struct ActorCallback< FlowTestCase898Actor, 4, Void >;
friend struct ActorCallback< FlowTestCase898Actor, 5, Void >;
friend struct ActorCallback< FlowTestCase898Actor, 6, Void >;
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	FlowTestCase898Actor(UnitTestParameters const& params) 
															#line 3260 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
		 : Actor<Void>(),
		   FlowTestCase898ActorState<FlowTestCase898Actor>(params),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("flowTestCase898", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(17133146770374145280UL, 17852334328801171456UL);
		ActorExecutionContextHelper __helper(static_cast<FlowTestCase898Actor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("flowTestCase898");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("flowTestCase898", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 0, Reference<IAsyncFile> >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 2, Void >*)0, actor_cancelled()); break;
		case 4: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 3, Void >*)0, actor_cancelled()); break;
		case 5: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 4, Void >*)0, actor_cancelled()); break;
		case 6: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 5, Void >*)0, actor_cancelled()); break;
		case 7: this->a_callback_error((ActorCallback< FlowTestCase898Actor, 6, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
static Future<Void> flowTestCase898( UnitTestParameters const& params ) {
															#line 898 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"
	return Future<Void>(new FlowTestCase898Actor(params));
															#line 3299 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.g.h"
}
ACTOR_TEST_CASE(flowTestCase898, "/fdbrpc/AsyncFileKAIO/RequestList")

#line 939 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/AsyncFileKAIO.actor.h"

AsyncFileKAIO::Context AsyncFileKAIO::ctx;

#include "flow/unactorcompiler.h"
#endif
#endif
