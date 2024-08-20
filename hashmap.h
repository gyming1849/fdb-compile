#include "flow/flow.h"
#include "flow/network.h"
#include "flow/IConnection.h"
#include "fdbrpc/FlowTransport.h"
#include "fdbrpc/fdbrpc.h"
#include "flow/TLSConfig.actor.g.h"

#include "flow/actorcompiler.h"

#include <string>
using std::string;

struct HashmapServerInterface
{
    /* data */
    PromiseStream<std::pair<string, string>> put;
    PromiseStream<std::pair<string, Promise<string>>> get;
    PromiseStream<std::pair<string, Promise<bool>>> deleteKey;
    // static std::unordered_map<string,string> hashmap;

    template <class Ar>
    void serialize(Ar &ar) {
        serializer(ar, put, get, deleteKey);
    }
};
struct HashmapRequest {
	constexpr static FileIdentifier file_identifier = 1559713;

	ReplyPromise<std::string> reply{ PeerCompatibilityPolicy{ RequirePeer::AtLeast,
		                                                      ProtocolVersion::withStableInterfaces() } };

	bool verify() const { return true; }

    std::map<string,string> keyValueMap;

	template <class Ar>
	void serialize(Ar& ar) {
		serializer(ar, reply, keyValueMap);
	}
};


