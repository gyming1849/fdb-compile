/*
 * ProtocolVersion.h
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

 #ifndef FLOW_PROTOCOL_VERSION_H
 #define FLOW_PROTOCOL_VERSION_H

#pragma once
#include "flow/Trace.h"
#include <cstdint>

// This version impacts both communications and the deserialization of certain database and IKeyValueStore keys.
constexpr uint64_t defaultProtocolVersionValue = 0x0FDB00B074000000LL;

// The first protocol version that cannot be downgraded from. Ordinarily, this will be two release versions larger
// than the current version, meaning that we only support downgrades between consecutive release versions.
constexpr uint64_t minInvalidProtocolVersionValue = 0x0FDB00B076000000LL;

// The lowest protocol version that can be downgraded to.
constexpr uint64_t minCompatibleProtocolVersionValue = 0x0FDB00B073000000LL;

// The protocol version that will most likely follow the current one
// Used only for testing upgrades to the future version
constexpr uint64_t futureProtocolVersionValue = 0x0FDB00B075000000LL;

// ProtocolVersion wraps a uint64_t to make it type safe. It will know about the current versions.
// The default constructor will initialize the version to 0 (which is an invalid
// version). ProtocolVersion objects should never be compared to version numbers
// directly. Instead one should always use the type-safe version types from which
// this class inherits all.
class ProtocolVersion {
	uint64_t _version;

public: // constants
	static constexpr uint64_t versionFlagMask = 0x0FFFFFFFFFFFFFFFLL;
	static constexpr uint64_t objectSerializerFlag = 0x1000000000000000LL;
	static constexpr uint64_t compatibleProtocolVersionMask = 0xFFFFFFFFFFFF0000LL;
	static constexpr uint64_t minValidProtocolVersion = 0x0FDB00A200060001LL;
	static constexpr uint64_t invalidProtocolVersion = 0x0FDB00A100000000LL;

public:
	constexpr explicit ProtocolVersion(uint64_t version) : _version(version) {}
	constexpr ProtocolVersion() : _version(0) {}

	constexpr bool isCompatible(ProtocolVersion other) const {
		return (other.version() & compatibleProtocolVersionMask) == (version() & compatibleProtocolVersionMask);
	}

	// Returns a normalized protocol version that will be the same for all compatible versions
	constexpr ProtocolVersion normalizedVersion() const {
		return ProtocolVersion(_version & compatibleProtocolVersionMask);
	}
	constexpr bool isValid() const { return version() >= minValidProtocolVersion; }

	constexpr bool isInvalid() const { return version() == invalidProtocolVersion; }

	constexpr uint64_t version() const { return _version & versionFlagMask; }
	constexpr uint64_t versionWithFlags() const { return _version; }

	constexpr bool hasObjectSerializerFlag() const { return (_version & objectSerializerFlag) > 0; }
	constexpr void addObjectSerializerFlag() { _version = _version | objectSerializerFlag; }
	constexpr void removeObjectSerializerFlag() {
		_version = hasObjectSerializerFlag() ? _version ^ objectSerializerFlag : _version;
	}
	constexpr void removeAllFlags() { _version = version(); }

	// comparison operators
	// Comparison operators ignore the flags - this is because the version flags are stored in the
	// most significant byte which can make comparison confusing. Also, generally, when one wants to
	// compare versions, we are usually not interested in the flags.
	constexpr bool operator==(const ProtocolVersion other) const { return version() == other.version(); }
	constexpr bool operator!=(const ProtocolVersion other) const { return version() != other.version(); }
	constexpr bool operator<=(const ProtocolVersion other) const { return version() <= other.version(); }
	constexpr bool operator>=(const ProtocolVersion other) const { return version() >= other.version(); }
	constexpr bool operator<(const ProtocolVersion other) const { return version() < other.version(); }
	constexpr bool operator>(const ProtocolVersion other) const { return version() > other.version(); }

public: // introduced features
	// The 5th digit from right is dev version, for example, 2 in 0x0FDB00B061020000LL;
	// It was used to identify a protocol change (e.g., interface change) between major/minor versions (say 5.1 and 5.2)
	// We stopped using the dev version consistently in the past.
	// To ensure binaries work across patch releases (e.g., 6.2.0 to 6.2.22), we require that the protocol version be
	// the same for each of them.



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A200090000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A200090000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A200090000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct Watches {
		static constexpr uint64_t protocolVersion = 0x0FDB00A200090000LL;
	};
	constexpr bool hasWatches() const { return this->version() >= Watches::protocolVersion; }
	static constexpr ProtocolVersion withWatches() { return ProtocolVersion(Watches::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A2000D0000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A2000D0000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A2000D0000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct MovableCoordinatedState {
		static constexpr uint64_t protocolVersion = 0x0FDB00A2000D0000LL;
	};
	constexpr bool hasMovableCoordinatedState() const { return this->version() >= MovableCoordinatedState::protocolVersion; }
	static constexpr ProtocolVersion withMovableCoordinatedState() { return ProtocolVersion(MovableCoordinatedState::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A340000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A340000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A340000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ProcessID {
		static constexpr uint64_t protocolVersion = 0x0FDB00A340000000LL;
	};
	constexpr bool hasProcessID() const { return this->version() >= ProcessID::protocolVersion; }
	static constexpr ProtocolVersion withProcessID() { return ProtocolVersion(ProcessID::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A400040000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A400040000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A400040000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct OpenDatabase {
		static constexpr uint64_t protocolVersion = 0x0FDB00A400040000LL;
	};
	constexpr bool hasOpenDatabase() const { return this->version() >= OpenDatabase::protocolVersion; }
	static constexpr ProtocolVersion withOpenDatabase() { return ProtocolVersion(OpenDatabase::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A446020000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A446020000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A446020000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct Locality {
		static constexpr uint64_t protocolVersion = 0x0FDB00A446020000LL;
	};
	constexpr bool hasLocality() const { return this->version() >= Locality::protocolVersion; }
	static constexpr ProtocolVersion withLocality() { return ProtocolVersion(Locality::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A460010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A460010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A460010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct MultiGenerationTLog {
		static constexpr uint64_t protocolVersion = 0x0FDB00A460010000LL;
	};
	constexpr bool hasMultiGenerationTLog() const { return this->version() >= MultiGenerationTLog::protocolVersion; }
	static constexpr ProtocolVersion withMultiGenerationTLog() { return ProtocolVersion(MultiGenerationTLog::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A460010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A460010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A460010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct SharedMutations {
		static constexpr uint64_t protocolVersion = 0x0FDB00A460010000LL;
	};
	constexpr bool hasSharedMutations() const { return this->version() >= SharedMutations::protocolVersion; }
	static constexpr ProtocolVersion withSharedMutations() { return ProtocolVersion(SharedMutations::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A551000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A551000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A551000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct InexpensiveMultiVersionClient {
		static constexpr uint64_t protocolVersion = 0x0FDB00A551000000LL;
	};
	constexpr bool hasInexpensiveMultiVersionClient() const { return this->version() >= InexpensiveMultiVersionClient::protocolVersion; }
	static constexpr ProtocolVersion withInexpensiveMultiVersionClient() { return ProtocolVersion(InexpensiveMultiVersionClient::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00A560010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00A560010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00A560010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TagLocality {
		static constexpr uint64_t protocolVersion = 0x0FDB00A560010000LL;
	};
	constexpr bool hasTagLocality() const { return this->version() >= TagLocality::protocolVersion; }
	static constexpr ProtocolVersion withTagLocality() { return ProtocolVersion(TagLocality::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B060000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B060000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B060000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct Fearless {
		static constexpr uint64_t protocolVersion = 0x0FDB00B060000000LL;
	};
	constexpr bool hasFearless() const { return this->version() >= Fearless::protocolVersion; }
	static constexpr ProtocolVersion withFearless() { return ProtocolVersion(Fearless::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B061020000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B061020000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B061020000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct EndpointAddrList {
		static constexpr uint64_t protocolVersion = 0x0FDB00B061020000LL;
	};
	constexpr bool hasEndpointAddrList() const { return this->version() >= EndpointAddrList::protocolVersion; }
	static constexpr ProtocolVersion withEndpointAddrList() { return ProtocolVersion(EndpointAddrList::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B061030000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B061030000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B061030000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct IPv6 {
		static constexpr uint64_t protocolVersion = 0x0FDB00B061030000LL;
	};
	constexpr bool hasIPv6() const { return this->version() >= IPv6::protocolVersion; }
	static constexpr ProtocolVersion withIPv6() { return ProtocolVersion(IPv6::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B061030000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B061030000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B061030000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TLogVersion {
		static constexpr uint64_t protocolVersion = 0x0FDB00B061030000LL;
	};
	constexpr bool hasTLogVersion() const { return this->version() >= TLogVersion::protocolVersion; }
	static constexpr ProtocolVersion withTLogVersion() { return ProtocolVersion(TLogVersion::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B061070000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B061070000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B061070000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct PseudoLocalities {
		static constexpr uint64_t protocolVersion = 0x0FDB00B061070000LL;
	};
	constexpr bool hasPseudoLocalities() const { return this->version() >= PseudoLocalities::protocolVersion; }
	static constexpr ProtocolVersion withPseudoLocalities() { return ProtocolVersion(PseudoLocalities::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B061070000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B061070000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B061070000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ShardedTxsTags {
		static constexpr uint64_t protocolVersion = 0x0FDB00B061070000LL;
	};
	constexpr bool hasShardedTxsTags() const { return this->version() >= ShardedTxsTags::protocolVersion; }
	static constexpr ProtocolVersion withShardedTxsTags() { return ProtocolVersion(ShardedTxsTags::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TLogQueueEntryRef {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasTLogQueueEntryRef() const { return this->version() >= TLogQueueEntryRef::protocolVersion; }
	static constexpr ProtocolVersion withTLogQueueEntryRef() { return ProtocolVersion(TLogQueueEntryRef::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct GenerationRegVal {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasGenerationRegVal() const { return this->version() >= GenerationRegVal::protocolVersion; }
	static constexpr ProtocolVersion withGenerationRegVal() { return ProtocolVersion(GenerationRegVal::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct MovableCoordinatedStateV2 {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasMovableCoordinatedStateV2() const { return this->version() >= MovableCoordinatedStateV2::protocolVersion; }
	static constexpr ProtocolVersion withMovableCoordinatedStateV2() { return ProtocolVersion(MovableCoordinatedStateV2::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct KeyServerValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasKeyServerValue() const { return this->version() >= KeyServerValue::protocolVersion; }
	static constexpr ProtocolVersion withKeyServerValue() { return ProtocolVersion(KeyServerValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct LogsValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasLogsValue() const { return this->version() >= LogsValue::protocolVersion; }
	static constexpr ProtocolVersion withLogsValue() { return ProtocolVersion(LogsValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ServerTagValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasServerTagValue() const { return this->version() >= ServerTagValue::protocolVersion; }
	static constexpr ProtocolVersion withServerTagValue() { return ProtocolVersion(ServerTagValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TagLocalityListValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasTagLocalityListValue() const { return this->version() >= TagLocalityListValue::protocolVersion; }
	static constexpr ProtocolVersion withTagLocalityListValue() { return ProtocolVersion(TagLocalityListValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct DatacenterReplicasValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasDatacenterReplicasValue() const { return this->version() >= DatacenterReplicasValue::protocolVersion; }
	static constexpr ProtocolVersion withDatacenterReplicasValue() { return ProtocolVersion(DatacenterReplicasValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ProcessClassValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasProcessClassValue() const { return this->version() >= ProcessClassValue::protocolVersion; }
	static constexpr ProtocolVersion withProcessClassValue() { return ProtocolVersion(ProcessClassValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct WorkerListValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasWorkerListValue() const { return this->version() >= WorkerListValue::protocolVersion; }
	static constexpr ProtocolVersion withWorkerListValue() { return ProtocolVersion(WorkerListValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BackupStartValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasBackupStartValue() const { return this->version() >= BackupStartValue::protocolVersion; }
	static constexpr ProtocolVersion withBackupStartValue() { return ProtocolVersion(BackupStartValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct LogRangeEncodeValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasLogRangeEncodeValue() const { return this->version() >= LogRangeEncodeValue::protocolVersion; }
	static constexpr ProtocolVersion withLogRangeEncodeValue() { return ProtocolVersion(LogRangeEncodeValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct HealthyZoneValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasHealthyZoneValue() const { return this->version() >= HealthyZoneValue::protocolVersion; }
	static constexpr ProtocolVersion withHealthyZoneValue() { return ProtocolVersion(HealthyZoneValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct DRBackupRanges {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasDRBackupRanges() const { return this->version() >= DRBackupRanges::protocolVersion; }
	static constexpr ProtocolVersion withDRBackupRanges() { return ProtocolVersion(DRBackupRanges::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RegionConfiguration {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasRegionConfiguration() const { return this->version() >= RegionConfiguration::protocolVersion; }
	static constexpr ProtocolVersion withRegionConfiguration() { return ProtocolVersion(RegionConfiguration::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ReplicationPolicy {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasReplicationPolicy() const { return this->version() >= ReplicationPolicy::protocolVersion; }
	static constexpr ProtocolVersion withReplicationPolicy() { return ProtocolVersion(ReplicationPolicy::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BackupMutations {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasBackupMutations() const { return this->version() >= BackupMutations::protocolVersion; }
	static constexpr ProtocolVersion withBackupMutations() { return ProtocolVersion(BackupMutations::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ClusterControllerPriorityInfo {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasClusterControllerPriorityInfo() const { return this->version() >= ClusterControllerPriorityInfo::protocolVersion; }
	static constexpr ProtocolVersion withClusterControllerPriorityInfo() { return ProtocolVersion(ClusterControllerPriorityInfo::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ProcessIDFile {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasProcessIDFile() const { return this->version() >= ProcessIDFile::protocolVersion; }
	static constexpr ProtocolVersion withProcessIDFile() { return ProtocolVersion(ProcessIDFile::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B062010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B062010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B062010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct CloseUnusedConnection {
		static constexpr uint64_t protocolVersion = 0x0FDB00B062010001LL;
	};
	constexpr bool hasCloseUnusedConnection() const { return this->version() >= CloseUnusedConnection::protocolVersion; }
	static constexpr ProtocolVersion withCloseUnusedConnection() { return ProtocolVersion(CloseUnusedConnection::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct DbCoreState {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasDbCoreState() const { return this->version() >= DbCoreState::protocolVersion; }
	static constexpr ProtocolVersion withDbCoreState() { return ProtocolVersion(DbCoreState::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TagThrottleValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasTagThrottleValue() const { return this->version() >= TagThrottleValue::protocolVersion; }
	static constexpr ProtocolVersion withTagThrottleValue() { return ProtocolVersion(TagThrottleValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct StorageCacheValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasStorageCacheValue() const { return this->version() >= StorageCacheValue::protocolVersion; }
	static constexpr ProtocolVersion withStorageCacheValue() { return ProtocolVersion(StorageCacheValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RestoreStatusValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasRestoreStatusValue() const { return this->version() >= RestoreStatusValue::protocolVersion; }
	static constexpr ProtocolVersion withRestoreStatusValue() { return ProtocolVersion(RestoreStatusValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RestoreRequestValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasRestoreRequestValue() const { return this->version() >= RestoreRequestValue::protocolVersion; }
	static constexpr ProtocolVersion withRestoreRequestValue() { return ProtocolVersion(RestoreRequestValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RestoreRequestDoneVersionValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasRestoreRequestDoneVersionValue() const { return this->version() >= RestoreRequestDoneVersionValue::protocolVersion; }
	static constexpr ProtocolVersion withRestoreRequestDoneVersionValue() { return ProtocolVersion(RestoreRequestDoneVersionValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RestoreRequestTriggerValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasRestoreRequestTriggerValue() const { return this->version() >= RestoreRequestTriggerValue::protocolVersion; }
	static constexpr ProtocolVersion withRestoreRequestTriggerValue() { return ProtocolVersion(RestoreRequestTriggerValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct RestoreWorkerInterfaceValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasRestoreWorkerInterfaceValue() const { return this->version() >= RestoreWorkerInterfaceValue::protocolVersion; }
	static constexpr ProtocolVersion withRestoreWorkerInterfaceValue() { return ProtocolVersion(RestoreWorkerInterfaceValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BackupProgressValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasBackupProgressValue() const { return this->version() >= BackupProgressValue::protocolVersion; }
	static constexpr ProtocolVersion withBackupProgressValue() { return ProtocolVersion(BackupProgressValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct KeyServerValueV2 {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasKeyServerValueV2() const { return this->version() >= KeyServerValueV2::protocolVersion; }
	static constexpr ProtocolVersion withKeyServerValueV2() { return ProtocolVersion(KeyServerValueV2::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BackupWorker {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasBackupWorker() const { return this->version() >= BackupWorker::protocolVersion; }
	static constexpr ProtocolVersion withBackupWorker() { return ProtocolVersion(BackupWorker::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ReportConflictingKeys {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasReportConflictingKeys() const { return this->version() >= ReportConflictingKeys::protocolVersion; }
	static constexpr ProtocolVersion withReportConflictingKeys() { return ProtocolVersion(ReportConflictingKeys::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct SmallEndpoints {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasSmallEndpoints() const { return this->version() >= SmallEndpoints::protocolVersion; }
	static constexpr ProtocolVersion withSmallEndpoints() { return ProtocolVersion(SmallEndpoints::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct CacheRole {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063010000LL;
	};
	constexpr bool hasCacheRole() const { return this->version() >= CacheRole::protocolVersion; }
	static constexpr ProtocolVersion withCacheRole() { return ProtocolVersion(CacheRole::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B063000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B063000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B063000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct UnifiedTlogSpilling {
		static constexpr uint64_t protocolVersion = 0x0FDB00B063000000LL;
	};
	constexpr bool hasUnifiedTlogSpilling() const { return this->version() >= UnifiedTlogSpilling::protocolVersion; }
	static constexpr ProtocolVersion withUnifiedTlogSpilling() { return ProtocolVersion(UnifiedTlogSpilling::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B070010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B070010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B070010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct StableInterfaces {
		static constexpr uint64_t protocolVersion = 0x0FDB00B070010000LL;
	};
	constexpr bool hasStableInterfaces() const { return this->version() >= StableInterfaces::protocolVersion; }
	static constexpr ProtocolVersion withStableInterfaces() { return ProtocolVersion(StableInterfaces::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B070010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B070010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B070010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ServerListValue {
		static constexpr uint64_t protocolVersion = 0x0FDB00B070010001LL;
	};
	constexpr bool hasServerListValue() const { return this->version() >= ServerListValue::protocolVersion; }
	static constexpr ProtocolVersion withServerListValue() { return ProtocolVersion(ServerListValue::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B070010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B070010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B070010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TagThrottleValueReason {
		static constexpr uint64_t protocolVersion = 0x0FDB00B070010001LL;
	};
	constexpr bool hasTagThrottleValueReason() const { return this->version() >= TagThrottleValueReason::protocolVersion; }
	static constexpr ProtocolVersion withTagThrottleValueReason() { return ProtocolVersion(TagThrottleValueReason::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B070010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B070010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B070010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct SpanContext {
		static constexpr uint64_t protocolVersion = 0x0FDB00B070010001LL;
	};
	constexpr bool hasSpanContext() const { return this->version() >= SpanContext::protocolVersion; }
	static constexpr ProtocolVersion withSpanContext() { return ProtocolVersion(SpanContext::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B070010001LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B070010001LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B070010001LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct TSS {
		static constexpr uint64_t protocolVersion = 0x0FDB00B070010001LL;
	};
	constexpr bool hasTSS() const { return this->version() >= TSS::protocolVersion; }
	static constexpr ProtocolVersion withTSS() { return ProtocolVersion(TSS::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ChangeFeed {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasChangeFeed() const { return this->version() >= ChangeFeed::protocolVersion; }
	static constexpr ProtocolVersion withChangeFeed() { return ProtocolVersion(ChangeFeed::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BlobGranule {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasBlobGranule() const { return this->version() >= BlobGranule::protocolVersion; }
	static constexpr ProtocolVersion withBlobGranule() { return ProtocolVersion(BlobGranule::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct NetworkAddressHostnameFlag {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasNetworkAddressHostnameFlag() const { return this->version() >= NetworkAddressHostnameFlag::protocolVersion; }
	static constexpr ProtocolVersion withNetworkAddressHostnameFlag() { return ProtocolVersion(NetworkAddressHostnameFlag::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct StorageMetadata {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasStorageMetadata() const { return this->version() >= StorageMetadata::protocolVersion; }
	static constexpr ProtocolVersion withStorageMetadata() { return ProtocolVersion(StorageMetadata::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct PerpetualWiggleMetadata {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasPerpetualWiggleMetadata() const { return this->version() >= PerpetualWiggleMetadata::protocolVersion; }
	static constexpr ProtocolVersion withPerpetualWiggleMetadata() { return ProtocolVersion(PerpetualWiggleMetadata::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct StorageInterfaceReadiness {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasStorageInterfaceReadiness() const { return this->version() >= StorageInterfaceReadiness::protocolVersion; }
	static constexpr ProtocolVersion withStorageInterfaceReadiness() { return ProtocolVersion(StorageInterfaceReadiness::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct Tenants {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasTenants() const { return this->version() >= Tenants::protocolVersion; }
	static constexpr ProtocolVersion withTenants() { return ProtocolVersion(Tenants::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B071010000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B071010000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B071010000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ResolverPrivateMutations {
		static constexpr uint64_t protocolVersion = 0x0FDB00B071010000LL;
	};
	constexpr bool hasResolverPrivateMutations() const { return this->version() >= ResolverPrivateMutations::protocolVersion; }
	static constexpr ProtocolVersion withResolverPrivateMutations() { return ProtocolVersion(ResolverPrivateMutations::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct OTELSpanContext {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasOTELSpanContext() const { return this->version() >= OTELSpanContext::protocolVersion; }
	static constexpr ProtocolVersion withOTELSpanContext() { return ProtocolVersion(OTELSpanContext::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct SWVersionTracking {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasSWVersionTracking() const { return this->version() >= SWVersionTracking::protocolVersion; }
	static constexpr ProtocolVersion withSWVersionTracking() { return ProtocolVersion(SWVersionTracking::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct EncryptionAtRest {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasEncryptionAtRest() const { return this->version() >= EncryptionAtRest::protocolVersion; }
	static constexpr ProtocolVersion withEncryptionAtRest() { return ProtocolVersion(EncryptionAtRest::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ShardEncodeLocationMetaData {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasShardEncodeLocationMetaData() const { return this->version() >= ShardEncodeLocationMetaData::protocolVersion; }
	static constexpr ProtocolVersion withShardEncodeLocationMetaData() { return ProtocolVersion(ShardEncodeLocationMetaData::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BlobGranuleFile {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasBlobGranuleFile() const { return this->version() >= BlobGranuleFile::protocolVersion; }
	static constexpr ProtocolVersion withBlobGranuleFile() { return ProtocolVersion(BlobGranuleFile::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct EncryptedSnapshotBackupFile {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasEncryptedSnapshotBackupFile() const { return this->version() >= EncryptedSnapshotBackupFile::protocolVersion; }
	static constexpr ProtocolVersion withEncryptedSnapshotBackupFile() { return ProtocolVersion(EncryptedSnapshotBackupFile::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct ClusterIdSpecialKey {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasClusterIdSpecialKey() const { return this->version() >= ClusterIdSpecialKey::protocolVersion; }
	static constexpr ProtocolVersion withClusterIdSpecialKey() { return ProtocolVersion(ClusterIdSpecialKey::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BlobGranuleFileLogicalSize {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasBlobGranuleFileLogicalSize() const { return this->version() >= BlobGranuleFileLogicalSize::protocolVersion; }
	static constexpr ProtocolVersion withBlobGranuleFileLogicalSize() { return ProtocolVersion(BlobGranuleFileLogicalSize::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B072000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B072000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B072000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct BlobRangeChangeLog {
		static constexpr uint64_t protocolVersion = 0x0FDB00B072000000LL;
	};
	constexpr bool hasBlobRangeChangeLog() const { return this->version() >= BlobRangeChangeLog::protocolVersion; }
	static constexpr ProtocolVersion withBlobRangeChangeLog() { return ProtocolVersion(BlobRangeChangeLog::protocolVersion); }



	// The first check second expression version doesn't need to change because it's just for earlier protocol versions.
	static_assert((0x0FDB00B073000000LL & 0x0000000000F0FFFFLL) == 0 || 0x0FDB00B073000000LL < 0x0FDB00B071000000LL, "Unexpected feature protocol version");
	static_assert(0x0FDB00B073000000LL <= defaultProtocolVersionValue, "Feature protocol version too large");
	struct GcTxnGenerations {
		static constexpr uint64_t protocolVersion = 0x0FDB00B073000000LL;
	};
	constexpr bool hasGcTxnGenerations() const { return this->version() >= GcTxnGenerations::protocolVersion; }
	static constexpr ProtocolVersion withGcTxnGenerations() { return ProtocolVersion(GcTxnGenerations::protocolVersion); }

};

template <>
struct Traceable<ProtocolVersion> : std::true_type {
	static std::string toString(const ProtocolVersion& protocolVersion) {
		return format("0x%016lX", protocolVersion.version());
	}
};

constexpr ProtocolVersion defaultProtocolVersion(defaultProtocolVersionValue);
constexpr ProtocolVersion minInvalidProtocolVersion(minInvalidProtocolVersionValue);
constexpr ProtocolVersion minCompatibleProtocolVersion(minCompatibleProtocolVersionValue);

// The protocol version of the process, normally it is equivalent defaultProtocolVersion
// The currentProtocolVersion can be overridden dynamically for testing upgrades
// to a future FDB version
ProtocolVersion currentProtocolVersion();

// Assume the next future protocol version as the current one. Used for testing purposes only
void useFutureProtocolVersion();

// This assert is intended to help prevent incrementing the leftmost digits accidentally. It will probably need to
// change when we reach version 10.
static_assert(defaultProtocolVersion.version() < 0x0FDB00B100000000LL, "Unexpected protocol version");

// The last two bytes of the protocol version are currently masked out in compatibility checks. We do not use them,
// so prevent them from being inadvertently changed.
//
// We also do not modify the protocol version for patch releases, so prevent modifying the patch version digit.
static_assert((defaultProtocolVersion.version() & 0x0000000000F0FFFFLL) == 0, "Unexpected protocol version");

// Downgrades must support at least one minor version.
static_assert(minInvalidProtocolVersion.version() >=
                  (defaultProtocolVersion.version() & 0xFFFFFFFFFF000000LL) + 0x0000000002000000,
              "Downgrades must support one minor version");

// The min invalid protocol version should be the smallest possible protocol version associated with a minor release
// version.
static_assert((minInvalidProtocolVersion.version() & 0xFFFFFFLL) == 0, "Unexpected min invalid protocol version");

struct SWVersion {
	constexpr static FileIdentifier file_identifier = 13943914;

private:
	uint64_t _newestProtocolVersion;
	uint64_t _lastRunProtocolVersion;
	uint64_t _lowestCompatibleProtocolVersion;

public:
	SWVersion() {
		_newestProtocolVersion = 0;
		_lastRunProtocolVersion = 0;
		_lowestCompatibleProtocolVersion = 0;
	}

	SWVersion(ProtocolVersion latestVersion, ProtocolVersion lastVersion, ProtocolVersion minCompatibleVersion)
	  : _newestProtocolVersion(latestVersion.version()), _lastRunProtocolVersion(lastVersion.version()),
	    _lowestCompatibleProtocolVersion(minCompatibleVersion.version()) {}

	bool isValid() const {
		return (_newestProtocolVersion != 0 && _lastRunProtocolVersion != 0 && _lowestCompatibleProtocolVersion != 0);
	}

	uint64_t newestProtocolVersion() const { return _newestProtocolVersion; }
	uint64_t lastRunProtocolVersion() const { return _lastRunProtocolVersion; }
	uint64_t lowestCompatibleProtocolVersion() const { return _lowestCompatibleProtocolVersion; }

	template <class Ar>
	void serialize(Ar& ar) {
		serializer(ar, _newestProtocolVersion, _lastRunProtocolVersion, _lowestCompatibleProtocolVersion);
	}
};

template <>
struct Traceable<SWVersion> : std::true_type {
	static std::string toString(const SWVersion& swVersion) {
		return format("Newest: 0x%016lX, Last: 0x%016lX, MinCompatible: 0x%016lX",
		              swVersion.newestProtocolVersion(),
		              swVersion.lastRunProtocolVersion(),
		              swVersion.lowestCompatibleProtocolVersion());
	}
};

#endif  // FLOW_PROTOCOL_VERSION_H