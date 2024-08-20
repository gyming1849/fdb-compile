#define POST_ACTOR_COMPILER 1
#line 1 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/EventTypes.actor.h"
/*
 * EventTypes.actor.h
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
#if defined(NO_INTELLISENSE) && !defined(FLOW_EVENTTYPES_ACTOR_G_H)
#define FLOW_EVENTTYPES_ACTOR_G_H
#include "flow/EventTypes.actor.g.h"
#elif !defined(FLOW_EVENTTYPES_ACTOR_H)
#define FLOW_EVENTTYPES_ACTOR_H

#include "flow/flow.h"
#include "flow/TDMetric.actor.h"
#include "flow/actorcompiler.h" // This must be the last #include.

template<> struct Descriptor<struct TraceEventNameID> {
	static StringRef typeName() { return "TraceEventNameID"_sr; }
	typedef TraceEventNameID type;
	struct nameDescriptor {
		static StringRef name() { return "name"_sr; }
		static StringRef typeName() { return "Standalone<StringRef>"_sr; }
		static StringRef comment() { return ""_sr; }
		typedef Standalone<StringRef> type;
		static inline type get(TraceEventNameID& from);
	};
	struct idDescriptor {
		static StringRef name() { return "id"_sr; }
		static StringRef typeName() { return "Standalone<StringRef>"_sr; }
		static StringRef comment() { return ""_sr; }
		typedef Standalone<StringRef> type;
		static inline type get(TraceEventNameID& from);
	};
	typedef std::tuple<nameDescriptor,idDescriptor> fields;
	typedef make_index_sequence_impl<0, index_sequence<>, std::tuple_size<fields>::value>::type field_indexes;
};
struct TraceEventNameID {
	Standalone<StringRef> name; //
	Standalone<StringRef> id; //
};
Standalone<StringRef> Descriptor<TraceEventNameID>::nameDescriptor::get(TraceEventNameID& from) { return from.name; }
Standalone<StringRef> Descriptor<TraceEventNameID>::idDescriptor::get(TraceEventNameID& from) { return from.id; }
#line 38 "/Users/gyming/Documents/USC/CATPS/Task/foundationdb/flow/include/flow/EventTypes.actor.h"


#include "flow/unactorcompiler.h"

#endif
