#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
/*
 * LoadBalance.actor.h
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
#if defined(NO_INTELLISENSE) && !defined(FLOW_LOADBALANCE_ACTOR_G_H)
#define FLOW_LOADBALANCE_ACTOR_G_H
#include "fdbrpc/LoadBalance.actor.g.h"
#elif !defined(FLOW_LOADBALANCE_ACTOR_H)
#define FLOW_LOADBALANCE_ACTOR_H

#include "flow/BooleanParam.h"
#include "flow/flow.h"
#include "flow/Knobs.h"

#include "fdbrpc/FailureMonitor.h"
#include "fdbrpc/fdbrpc.h"
#include "fdbrpc/Locality.h"
#include "fdbrpc/QueueModel.h"
#include "fdbrpc/MultiInterface.h"
#include "fdbrpc/simulator.h" // for checking tss simulation mode
#include "fdbrpc/TSSComparison.h"
#include "flow/actorcompiler.h" // This must be the last #include.

															#line 46 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
[[nodiscard]] Future<Void> allAlternativesFailedDelay( Future<Void> const& okFuture );

#line 45 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"

struct ModelHolder : NonCopyable, public ReferenceCounted<ModelHolder> {
	QueueModel* model;
	bool released;
	double startTime;
	double delta;
	uint64_t token;

	ModelHolder(QueueModel* model, uint64_t token) : model(model), released(false), startTime(now()), token(token) {
		if (model) {
			delta = model->addRequest(token);
		}
	}

	void release(bool clean, bool futureVersion, double penalty, bool measureLatency = true) {
		if (model && !released) {
			released = true;
			double latency = (clean || measureLatency) ? now() - startTime : 0.0;
			model->endRequest(token, latency, penalty, delta, clean, futureVersion);
		}
	}

	~ModelHolder() { release(false, false, -1.0, false); }
};

// Subclasses must initialize all members in their default constructors
// Subclasses must serialize all members
struct LoadBalancedReply {
	double penalty;
	Optional<Error> error;
	LoadBalancedReply() : penalty(1.0) {}
};

Optional<LoadBalancedReply> getLoadBalancedReply(const LoadBalancedReply* reply);
Optional<LoadBalancedReply> getLoadBalancedReply(const void*);

															#line 86 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
namespace {
// This generated class is to be used only via tssComparison()
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Req, class Resp, class Interface, class Multi, bool P, class TssComparisonActor>
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class TssComparisonActorState {
															#line 93 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TssComparisonActorState(Req const& req,Future<ErrorOr<Resp>> const& fSource,Future<ErrorOr<Resp>> const& fTss,TSSEndpointData const& tssData,uint64_t const& srcEndpointId,Reference<MultiInterface<Multi>> const& ssTeam,RequestStream<Req, P> Interface::* const& channel) 
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		 : req(req),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   fSource(fSource),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   fTss(fTss),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   tssData(tssData),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   srcEndpointId(srcEndpointId),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   ssTeam(ssTeam),
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   channel(channel),
															#line 89 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   startTime(now()),
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   fTssWithTimeout(timeout(fTss, FLOW_KNOBS->LOAD_BALANCE_TSS_TIMEOUT)),
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   finished(0),
															#line 92 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   srcEndTime(),
															#line 93 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   tssEndTime(),
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   srcErrorCode(error_code_success),
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   tssErrorCode(error_code_success),
															#line 97 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   src(),
															#line 98 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   tss()
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
	{
		fdb_probe_actor_create("tssComparison", reinterpret_cast<unsigned long>(this));

	}
	~TssComparisonActorState() 
	{
		fdb_probe_actor_destroy("tssComparison", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 100 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			;
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
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
		this->~TssComparisonActorState();
		static_cast<TssComparisonActor*>(this)->sendErrorAndDelPromiseRef(error);
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1cont1(int loopDepth) 
	{
															#line 120 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		++tssData.metrics->requests;
															#line 122 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (src.isError())
															#line 170 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 123 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			srcErrorCode = src.getError().code();
															#line 124 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			tssData.metrics->ssError(srcErrorCode);
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 126 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (!tss.present())
															#line 180 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 127 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			++tssData.metrics->tssTimeouts;
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		else
		{
															#line 128 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (tss.get().isError())
															#line 190 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 129 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				tssErrorCode = tss.get().getError().code();
															#line 130 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				tssData.metrics->tssError(tssErrorCode);
															#line 196 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
		}
															#line 132 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (!src.isError() && tss.present() && !tss.get().isError())
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 133 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			Optional<LoadBalancedReply> srcLB = getLoadBalancedReply(&src.get());
															#line 134 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			Optional<LoadBalancedReply> tssLB = getLoadBalancedReply(&tss.get().get());
															#line 135 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ASSERT(srcLB.present() == tssLB.present());
															#line 139 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!srcLB.present() || (!srcLB.get().error.present() && !tssLB.get().error.present()))
															#line 211 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 142 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				tssData.metrics->recordLatency(req, srcEndTime - startTime, tssEndTime - startTime);
															#line 144 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (!TSS_doCompare(src.get(), tss.get().get()))
															#line 217 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 145 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					CODE_PROBE(true, "TSS Mismatch");
															#line 146 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					mismatchEvent = TraceEvent((g_network->isSimulated() && g_simulator->tssMode == ISimulator::TSSMode::EnabledDropMutations) ? SevWarnAlways : SevError, TSS_mismatchTraceName(req));
															#line 151 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					mismatchEvent.setMaxEventLength(FLOW_KNOBS->TSS_LARGE_TRACE_SIZE);
															#line 152 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					mismatchEvent.detail("TSSID", tssData.tssId);
															#line 154 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (FLOW_KNOBS->LOAD_BALANCE_TSS_MISMATCH_VERIFY_SS && ssTeam->size() > 1)
															#line 229 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 155 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						CODE_PROBE(true, "checking TSS mismatch against rest of storage team");
															#line 159 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						restOfTeamFutures = std::vector<Future<ErrorOr<Resp>>>();
															#line 160 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						restOfTeamFutures.reserve(ssTeam->size() - 1);
															#line 161 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						for(int i = 0;i < ssTeam->size();i++) {
															#line 162 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							RequestStream<Req, P> const* si = &ssTeam->get(i, channel);
															#line 163 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							if (si->getEndpoint().token.first() != srcEndpointId)
															#line 243 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							{
															#line 165 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								resetReply(req);
															#line 166 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								restOfTeamFutures.push_back(si->tryGetReply(req));
															#line 249 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							}
						}
															#line 170 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						StrictFuture<Void> __when_expr_2 = waitForAllReady(restOfTeamFutures);
															#line 170 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (static_cast<TssComparisonActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), loopDepth);
															#line 256 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), loopDepth); else return a_body1cont1when1(__when_expr_2.get(), loopDepth); };
						static_cast<TssComparisonActor*>(this)->actor_wait_state = 2;
															#line 170 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< TssComparisonActor, 2, Void >*>(static_cast<TssComparisonActor*>(this)));
															#line 261 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						loopDepth = 0;
					}
					else
					{
						loopDepth = a_body1cont9(loopDepth);
					}
				}
				else
				{
					loopDepth = a_body1cont8(loopDepth);
				}
			}
			else
			{
															#line 222 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (tssLB.present() && tssLB.get().error.present())
															#line 278 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 223 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					tssErrorCode = tssLB.get().error.get().code();
															#line 224 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					tssData.metrics->tssError(tssErrorCode);
															#line 284 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
				else
				{
															#line 225 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (srcLB.present() && srcLB.get().error.present())
															#line 290 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 226 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						srcErrorCode = srcLB.get().error.get().code();
															#line 227 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						tssData.metrics->ssError(srcErrorCode);
															#line 296 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
				}
				loopDepth = a_body1cont7(loopDepth);
			}
		}
		else
		{
			loopDepth = a_body1cont2(loopDepth);
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
															#line 102 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<Void> __when_expr_0 = store(src, fSource);
															#line 101 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (static_cast<TssComparisonActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 322 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
															#line 110 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<Void> __when_expr_1 = store(tss, fTssWithTimeout);
															#line 326 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when2(__when_expr_1.get(), loopDepth); };
		static_cast<TssComparisonActor*>(this)->actor_wait_state = 1;
															#line 102 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< TssComparisonActor, 0, Void >*>(static_cast<TssComparisonActor*>(this)));
															#line 110 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< TssComparisonActor, 1, Void >*>(static_cast<TssComparisonActor*>(this)));
															#line 333 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
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
	int a_body1loopBody1cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		srcEndTime = now();
															#line 104 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		fSource = Never();
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		finished++;
															#line 106 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (finished == 2)
															#line 367 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
															#line 103 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		srcEndTime = now();
															#line 104 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		fSource = Never();
															#line 105 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		finished++;
															#line 106 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (finished == 2)
															#line 385 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void const& _,int loopDepth) 
	{
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		tssEndTime = now();
															#line 112 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		fTssWithTimeout = Never();
															#line 113 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		finished++;
															#line 114 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (finished == 2)
															#line 403 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void && _,int loopDepth) 
	{
															#line 111 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		tssEndTime = now();
															#line 112 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		fTssWithTimeout = Never();
															#line 113 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		finished++;
															#line 114 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (finished == 2)
															#line 421 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
			return a_body1break1(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<TssComparisonActor*>(this)->actor_wait_state > 0) static_cast<TssComparisonActor*>(this)->actor_wait_state = 0;
		static_cast<TssComparisonActor*>(this)->ActorCallback< TssComparisonActor, 0, Void >::remove();
		static_cast<TssComparisonActor*>(this)->ActorCallback< TssComparisonActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< TssComparisonActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< TssComparisonActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1cont2(int loopDepth) 
	{
															#line 231 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (srcErrorCode != error_code_success && tssErrorCode != error_code_success && srcErrorCode != tssErrorCode)
															#line 554 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 233 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			TraceEvent("TSSErrorMismatch") .suppressFor(1.0) .detail("TSSID", tssData.tssId) .detail("SSError", srcErrorCode) .detail("TSSError", tssErrorCode);
															#line 558 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 240 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (!static_cast<TssComparisonActor*>(this)->SAV<Void>::futures) { (void)(Void()); this->~TssComparisonActorState(); static_cast<TssComparisonActor*>(this)->destroy(); return 0; }
															#line 562 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		new (&static_cast<TssComparisonActor*>(this)->SAV< Void >::value()) Void(Void());
		this->~TssComparisonActorState();
		static_cast<TssComparisonActor*>(this)->finishSendAndDelPromiseRef();
		return 0;

		return loopDepth;
	}
	int a_body1cont7(int loopDepth) 
	{
		loopDepth = a_body1cont2(loopDepth);

		return loopDepth;
	}
	int a_body1cont8(int loopDepth) 
	{
		loopDepth = a_body1cont7(loopDepth);

		return loopDepth;
	}
	int a_body1cont9(int loopDepth) 
	{
															#line 197 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (tssData.metrics->shouldRecordDetailedMismatch())
															#line 586 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 198 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			TSS_traceMismatch(mismatchEvent, req, src.get(), tss.get().get());
															#line 200 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			CODE_PROBE(FLOW_KNOBS->LOAD_BALANCE_TSS_MISMATCH_TRACE_FULL, "Tracing Full TSS Mismatch");
															#line 201 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			CODE_PROBE(!FLOW_KNOBS->LOAD_BALANCE_TSS_MISMATCH_TRACE_FULL, "Tracing Partial TSS Mismatch and storing the rest in FDB");
															#line 204 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!FLOW_KNOBS->LOAD_BALANCE_TSS_MISMATCH_TRACE_FULL)
															#line 596 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 205 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				mismatchEvent.disable();
															#line 206 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				UID mismatchUID = deterministicRandom()->randomUniqueID();
															#line 207 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				tssData.metrics->recordDetailedMismatchData(mismatchUID, mismatchEvent.getFields().toString());
															#line 210 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				TraceEvent summaryEvent((g_network->isSimulated() && g_simulator->tssMode == ISimulator::TSSMode::EnabledDropMutations) ? SevWarnAlways : SevError, TSS_mismatchTraceName(req));
															#line 215 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				summaryEvent.detail("TSSID", tssData.tssId).detail("MismatchId", mismatchUID);
															#line 608 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
		}
		else
		{
															#line 219 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			mismatchEvent.disable();
															#line 615 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		loopDepth = a_body1cont8(loopDepth);

		return loopDepth;
	}
	int a_body1cont10(Void const& _,int loopDepth) 
	{
															#line 172 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numError = 0;
															#line 173 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchSS = 0;
															#line 174 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchTSS = 0;
															#line 175 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchNeither = 0;
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		for( Future<ErrorOr<Resp>> f : restOfTeamFutures ) {
															#line 177 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!f.canGet() || f.get().isError())
															#line 635 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 178 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				numError++;
															#line 639 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
			else
			{
															#line 180 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				Optional<LoadBalancedReply> fLB = getLoadBalancedReply(&f.get().get());
															#line 181 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (fLB.present() && fLB.get().error.present())
															#line 647 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 182 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					numError++;
															#line 651 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
				else
				{
															#line 183 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (TSS_doCompare(src.get(), f.get().get()))
															#line 657 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						numMatchSS++;
															#line 661 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
					else
					{
															#line 185 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (TSS_doCompare(tss.get().get(), f.get().get()))
															#line 667 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						{
															#line 186 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							numMatchTSS++;
															#line 671 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
						else
						{
															#line 188 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							numMatchNeither++;
															#line 677 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
					}
				}
			}
		}
															#line 192 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		mismatchEvent.detail("TeamCheckErrors", numError) .detail("TeamCheckMatchSS", numMatchSS) .detail("TeamCheckMatchTSS", numMatchTSS) .detail("TeamCheckMatchNeither", numMatchNeither);
															#line 685 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1cont10(Void && _,int loopDepth) 
	{
															#line 172 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numError = 0;
															#line 173 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchSS = 0;
															#line 174 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchTSS = 0;
															#line 175 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		int numMatchNeither = 0;
															#line 176 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		for( Future<ErrorOr<Resp>> f : restOfTeamFutures ) {
															#line 177 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!f.canGet() || f.get().isError())
															#line 704 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 178 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				numError++;
															#line 708 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
			else
			{
															#line 180 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				Optional<LoadBalancedReply> fLB = getLoadBalancedReply(&f.get().get());
															#line 181 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (fLB.present() && fLB.get().error.present())
															#line 716 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 182 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					numError++;
															#line 720 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
				else
				{
															#line 183 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (TSS_doCompare(src.get(), f.get().get()))
															#line 726 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 184 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						numMatchSS++;
															#line 730 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
					else
					{
															#line 185 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (TSS_doCompare(tss.get().get(), f.get().get()))
															#line 736 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						{
															#line 186 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							numMatchTSS++;
															#line 740 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
						else
						{
															#line 188 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							numMatchNeither++;
															#line 746 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
					}
				}
			}
		}
															#line 192 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		mismatchEvent.detail("TeamCheckErrors", numError) .detail("TeamCheckMatchSS", numMatchSS) .detail("TeamCheckMatchTSS", numMatchTSS) .detail("TeamCheckMatchNeither", numMatchNeither);
															#line 754 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1cont9(loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1cont10(_, loopDepth);

		return loopDepth;
	}
	int a_body1cont1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1cont10(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<TssComparisonActor*>(this)->actor_wait_state > 0) static_cast<TssComparisonActor*>(this)->actor_wait_state = 0;
		static_cast<TssComparisonActor*>(this)->ActorCallback< TssComparisonActor, 2, Void >::remove();

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 2, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< TssComparisonActor, 2, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< TssComparisonActor, 2, Void >*,Error err) 
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Req req;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Future<ErrorOr<Resp>> fSource;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Future<ErrorOr<Resp>> fTss;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TSSEndpointData tssData;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	uint64_t srcEndpointId;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Reference<MultiInterface<Multi>> ssTeam;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestStream<Req, P> Interface::* channel;
															#line 89 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double startTime;
															#line 90 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Future<Optional<ErrorOr<Resp>>> fTssWithTimeout;
															#line 91 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int finished;
															#line 92 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double srcEndTime;
															#line 93 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double tssEndTime;
															#line 95 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int srcErrorCode;
															#line 96 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int tssErrorCode;
															#line 97 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	ErrorOr<Resp> src;
															#line 98 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Optional<ErrorOr<Resp>> tss;
															#line 146 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TraceEvent mismatchEvent;
															#line 159 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	std::vector<Future<ErrorOr<Resp>>> restOfTeamFutures;
															#line 870 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
};
// This generated class is to be used only via tssComparison()
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Req, class Resp, class Interface, class Multi, bool P>
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class TssComparisonActor final : public Actor<Void>, public ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 0, Void >, public ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 1, Void >, public ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 2, Void >, public FastAllocated<TssComparisonActor<Req, Resp, Interface, Multi, P>>, public TssComparisonActorState<Req, Resp, Interface, Multi, P, TssComparisonActor<Req, Resp, Interface, Multi, P>> {
															#line 877 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
	using FastAllocated<TssComparisonActor<Req, Resp, Interface, Multi, P>>::operator new;
	using FastAllocated<TssComparisonActor<Req, Resp, Interface, Multi, P>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(2180797396761985536UL, 17997741216804597504UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<Void>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 0, Void >;
friend struct ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 1, Void >;
friend struct ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 2, Void >;
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TssComparisonActor(Req const& req,Future<ErrorOr<Resp>> const& fSource,Future<ErrorOr<Resp>> const& fTss,TSSEndpointData const& tssData,uint64_t const& srcEndpointId,Reference<MultiInterface<Multi>> const& ssTeam,RequestStream<Req, P> Interface::* const& channel) 
															#line 896 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		 : Actor<Void>(),
		   TssComparisonActorState<Req, Resp, Interface, Multi, P, TssComparisonActor<Req, Resp, Interface, Multi, P>>(req, fSource, fTss, tssData, srcEndpointId, ssTeam, channel),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("tssComparison", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(8553245748359799296UL, 10319318729022024192UL);
		ActorExecutionContextHelper __helper(static_cast<TssComparisonActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("tssComparison");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("tssComparison", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< TssComparisonActor<Req, Resp, Interface, Multi, P>, 2, Void >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Req, class Resp, class Interface, class Multi, bool P>
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
[[nodiscard]] Future<Void> tssComparison( Req const& req, Future<ErrorOr<Resp>> const& fSource, Future<ErrorOr<Resp>> const& fTss, TSSEndpointData const& tssData, uint64_t const& srcEndpointId, Reference<MultiInterface<Multi>> const& ssTeam, RequestStream<Req, P> Interface::* const& channel ) {
															#line 81 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	return Future<Void>(new TssComparisonActor<Req, Resp, Interface, Multi, P>(req, fSource, fTss, tssData, srcEndpointId, ssTeam, channel));
															#line 932 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
}

#line 242 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"

FDB_BOOLEAN_PARAM(AtMostOnce);
FDB_BOOLEAN_PARAM(TriedAllOptions);

// Stores state for a request made by the load balancer
template <class Request, class Interface, class Multi, bool P>
struct RequestData : NonCopyable {
	typedef ErrorOr<REPLY_TYPE(Request)> Reply;

	Future<Reply> response;
	Reference<ModelHolder> modelHolder;
	TriedAllOptions triedAllOptions{ false };

	bool requestStarted = false; // true once the request has been sent to an alternative
	bool requestProcessed = false; // true once a response has been received and handled by checkAndProcessResult

	// Whether or not the response future is valid
	// This is true once setupRequest is called, even though at that point the response is Never().
	bool isValid() { return response.isValid(); }

	static void maybeDuplicateTSSRequest(RequestStream<Request, P> const* stream,
	                                     Request& request,
	                                     QueueModel* model,
	                                     Future<Reply> ssResponse,
	                                     Reference<MultiInterface<Multi>> alternatives,
	                                     RequestStream<Request, P> Interface::*channel) {
		if (model) {
			// Send parallel request to TSS pair, if it exists
			Optional<TSSEndpointData> tssData = model->getTssData(stream->getEndpoint().token.first());

			if (tssData.present()) {
				CODE_PROBE(true, "duplicating request to TSS");
				resetReply(request);
				// FIXME: optimize to avoid creating new netNotifiedQueue for each message
				RequestStream<Request, P> tssRequestStream(tssData.get().endpoint);
				Future<ErrorOr<REPLY_TYPE(Request)>> fTssResult = tssRequestStream.tryGetReply(request);
				model->addActor.send(tssComparison(request,
				                                   ssResponse,
				                                   fTssResult,
				                                   tssData.get(),
				                                   stream->getEndpoint().token.first(),
				                                   alternatives,
				                                   channel));
			}
		}
	}

	// Initializes the request state and starts it, possibly after a backoff delay
	void startRequest(
	    double backoff,
	    TriedAllOptions triedAllOptions,
	    RequestStream<Request, P> const* stream,
	    Request& request,
	    QueueModel* model,
	    Reference<MultiInterface<Multi>> alternatives, // alternatives and channel passed through for TSS check
	    RequestStream<Request, P> Interface::*channel) {
		modelHolder = Reference<ModelHolder>();
		requestStarted = false;

		if (backoff > 0) {
			response = mapAsync(delay(backoff), [this, stream, &request, model, alternatives, channel](Void _) {
				requestStarted = true;
				modelHolder = Reference<ModelHolder>(new ModelHolder(model, stream->getEndpoint().token.first()));
				Future<Reply> resp = stream->tryGetReply(request);
				maybeDuplicateTSSRequest(stream, request, model, resp, alternatives, channel);
				return resp;
			});
		} else {
			requestStarted = true;
			modelHolder = Reference<ModelHolder>(new ModelHolder(model, stream->getEndpoint().token.first()));
			response = stream->tryGetReply(request);
			maybeDuplicateTSSRequest(stream, request, model, response, alternatives, channel);
		}

		requestProcessed = false;
		this->triedAllOptions = triedAllOptions;
	}

	// Implementation of the logic to handle a response.
	// Checks the state of the response, updates the queue model, and returns one of the following outcomes:
	// A return value of true means that the request completed successfully
	// A return value of false means that the request failed but should be retried
	// A return value with an error means that the error should be thrown back to original caller
	static ErrorOr<bool> checkAndProcessResultImpl(Reply const& result,
	                                               Reference<ModelHolder> modelHolder,
	                                               AtMostOnce atMostOnce,
	                                               TriedAllOptions triedAllOptions) {
		ASSERT(modelHolder);

		Optional<LoadBalancedReply> loadBalancedReply;
		if (!result.isError()) {
			loadBalancedReply = getLoadBalancedReply(&result.get());
		}

		int errCode;
		if (loadBalancedReply.present()) {
			errCode = loadBalancedReply.get().error.present() ? loadBalancedReply.get().error.get().code()
			                                                  : error_code_success;
		} else {
			errCode = result.isError() ? result.getError().code() : error_code_success;
		}

		bool maybeDelivered = errCode == error_code_broken_promise || errCode == error_code_request_maybe_delivered;
		bool receivedResponse =
		    loadBalancedReply.present() ? !loadBalancedReply.get().error.present() : result.present();
		receivedResponse = receivedResponse || (!maybeDelivered && errCode != error_code_process_behind);
		bool futureVersion = errCode == error_code_future_version || errCode == error_code_process_behind;

		modelHolder->release(
		    receivedResponse, futureVersion, loadBalancedReply.present() ? loadBalancedReply.get().penalty : -1.0);

		if (errCode == error_code_server_overloaded) {
			return false;
		}

		if (loadBalancedReply.present() && !loadBalancedReply.get().error.present()) {
			return true;
		}

		if (!loadBalancedReply.present() && result.present()) {
			return true;
		}

		if (receivedResponse) {
			return loadBalancedReply.present() ? loadBalancedReply.get().error.get() : result.getError();
		}

		if (atMostOnce && maybeDelivered) {
			return request_maybe_delivered();
		}

		if (triedAllOptions && errCode == error_code_process_behind) {
			return process_behind();
		}

		return false;
	}

	// Checks the state of the response, updates the queue model, and returns one of the following outcomes:
	// A return value of true means that the request completed successfully
	// A return value of false means that the request failed but should be retried
	// In the event of a non-retryable failure, an error is thrown indicating the failure
	bool checkAndProcessResult(AtMostOnce atMostOnce) {
		ASSERT(response.isReady());
		requestProcessed = true;

		ErrorOr<bool> outcome =
		    checkAndProcessResultImpl(response.get(), std::move(modelHolder), atMostOnce, triedAllOptions);

		if (outcome.isError()) {
			throw outcome.getError();
		} else if (!outcome.get()) {
			response = Future<Reply>();
		}

		return outcome.get();
	}

	// Convert this request to a lagging request. Such a request is no longer being waited on, but it still needs to be
	// processed so we can update the queue model.
	void makeLaggingRequest() {
		ASSERT(response.isValid());
		ASSERT(!response.isReady());
		ASSERT(modelHolder);
		ASSERT(modelHolder->model);

		QueueModel* model = modelHolder->model;
		if (model->laggingRequestCount > FLOW_KNOBS->MAX_LAGGING_REQUESTS_OUTSTANDING ||
		    model->laggingRequests.isReady()) {
			model->laggingRequests.cancel();
			model->laggingRequestCount = 0;
			model->addActor = PromiseStream<Future<Void>>();
			model->laggingRequests = actorCollection(model->addActor.getFuture(), &model->laggingRequestCount);
		}

		// We need to process the lagging request in order to update the queue model
		Reference<ModelHolder> holderCapture = std::move(modelHolder);
		auto triedAllOptionsCapture = triedAllOptions;
		Future<Void> updateModel = map(response, [holderCapture, triedAllOptionsCapture](Reply result) {
			checkAndProcessResultImpl(result, holderCapture, AtMostOnce::False, triedAllOptionsCapture);
			return Void();
		});
		model->addActor.send(updateModel);
	}

	~RequestData() {
		// If the request has been started but hasn't completed, mark it as a lagging request
		if (requestStarted && !requestProcessed && modelHolder && modelHolder->model) {
			makeLaggingRequest();
		}
	}
};

// Try to get a reply from one of the alternatives until success, cancellation, or certain errors.
// Load balancing has a budget to race requests to a second alternative if the first request is slow.
// Tries to take into account failMon's information for load balancing and avoiding failed servers.
// If ALL the servers are failed and the list of servers is not fresh, throws an exception to let the caller refresh the
// list of servers.
// When model is set, load balance among alternatives in the same DC aims to balance request queue length on these
// interfaces. If too many interfaces in the same DC are bad, try remote interfaces.
															#line 1136 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
namespace {
// This generated class is to be used only via loadBalance()
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P, class LoadBalanceActor>
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class LoadBalanceActorState {
															#line 1143 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	LoadBalanceActorState(Reference<MultiInterface<Multi>> const& alternatives,RequestStream<Request, P> Interface::* const& channel,Request const& request = Request(),TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint,AtMostOnce const& atMostOnce = AtMostOnce::False,QueueModel* const& model = nullptr) 
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		 : alternatives(alternatives),
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   channel(channel),
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   request(request),
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   taskID(taskID),
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   atMostOnce(atMostOnce),
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   model(model),
															#line 452 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   firstRequestData(),
															#line 453 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   secondRequestData(),
															#line 455 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   firstRequestEndpoint(),
															#line 456 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   secondDelay(Never()),
															#line 458 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   requestFinished(),
															#line 459 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   startTime(now()),
															#line 461 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   triedAllOptions(TriedAllOptions::False)
															#line 1174 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
	{
		fdb_probe_actor_create("loadBalance", reinterpret_cast<unsigned long>(this));

	}
	~LoadBalanceActorState() 
	{
		fdb_probe_actor_destroy("loadBalance", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 463 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			setReplyPriority(request, taskID);
															#line 464 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!alternatives)
															#line 1191 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 465 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				this->~LoadBalanceActorState();
															#line 1195 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				static_cast<LoadBalanceActor*>(this)->sendAndDelPromiseRef(Never());
				return 0;
			}
															#line 467 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ASSERT(alternatives->size());
															#line 469 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			bestAlt = deterministicRandom()->randomInt(0, alternatives->countBest());
															#line 470 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			nextAlt = deterministicRandom()->randomInt(0, std::max(alternatives->size() - 1, 1));
															#line 471 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (nextAlt >= bestAlt)
															#line 1207 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 472 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				nextAlt++;
															#line 1211 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 474 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (model)
															#line 1215 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 475 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				double bestMetric = 1e9;
															#line 476 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				double nextMetric = 1e9;
															#line 477 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				double bestTime = 1e9;
															#line 478 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				double nextTime = 1e9;
															#line 479 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				int badServers = 0;
															#line 481 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				for(int i = 0;i < alternatives->size();i++) {
															#line 484 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (badServers < std::min(i, FLOW_KNOBS->LOAD_BALANCE_MAX_BAD_OPTIONS + 1) && i == alternatives->countBest())
															#line 1231 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
						break;
					}
					else
					{
															#line 490 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (badServers == alternatives->countBest() && i == badServers)
															#line 1239 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						{
															#line 491 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							TraceEvent("AllLocalAlternativesFailed") .suppressFor(1.0) .detail("Alternatives", alternatives->description()) .detail("Total", alternatives->size()) .detail("Best", alternatives->countBest());
															#line 1243 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
					}
															#line 498 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					RequestStream<Request, P> const* thisStream = &alternatives->get(i, channel);
															#line 499 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (!IFailureMonitor::failureMonitor().getState(thisStream->getEndpoint()).failed)
															#line 1250 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 500 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						auto const& qd = model->getMeasurement(thisStream->getEndpoint().token.first());
															#line 501 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (now() > qd.failedUntil)
															#line 1256 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						{
															#line 502 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							double thisMetric = qd.smoothOutstanding.smoothTotal();
															#line 503 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							double thisTime = qd.latency;
															#line 504 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							if (FLOW_KNOBS->LOAD_BALANCE_PENALTY_IS_BAD && qd.penalty > 1.001)
															#line 1264 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							{
															#line 508 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								++badServers;
															#line 1268 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							}
															#line 511 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							if (thisMetric < bestMetric)
															#line 1272 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							{
															#line 512 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								if (i != bestAlt)
															#line 1276 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								{
															#line 513 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextAlt = bestAlt;
															#line 514 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextMetric = bestMetric;
															#line 515 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextTime = bestTime;
															#line 1284 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								}
															#line 517 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								bestAlt = i;
															#line 518 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								bestMetric = thisMetric;
															#line 519 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								bestTime = thisTime;
															#line 1292 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							}
							else
							{
															#line 520 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								if (thisMetric < nextMetric)
															#line 1298 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								{
															#line 521 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextAlt = i;
															#line 522 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextMetric = thisMetric;
															#line 523 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextTime = thisTime;
															#line 1306 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								}
							}
						}
						else
						{
															#line 526 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							++badServers;
															#line 1314 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						}
					}
					else
					{
															#line 529 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						++badServers;
															#line 1321 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
				}
															#line 532 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (nextMetric > 1e8)
															#line 1326 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 536 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					for(int i = alternatives->countBest();i < alternatives->size();i++) {
															#line 537 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						RequestStream<Request, P> const* thisStream = &alternatives->get(i, channel);
															#line 538 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						if (!IFailureMonitor::failureMonitor().getState(thisStream->getEndpoint()).failed)
															#line 1334 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
						{
															#line 539 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							auto const& qd = model->getMeasurement(thisStream->getEndpoint().token.first());
															#line 540 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
							if (now() > qd.failedUntil)
															#line 1340 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
							{
															#line 541 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								double thisMetric = qd.smoothOutstanding.smoothTotal();
															#line 542 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								double thisTime = qd.latency;
															#line 544 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
								if (thisMetric < nextMetric)
															#line 1348 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								{
															#line 545 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextAlt = i;
															#line 546 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextMetric = thisMetric;
															#line 547 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
									nextTime = thisTime;
															#line 1356 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
								}
							}
						}
					}
				}
															#line 554 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (nextTime < 1e9)
															#line 1364 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 556 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (bestTime > FLOW_KNOBS->INSTANT_SECOND_REQUEST_MULTIPLIER * (model->secondMultiplier * (nextTime) + FLOW_KNOBS->BASE_SECOND_REQUEST_TIME))
															#line 1368 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 558 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						secondDelay = Void();
															#line 1372 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
					else
					{
															#line 560 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						secondDelay = delay(model->secondMultiplier * nextTime + FLOW_KNOBS->BASE_SECOND_REQUEST_TIME);
															#line 1378 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
				}
				else
				{
															#line 563 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					secondDelay = Never();
															#line 1385 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
			}
															#line 567 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			startAlt = nextAlt;
															#line 568 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			startDistance = (bestAlt + alternatives->size() - startAlt) % alternatives->size();
															#line 570 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			numAttempts = 0;
															#line 571 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = 0;
															#line 573 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			;
															#line 1398 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
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
		this->~LoadBalanceActorState();
		static_cast<LoadBalanceActor*>(this)->sendErrorAndDelPromiseRef(error);
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
															#line 574 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (now() - startTime > (g_network->isSimulated() ? 30.0 : 600.0))
															#line 1428 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 575 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			TraceEvent ev(g_network->isSimulated() ? SevWarn : SevWarnAlways, "LoadBalanceTooLong");
															#line 576 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ev.suppressFor(1.0);
															#line 577 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ev.detail("Duration", now() - startTime);
															#line 578 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ev.detail("NumAttempts", numAttempts);
															#line 579 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ev.detail("Backoff", backoff);
															#line 580 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ev.detail("TriedAllOptions", triedAllOptions);
															#line 581 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (ev.isEnabled())
															#line 1444 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 582 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				ev.log();
															#line 583 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				for(int alternativeNum = 0;alternativeNum < alternatives->size();alternativeNum++) {
															#line 584 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					RequestStream<Request, P> const* thisStream = &alternatives->get(alternativeNum, channel);
															#line 585 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					TraceEvent(SevWarn, "LoadBalanceTooLongEndpoint") .detail("Addr", thisStream->getEndpoint().getPrimaryAddress()) .detail("Token", thisStream->getEndpoint().token) .detail("Failed", IFailureMonitor::failureMonitor().getState(thisStream->getEndpoint()).failed);
															#line 1454 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
			}
		}
															#line 596 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		stream = nullptr;
															#line 597 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		distance = LBDistance::Type();
															#line 598 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		for(int alternativeNum = 0;alternativeNum < alternatives->size();alternativeNum++) {
															#line 599 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			int useAlt = nextAlt;
															#line 600 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (nextAlt == startAlt)
															#line 1468 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 601 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				useAlt = bestAlt;
															#line 1472 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
			else
			{
															#line 602 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if ((nextAlt + alternatives->size() - startAlt) % alternatives->size() <= startDistance)
															#line 1478 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 603 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					useAlt = (nextAlt + alternatives->size() - 1) % alternatives->size();
															#line 1482 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
			}
															#line 605 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			stream = &alternatives->get(useAlt, channel);
															#line 606 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			distance = alternatives->getDistance(useAlt);
															#line 607 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!IFailureMonitor::failureMonitor().getState(stream->getEndpoint()).failed && (!firstRequestEndpoint.present() || stream->getEndpoint().token.first() != firstRequestEndpoint.get()))
															#line 1491 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
				break;
			}
															#line 610 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			nextAlt = (nextAlt + 1) % alternatives->size();
															#line 611 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (nextAlt == startAlt)
															#line 1499 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 612 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				triedAllOptions = TriedAllOptions::True;
															#line 1503 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 613 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			stream = nullptr;
															#line 614 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			distance = LBDistance::DISTANT;
															#line 1509 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 617 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (!stream && !firstRequestData.isValid())
															#line 1513 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 620 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			std::vector<Future<Void>> ok(alternatives->size());
															#line 621 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			for(int i = 0;i < ok.size();i++) {
															#line 622 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				ok[i] = IFailureMonitor::failureMonitor().onStateEqual(alternatives->get(i, channel).getEndpoint(), FailureStatus(false));
															#line 1521 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 626 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			Future<Void> okFuture = quorum(ok, 1);
															#line 628 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!alternatives->alwaysFresh())
															#line 1527 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 630 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (now() - g_network->networkInfo.newestAlternativesFailure > 1 || deterministicRandom()->random01() < 0.01)
															#line 1531 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 632 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					TraceEvent("AllAlternativesFailed").detail("Alternatives", alternatives->description());
															#line 1535 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
															#line 634 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				StrictFuture<Void> __when_expr_0 = allAlternativesFailedDelay(okFuture);
															#line 634 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (static_cast<LoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1541 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
				static_cast<LoadBalanceActor*>(this)->actor_wait_state = 1;
															#line 634 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 0, Void >*>(static_cast<LoadBalanceActor*>(this)));
															#line 1546 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				loopDepth = 0;
			}
			else
			{
															#line 636 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				StrictFuture<Void> __when_expr_1 = okFuture;
															#line 636 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (static_cast<LoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1555 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when2(__when_expr_1.get(), loopDepth); };
				static_cast<LoadBalanceActor*>(this)->actor_wait_state = 2;
															#line 636 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 1, Void >*>(static_cast<LoadBalanceActor*>(this)));
															#line 1560 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				loopDepth = 0;
			}
		}
		else
		{
															#line 640 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!stream)
															#line 1568 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 642 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				StrictFuture<ErrorOr<REPLY_TYPE(Request)>> __when_expr_2 = firstRequestData.response;
															#line 642 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (static_cast<LoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 1574 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when3(__when_expr_2.get(), loopDepth); };
				static_cast<LoadBalanceActor*>(this)->actor_wait_state = 3;
															#line 642 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*>(static_cast<LoadBalanceActor*>(this)));
															#line 1579 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				loopDepth = 0;
			}
			else
			{
															#line 648 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (firstRequestData.isValid())
															#line 1586 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 650 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (distance == LBDistance::DISTANT)
															#line 1590 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 651 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						TraceEvent("LBDistant2nd") .suppressFor(0.1) .detail("Distance", (int)distance) .detail("BackOff", backoff) .detail("TriedAllOptions", triedAllOptions) .detail("Alternatives", alternatives->description()) .detail("Token", stream->getEndpoint().token) .detail("Total", alternatives->size()) .detail("Best", alternatives->countBest()) .detail("Attempts", numAttempts);
															#line 1594 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
															#line 662 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					secondRequestData.startRequest(backoff, triedAllOptions, stream, request, model, alternatives, channel);
															#line 664 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					;
															#line 1600 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					loopDepth = a_body1loopBody1loopHead1(loopDepth);
				}
				else
				{
															#line 689 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					if (distance == LBDistance::DISTANT)
															#line 1607 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					{
															#line 690 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
						TraceEvent("LBDistant") .suppressFor(0.1) .detail("Distance", (int)distance) .detail("BackOff", backoff) .detail("TriedAllOptions", triedAllOptions) .detail("Alternatives", alternatives->description()) .detail("Token", stream->getEndpoint().token) .detail("Total", alternatives->size()) .detail("Best", alternatives->countBest()) .detail("Attempts", numAttempts);
															#line 1611 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					}
															#line 701 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					firstRequestData.startRequest(backoff, triedAllOptions, stream, request, model, alternatives, channel);
															#line 702 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					firstRequestEndpoint = stream->getEndpoint().token.first();
															#line 704 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					;
															#line 1619 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
					loopDepth = a_body1loopBody1loopHead2(loopDepth);
				}
			}
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
															#line 740 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		nextAlt = (nextAlt + 1) % alternatives->size();
															#line 741 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (nextAlt == startAlt)
															#line 1633 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 742 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			triedAllOptions = TriedAllOptions::True;
															#line 1637 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 743 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		resetReply(request, taskID);
															#line 744 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		secondDelay = Never();
															#line 1643 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont11(int loopDepth) 
	{
															#line 639 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		numAttempts = 0;
															#line 1652 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont13(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont13(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont13(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont13(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<LoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont15(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont15(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont15(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont15(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<LoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1loopBody1cont16(int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont17(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
															#line 643 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 1841 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 644 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 1845 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 647 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 1853 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1cont16(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont17(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
															#line 643 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 1862 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 644 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 1866 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 647 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 1874 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1cont16(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when3(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont17(result, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when3(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont17(std::move(result), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<LoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >::remove();

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1when3(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1when3(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
	int a_body1loopBody1cont18(int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont16(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont19(int loopDepth) 
	{
															#line 682 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (++numAttempts >= alternatives->size())
															#line 1964 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 683 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = std::min( FLOW_KNOBS->LOAD_BALANCE_MAX_BACKOFF, std::max(FLOW_KNOBS->LOAD_BALANCE_START_BACKOFF, backoff * FLOW_KNOBS->LOAD_BALANCE_BACKOFF_RATE));
															#line 1968 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		loopDepth = a_body1loopBody1cont18(loopDepth);

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
															#line 665 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Request)>> __when_expr_3 = firstRequestData.response.isValid() ? firstRequestData.response : Never();
															#line 664 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 2));
															#line 1987 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_3.isReady()) { if (__when_expr_3.isError()) return a_body1Catch1(__when_expr_3.getError(), std::max(0, loopDepth - 2)); else return a_body1loopBody1loopBody1when1(__when_expr_3.get(), loopDepth); };
															#line 673 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Request)>> __when_expr_4 = secondRequestData.response;
															#line 1991 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_4.isReady()) { if (__when_expr_4.isError()) return a_body1Catch1(__when_expr_4.getError(), std::max(0, loopDepth - 2)); else return a_body1loopBody1loopBody1when2(__when_expr_4.get(), loopDepth); };
		static_cast<LoadBalanceActor*>(this)->actor_wait_state = 4;
															#line 665 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_3.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 3, ErrorOr<REPLY_TYPE(Request)> >*>(static_cast<LoadBalanceActor*>(this)));
															#line 673 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_4.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 4, ErrorOr<REPLY_TYPE(Request)> >*>(static_cast<LoadBalanceActor*>(this)));
															#line 1998 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1break1(int loopDepth) 
	{
		try {
			return a_body1loopBody1cont19(loopDepth);
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
		if (loopDepth == 0) return a_body1loopBody1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when1(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
															#line 667 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 2026 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 668 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2030 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 671 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 2038 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when1(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
															#line 667 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 2047 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 668 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2051 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 671 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 2059 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when2(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
															#line 674 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (secondRequestData.checkAndProcessResult(atMostOnce))
															#line 2068 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 675 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2072 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
		return a_body1loopBody1break1(loopDepth==0?0:loopDepth-1); // break

		return loopDepth;
	}
	int a_body1loopBody1loopBody1when2(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
															#line 674 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (secondRequestData.checkAndProcessResult(atMostOnce))
															#line 2086 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 675 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2090 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
		return a_body1loopBody1break1(loopDepth==0?0:loopDepth-1); // break

		return loopDepth;
	}
	void a_exitChoose4() 
	{
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<LoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 3, ErrorOr<REPLY_TYPE(Request)> >::remove();
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 4, ErrorOr<REPLY_TYPE(Request)> >::remove();

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 3, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1loopBody1loopBody1when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 3, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1loopBody1loopBody1when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 3, ErrorOr<REPLY_TYPE(Request)> >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 3);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 3);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 4, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1loopBody1loopBody1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 4);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 4, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1loopBody1loopBody1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 4);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 4, ErrorOr<REPLY_TYPE(Request)> >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 4);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose4();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 4);

	}
	int a_body1loopBody1cont21(int loopDepth) 
	{
															#line 733 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (++numAttempts >= alternatives->size())
															#line 2225 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 734 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = std::min( FLOW_KNOBS->LOAD_BALANCE_MAX_BACKOFF, std::max(FLOW_KNOBS->LOAD_BALANCE_START_BACKOFF, backoff * FLOW_KNOBS->LOAD_BALANCE_BACKOFF_RATE));
															#line 2229 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		loopDepth = a_body1loopBody1cont18(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopHead2(int loopDepth) 
	{
		int oldLoopDepth = ++loopDepth;
		while (loopDepth == oldLoopDepth) loopDepth = a_body1loopBody1loopBody2(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody2(int loopDepth) 
	{
															#line 706 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Request)>> __when_expr_5 = firstRequestData.response;
															#line 705 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 2));
															#line 2248 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_5.isReady()) { if (__when_expr_5.isError()) return a_body1Catch1(__when_expr_5.getError(), std::max(0, loopDepth - 2)); else return a_body1loopBody1loopBody2when1(__when_expr_5.get(), loopDepth); };
															#line 722 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<Void> __when_expr_6 = secondDelay;
															#line 2252 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_6.isReady()) { if (__when_expr_6.isError()) return a_body1Catch1(__when_expr_6.getError(), std::max(0, loopDepth - 2)); else return a_body1loopBody1loopBody2when2(__when_expr_6.get(), loopDepth); };
		static_cast<LoadBalanceActor*>(this)->actor_wait_state = 5;
															#line 706 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_5.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 5, ErrorOr<REPLY_TYPE(Request)> >*>(static_cast<LoadBalanceActor*>(this)));
															#line 722 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_6.addCallbackAndClear(static_cast<ActorCallback< LoadBalanceActor, 6, Void >*>(static_cast<LoadBalanceActor*>(this)));
															#line 2259 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1break2(int loopDepth) 
	{
		try {
			return a_body1loopBody1cont21(loopDepth);
		}
		catch (Error& error) {
			loopDepth = a_body1Catch1(error, std::max(0, loopDepth - 1));
		} catch (...) {
			loopDepth = a_body1Catch1(unknown_error(), std::max(0, loopDepth - 1));
		}

		return loopDepth;
	}
	int a_body1loopBody1loopBody2cont1(int loopDepth) 
	{
		if (loopDepth == 0) return a_body1loopBody1loopHead2(0);

		return loopDepth;
	}
	int a_body1loopBody1loopBody2when1(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
															#line 707 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (model)
															#line 2287 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 708 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondMultiplier = std::max(model->secondMultiplier - FLOW_KNOBS->SECOND_REQUEST_MULTIPLIER_DECAY, 1.0);
															#line 710 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondBudget = std::min(model->secondBudget + FLOW_KNOBS->SECOND_REQUEST_BUDGET_GROWTH, FLOW_KNOBS->SECOND_REQUEST_MAX_BUDGET);
															#line 2293 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 715 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 2297 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 716 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2301 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 719 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 2309 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		return a_body1loopBody1break2(loopDepth==0?0:loopDepth-1); // break

		return loopDepth;
	}
	int a_body1loopBody1loopBody2when1(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
															#line 707 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (model)
															#line 2318 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 708 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondMultiplier = std::max(model->secondMultiplier - FLOW_KNOBS->SECOND_REQUEST_MULTIPLIER_DECAY, 1.0);
															#line 710 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondBudget = std::min(model->secondBudget + FLOW_KNOBS->SECOND_REQUEST_BUDGET_GROWTH, FLOW_KNOBS->SECOND_REQUEST_MAX_BUDGET);
															#line 2324 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 715 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (firstRequestData.checkAndProcessResult(atMostOnce))
															#line 2328 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 716 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<LoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~LoadBalanceActorState(); static_cast<LoadBalanceActor*>(this)->destroy(); return 0; }
															#line 2332 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<LoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~LoadBalanceActorState();
			static_cast<LoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 719 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		firstRequestEndpoint = Optional<uint64_t>();
															#line 2340 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		return a_body1loopBody1break2(loopDepth==0?0:loopDepth-1); // break

		return loopDepth;
	}
	int a_body1loopBody1loopBody2when2(Void const& _,int loopDepth) 
	{
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		secondDelay = Never();
															#line 724 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (model && model->secondBudget >= 1.0)
															#line 2351 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 725 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondMultiplier += FLOW_KNOBS->SECOND_REQUEST_MULTIPLIER_GROWTH;
															#line 726 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondBudget -= 1.0;
															#line 2357 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			return a_body1loopBody1break2(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1loopBody2cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1loopBody2when2(Void && _,int loopDepth) 
	{
															#line 723 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		secondDelay = Never();
															#line 724 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (model && model->secondBudget >= 1.0)
															#line 2370 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 725 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondMultiplier += FLOW_KNOBS->SECOND_REQUEST_MULTIPLIER_GROWTH;
															#line 726 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			model->secondBudget -= 1.0;
															#line 2376 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			return a_body1loopBody1break2(loopDepth==0?0:loopDepth-1); // break
		}
		loopDepth = a_body1loopBody1loopBody2cont1(loopDepth);

		return loopDepth;
	}
	void a_exitChoose5() 
	{
		if (static_cast<LoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<LoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 5, ErrorOr<REPLY_TYPE(Request)> >::remove();
		static_cast<LoadBalanceActor*>(this)->ActorCallback< LoadBalanceActor, 6, Void >::remove();

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 5, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1loopBody1loopBody2when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 5);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 5, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1loopBody1loopBody2when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 5);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 5, ErrorOr<REPLY_TYPE(Request)> >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 5);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 5);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 6, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1loopBody1loopBody2when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 6);

	}
	void a_callback_fire(ActorCallback< LoadBalanceActor, 6, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1loopBody1loopBody2when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 6);

	}
	void a_callback_error(ActorCallback< LoadBalanceActor, 6, Void >*,Error err) 
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), 6);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose5();
		try {
			a_body1Catch1(err, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), 6);

	}
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Reference<MultiInterface<Multi>> alternatives;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestStream<Request, P> Interface::* channel;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Request request;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TaskPriority taskID;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	AtMostOnce atMostOnce;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	QueueModel* model;
															#line 452 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestData<Request, Interface, Multi, P> firstRequestData;
															#line 453 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestData<Request, Interface, Multi, P> secondRequestData;
															#line 455 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Optional<uint64_t> firstRequestEndpoint;
															#line 456 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Future<Void> secondDelay;
															#line 458 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Promise<Void> requestFinished;
															#line 459 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double startTime;
															#line 461 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TriedAllOptions triedAllOptions;
															#line 469 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int bestAlt;
															#line 470 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int nextAlt;
															#line 567 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int startAlt;
															#line 568 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int startDistance;
															#line 570 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int numAttempts;
															#line 571 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double backoff;
															#line 596 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestStream<Request, P> const* stream;
															#line 597 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	LBDistance::Type distance;
															#line 2546 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
};
// This generated class is to be used only via loadBalance()
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P>
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class LoadBalanceActor final : public Actor<REPLY_TYPE(Request)>, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 0, Void >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 1, Void >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 3, ErrorOr<REPLY_TYPE(Request)> >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 4, ErrorOr<REPLY_TYPE(Request)> >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 5, ErrorOr<REPLY_TYPE(Request)> >, public ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 6, Void >, public FastAllocated<LoadBalanceActor<Interface, Request, Multi, P>>, public LoadBalanceActorState<Interface, Request, Multi, P, LoadBalanceActor<Interface, Request, Multi, P>> {
															#line 2553 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
	using FastAllocated<LoadBalanceActor<Interface, Request, Multi, P>>::operator new;
	using FastAllocated<LoadBalanceActor<Interface, Request, Multi, P>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(17612208726777054720UL, 6495730042038905344UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Request)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 0, Void >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 1, Void >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 3, ErrorOr<REPLY_TYPE(Request)> >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 4, ErrorOr<REPLY_TYPE(Request)> >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 5, ErrorOr<REPLY_TYPE(Request)> >;
friend struct ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 6, Void >;
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	LoadBalanceActor(Reference<MultiInterface<Multi>> const& alternatives,RequestStream<Request, P> Interface::* const& channel,Request const& request = Request(),TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint,AtMostOnce const& atMostOnce = AtMostOnce::False,QueueModel* const& model = nullptr) 
															#line 2576 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		 : Actor<REPLY_TYPE(Request)>(),
		   LoadBalanceActorState<Interface, Request, Multi, P, LoadBalanceActor<Interface, Request, Multi, P>>(alternatives, channel, request, taskID, atMostOnce, model),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("loadBalance", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(12051063900488922880UL, 14234974990573568000UL);
		ActorExecutionContextHelper __helper(static_cast<LoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("loadBalance");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("loadBalance", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >*)0, actor_cancelled()); break;
		case 4: this->a_callback_error((ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 3, ErrorOr<REPLY_TYPE(Request)> >*)0, actor_cancelled()); break;
		case 5: this->a_callback_error((ActorCallback< LoadBalanceActor<Interface, Request, Multi, P>, 5, ErrorOr<REPLY_TYPE(Request)> >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P>
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Request)> loadBalance( Reference<MultiInterface<Multi>> const& alternatives, RequestStream<Request, P> Interface::* const& channel, Request const& request = Request(), TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint, AtMostOnce const& atMostOnce = AtMostOnce::False, QueueModel* const& model = nullptr ) {
															#line 442 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	return Future<REPLY_TYPE(Request)>(new LoadBalanceActor<Interface, Request, Multi, P>(alternatives, channel, request, taskID, atMostOnce, model));
															#line 2615 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
}

#line 747 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"

// Subclasses must initialize all members in their default constructors
// Subclasses must serialize all members
struct BasicLoadBalancedReply {
	int processBusyTime;
	BasicLoadBalancedReply() : processBusyTime(0) {}
};

Optional<BasicLoadBalancedReply> getBasicLoadBalancedReply(const BasicLoadBalancedReply* reply);
Optional<BasicLoadBalancedReply> getBasicLoadBalancedReply(const void*);

// A simpler version of LoadBalance that does not send second requests where the list of servers are always fresh
//
// If |alternativeChosen| is not null, then atMostOnce must be True, and if the returned future completes successfully
// then *alternativeChosen will be the alternative to which the message was sent. *alternativeChosen must outlive the
// returned future.
															#line 2635 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
namespace {
// This generated class is to be used only via basicLoadBalance()
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P, class BasicLoadBalanceActor>
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class BasicLoadBalanceActorState {
															#line 2642 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	BasicLoadBalanceActorState(Reference<ModelInterface<Multi>> const& alternatives,RequestStream<Request, P> Interface::* const& channel,Request const& request = Request(),TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint,AtMostOnce const& atMostOnce = AtMostOnce::False,int* const& alternativeChosen = nullptr) 
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		 : alternatives(alternatives),
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   channel(channel),
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   request(request),
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   taskID(taskID),
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   atMostOnce(atMostOnce),
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		   alternativeChosen(alternativeChosen)
															#line 2659 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
	{
		fdb_probe_actor_create("basicLoadBalance", reinterpret_cast<unsigned long>(this));

	}
	~BasicLoadBalanceActorState() 
	{
		fdb_probe_actor_destroy("basicLoadBalance", reinterpret_cast<unsigned long>(this));

	}
	int a_body1(int loopDepth=0) 
	{
		try {
															#line 770 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ASSERT(alternativeChosen == nullptr || atMostOnce == AtMostOnce::True);
															#line 771 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			setReplyPriority(request, taskID);
															#line 772 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!alternatives)
															#line 2678 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 773 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				this->~BasicLoadBalanceActorState();
															#line 2682 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				static_cast<BasicLoadBalanceActor*>(this)->sendAndDelPromiseRef(Never());
				return 0;
			}
															#line 775 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			ASSERT(alternatives->size() && alternatives->alwaysFresh());
															#line 777 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			bestAlt = alternatives->getBest();
															#line 778 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			nextAlt = deterministicRandom()->randomInt(0, std::max(alternatives->size() - 1, 1));
															#line 779 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (nextAlt >= bestAlt)
															#line 2694 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 780 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				nextAlt++;
															#line 2698 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 782 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			startAlt = nextAlt;
															#line 783 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			startDistance = (bestAlt + alternatives->size() - startAlt) % alternatives->size();
															#line 785 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			numAttempts = 0;
															#line 786 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = 0;
															#line 787 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			useAlt = int();
															#line 788 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			;
															#line 2712 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
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
		this->~BasicLoadBalanceActorState();
		static_cast<BasicLoadBalanceActor*>(this)->sendErrorAndDelPromiseRef(error);
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
															#line 790 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		stream = nullptr;
															#line 791 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		for(int alternativeNum = 0;alternativeNum < alternatives->size();alternativeNum++) {
															#line 792 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			useAlt = nextAlt;
															#line 793 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (nextAlt == startAlt)
															#line 2748 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 794 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				useAlt = bestAlt;
															#line 2752 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
			else
			{
															#line 795 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if ((nextAlt + alternatives->size() - startAlt) % alternatives->size() <= startDistance)
															#line 2758 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				{
															#line 796 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
					useAlt = (nextAlt + alternatives->size() - 1) % alternatives->size();
															#line 2762 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				}
			}
															#line 798 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			stream = &alternatives->get(useAlt, channel);
															#line 799 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (alternativeChosen != nullptr)
															#line 2769 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 800 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				*alternativeChosen = useAlt;
															#line 2773 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 802 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!IFailureMonitor::failureMonitor().getState(stream->getEndpoint()).failed)
															#line 2777 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
				break;
			}
															#line 804 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			nextAlt = (nextAlt + 1) % alternatives->size();
															#line 805 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			stream = nullptr;
															#line 2785 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 808 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (!stream)
															#line 2789 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 811 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			std::vector<Future<Void>> ok(alternatives->size());
															#line 812 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			for(int i = 0;i < ok.size();i++) {
															#line 813 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				ok[i] = IFailureMonitor::failureMonitor().onStateEqual(alternatives->get(i, channel).getEndpoint(), FailureStatus(false));
															#line 2797 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 816 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			StrictFuture<Void> __when_expr_0 = quorum(ok, 1);
															#line 816 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2803 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			if (__when_expr_0.isReady()) { if (__when_expr_0.isError()) return a_body1Catch1(__when_expr_0.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when1(__when_expr_0.get(), loopDepth); };
			static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 1;
															#line 816 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			__when_expr_0.addCallbackAndClear(static_cast<ActorCallback< BasicLoadBalanceActor, 0, Void >*>(static_cast<BasicLoadBalanceActor*>(this)));
															#line 2808 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			loopDepth = 0;
		}
		else
		{
															#line 820 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (backoff > 0.0)
															#line 2815 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 821 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				StrictFuture<Void> __when_expr_1 = delay(backoff);
															#line 821 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2821 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				if (__when_expr_1.isReady()) { if (__when_expr_1.isError()) return a_body1Catch1(__when_expr_1.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1when2(__when_expr_1.get(), loopDepth); };
				static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 2;
															#line 821 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				__when_expr_1.addCallbackAndClear(static_cast<ActorCallback< BasicLoadBalanceActor, 1, Void >*>(static_cast<BasicLoadBalanceActor*>(this)));
															#line 2826 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
				loopDepth = 0;
			}
			else
			{
				loopDepth = a_body1loopBody1cont11(loopDepth);
			}
		}

		return loopDepth;
	}
	int a_body1loopBody1cont1(int loopDepth) 
	{
															#line 851 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		nextAlt = (nextAlt + 1) % alternatives->size();
															#line 852 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		resetReply(request, taskID);
															#line 2843 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (loopDepth == 0) return a_body1loopHead1(0);

		return loopDepth;
	}
	int a_body1loopBody1cont8(Void const& _,int loopDepth) 
	{
															#line 818 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		numAttempts = 0;
															#line 2852 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont8(Void && _,int loopDepth) 
	{
															#line 818 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		numAttempts = 0;
															#line 2861 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont8(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when1(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont8(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose1() 
	{
		if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<BasicLoadBalanceActor*>(this)->ActorCallback< BasicLoadBalanceActor, 0, Void >::remove();

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 0, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 0, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	void a_callback_error(ActorCallback< BasicLoadBalanceActor, 0, Void >*,Error err) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 0);

	}
	int a_body1loopBody1cont11(int loopDepth) 
	{
															#line 824 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		StrictFuture<ErrorOr<REPLY_TYPE(Request)>> __when_expr_2 = stream->tryGetReply(request);
															#line 824 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state < 0) return a_body1Catch1(actor_cancelled(), std::max(0, loopDepth - 1));
															#line 2947 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		if (__when_expr_2.isReady()) { if (__when_expr_2.isError()) return a_body1Catch1(__when_expr_2.getError(), std::max(0, loopDepth - 1)); else return a_body1loopBody1cont11when1(__when_expr_2.get(), loopDepth); };
		static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 3;
															#line 824 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		__when_expr_2.addCallbackAndClear(static_cast<ActorCallback< BasicLoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*>(static_cast<BasicLoadBalanceActor*>(this)));
															#line 2952 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		loopDepth = 0;

		return loopDepth;
	}
	int a_body1loopBody1cont12(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont12(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void const& _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont12(_, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1when2(Void && _,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont12(std::move(_), loopDepth);

		return loopDepth;
	}
	void a_exitChoose2() 
	{
		if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<BasicLoadBalanceActor*>(this)->ActorCallback< BasicLoadBalanceActor, 1, Void >::remove();

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 1, Void >*,Void const& value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1when2(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 1, Void >*,Void && value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose2();
		try {
			a_body1loopBody1when2(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	void a_callback_error(ActorCallback< BasicLoadBalanceActor, 1, Void >*,Error err) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 1);

	}
	int a_body1loopBody1cont11cont1(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
															#line 826 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (result.present())
															#line 3048 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 827 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			Optional<BasicLoadBalancedReply> loadBalancedReply = getBasicLoadBalancedReply(&result.get());
															#line 828 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (loadBalancedReply.present())
															#line 3054 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 829 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				alternatives->updateRecent(useAlt, loadBalancedReply.get().processBusyTime);
															#line 3058 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 832 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<BasicLoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~BasicLoadBalanceActorState(); static_cast<BasicLoadBalanceActor*>(this)->destroy(); return 0; }
															#line 3062 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<BasicLoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~BasicLoadBalanceActorState();
			static_cast<BasicLoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 835 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (result.getError().code() != error_code_broken_promise && result.getError().code() != error_code_request_maybe_delivered)
															#line 3070 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 837 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			return a_body1Catch1(result.getError(), std::max(0, loopDepth - 1));
															#line 3074 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 840 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (atMostOnce)
															#line 3078 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 841 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			return a_body1Catch1(request_maybe_delivered(), std::max(0, loopDepth - 1));
															#line 3082 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 844 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (++numAttempts >= alternatives->size())
															#line 3086 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 845 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = std::min( FLOW_KNOBS->LOAD_BALANCE_MAX_BACKOFF, std::max(FLOW_KNOBS->LOAD_BALANCE_START_BACKOFF, backoff * FLOW_KNOBS->LOAD_BALANCE_BACKOFF_RATE));
															#line 3090 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont11cont1(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
															#line 826 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (result.present())
															#line 3100 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 827 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			Optional<BasicLoadBalancedReply> loadBalancedReply = getBasicLoadBalancedReply(&result.get());
															#line 828 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (loadBalancedReply.present())
															#line 3106 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			{
															#line 829 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
				alternatives->updateRecent(useAlt, loadBalancedReply.get().processBusyTime);
															#line 3110 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			}
															#line 832 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			if (!static_cast<BasicLoadBalanceActor*>(this)->SAV<REPLY_TYPE(Request)>::futures) { (void)(result.get()); this->~BasicLoadBalanceActorState(); static_cast<BasicLoadBalanceActor*>(this)->destroy(); return 0; }
															#line 3114 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
			new (&static_cast<BasicLoadBalanceActor*>(this)->SAV< REPLY_TYPE(Request) >::value()) REPLY_TYPE(Request)(result.get());
			this->~BasicLoadBalanceActorState();
			static_cast<BasicLoadBalanceActor*>(this)->finishSendAndDelPromiseRef();
			return 0;
		}
															#line 835 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (result.getError().code() != error_code_broken_promise && result.getError().code() != error_code_request_maybe_delivered)
															#line 3122 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 837 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			return a_body1Catch1(result.getError(), std::max(0, loopDepth - 1));
															#line 3126 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 840 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (atMostOnce)
															#line 3130 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 841 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			return a_body1Catch1(request_maybe_delivered(), std::max(0, loopDepth - 1));
															#line 3134 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
															#line 844 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
		if (++numAttempts >= alternatives->size())
															#line 3138 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		{
															#line 845 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
			backoff = std::min( FLOW_KNOBS->LOAD_BALANCE_MAX_BACKOFF, std::max(FLOW_KNOBS->LOAD_BALANCE_START_BACKOFF, backoff * FLOW_KNOBS->LOAD_BALANCE_BACKOFF_RATE));
															#line 3142 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		}
		loopDepth = a_body1loopBody1cont1(loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont11when1(ErrorOr<REPLY_TYPE(Request)> const& result,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11cont1(result, loopDepth);

		return loopDepth;
	}
	int a_body1loopBody1cont11when1(ErrorOr<REPLY_TYPE(Request)> && result,int loopDepth) 
	{
		loopDepth = a_body1loopBody1cont11cont1(std::move(result), loopDepth);

		return loopDepth;
	}
	void a_exitChoose3() 
	{
		if (static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state > 0) static_cast<BasicLoadBalanceActor*>(this)->actor_wait_state = 0;
		static_cast<BasicLoadBalanceActor*>(this)->ActorCallback< BasicLoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >::remove();

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> const& value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont11when1(value, 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_fire(ActorCallback< BasicLoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,ErrorOr<REPLY_TYPE(Request)> && value) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(9578512156108914944UL, 107643746863906816UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		a_exitChoose3();
		try {
			a_body1loopBody1cont11when1(std::move(value), 0);
		}
		catch (Error& error) {
			a_body1Catch1(error, 0);
		} catch (...) {
			a_body1Catch1(unknown_error(), 0);
		}
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
	void a_callback_error(ActorCallback< BasicLoadBalanceActor, 2, ErrorOr<REPLY_TYPE(Request)> >*,Error err) 
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5187328219730237440UL, 3113259079076601088UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
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
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), 2);

	}
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Reference<ModelInterface<Multi>> alternatives;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestStream<Request, P> Interface::* channel;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	Request request;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	TaskPriority taskID;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	AtMostOnce atMostOnce;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int* alternativeChosen;
															#line 777 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int bestAlt;
															#line 778 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int nextAlt;
															#line 782 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int startAlt;
															#line 783 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int startDistance;
															#line 785 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int numAttempts;
															#line 786 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	double backoff;
															#line 787 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	int useAlt;
															#line 790 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	RequestStream<Request, P> const* stream;
															#line 3251 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
};
// This generated class is to be used only via basicLoadBalance()
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P>
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
class BasicLoadBalanceActor final : public Actor<REPLY_TYPE(Request)>, public ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 0, Void >, public ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 1, Void >, public ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >, public FastAllocated<BasicLoadBalanceActor<Interface, Request, Multi, P>>, public BasicLoadBalanceActorState<Interface, Request, Multi, P, BasicLoadBalanceActor<Interface, Request, Multi, P>> {
															#line 3258 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
public:
	using FastAllocated<BasicLoadBalanceActor<Interface, Request, Multi, P>>::operator new;
	using FastAllocated<BasicLoadBalanceActor<Interface, Request, Multi, P>>::operator delete;
	static constexpr ActorIdentifier __actorIdentifier = UID(9129417207408215040UL, 15556749342435723776UL);
	ActiveActorHelper activeActorHelper;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
    void destroy() override {
        activeActorHelper.~ActiveActorHelper();
        static_cast<Actor<REPLY_TYPE(Request)>*>(this)->~Actor();
        operator delete(this);
    }
#pragma clang diagnostic pop
friend struct ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 0, Void >;
friend struct ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 1, Void >;
friend struct ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >;
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	BasicLoadBalanceActor(Reference<ModelInterface<Multi>> const& alternatives,RequestStream<Request, P> Interface::* const& channel,Request const& request = Request(),TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint,AtMostOnce const& atMostOnce = AtMostOnce::False,int* const& alternativeChosen = nullptr) 
															#line 3277 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
		 : Actor<REPLY_TYPE(Request)>(),
		   BasicLoadBalanceActorState<Interface, Request, Multi, P, BasicLoadBalanceActor<Interface, Request, Multi, P>>(alternatives, channel, request, taskID, atMostOnce, alternativeChosen),
		   activeActorHelper(__actorIdentifier)
	{
		fdb_probe_actor_enter("basicLoadBalance", reinterpret_cast<unsigned long>(this), -1);
		#ifdef WITH_ACAC
		static constexpr ActorBlockIdentifier __identifier = UID(5600668509463549440UL, 16700316307983848448UL);
		ActorExecutionContextHelper __helper(static_cast<BasicLoadBalanceActor*>(this)->activeActorHelper.actorID, __identifier);
		#endif // WITH_ACAC
		#ifdef ENABLE_SAMPLING
		this->lineage.setActorName("basicLoadBalance");
		LineageScope _(&this->lineage);
		#endif
		this->a_body1();
		fdb_probe_actor_exit("basicLoadBalance", reinterpret_cast<unsigned long>(this), -1);

	}
	void cancel() override
	{
		auto wait_state = this->actor_wait_state;
		this->actor_wait_state = -1;
		switch (wait_state) {
		case 1: this->a_callback_error((ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 0, Void >*)0, actor_cancelled()); break;
		case 2: this->a_callback_error((ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 1, Void >*)0, actor_cancelled()); break;
		case 3: this->a_callback_error((ActorCallback< BasicLoadBalanceActor<Interface, Request, Multi, P>, 2, ErrorOr<REPLY_TYPE(Request)> >*)0, actor_cancelled()); break;
		}

	}
};
} // namespace
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
template <class Interface, class Request, class Multi, bool P>
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
[[nodiscard]] Future<REPLY_TYPE(Request)> basicLoadBalance( Reference<ModelInterface<Multi>> const& alternatives, RequestStream<Request, P> Interface::* const& channel, Request const& request = Request(), TaskPriority const& taskID = TaskPriority::DefaultPromiseEndpoint, AtMostOnce const& atMostOnce = AtMostOnce::False, int* const& alternativeChosen = nullptr ) {
															#line 763 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"
	return Future<REPLY_TYPE(Request)>(new BasicLoadBalanceActor<Interface, Request, Multi, P>(alternatives, channel, request, taskID, atMostOnce, alternativeChosen));
															#line 3314 "/Users/gyming/Documents/USC/CATPS/Task/build/fdbrpc/include/fdbrpc/LoadBalance.actor.g.h"
}

#line 855 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/fdbrpc/include/fdbrpc/LoadBalance.actor.h"

#include "flow/unactorcompiler.h"

#endif
