
// #include <foundationdb/fdb_c.h>

#include "hashmap.h"

// #include "flow/actorcompiler.h" // has to be last include

#include <vector>
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <unordered_map>
#include <thread>

// using namespace std;
using std::vector, std::pair, std::string;

HashmapServerInterface hsi;

ACTOR void handleRequest(HashmapRequest req) {
    state std::string res = "";
    state std::map<string,string>::iterator item;
    for(item = req.keyValueMap.begin();item!=req.keyValueMap.end();item++) {
        state std::pair<string,string> i = *item;
        if(i.second == "__query") {
            Promise<string> result;
            hsi.get.send(std::make_pair(i.first, result));
            string result = wait(result.getFuture());
            res = result;
        } else if(i.second == "__delete") {
            Promise<bool> result;
            hsi.deleteKey.send(std::make_pair(i.first, result));
        } else {
            hsi.put.send(std::make_pair(i.first, i.second));
        }
    }
    req.reply.send(res);
    // return Void();
}
struct HashmapReciever final : NetworkMessageReceiver {
	HashmapReciever() {}
	void receive(ArenaObjectReader& reader) override {
		HashmapRequest req;
        reader.deserialize(req);
        handleRequest(req);
	}
	PeerCompatibilityPolicy peerCompatibilityPolicy() const override {
		return PeerCompatibilityPolicy{ RequirePeer::AtLeast, ProtocolVersion::withStableInterfaces() };
	}
	bool isPublic() const override { return true; }
};


ACTOR void serveHashmapServerInterface(HashmapServerInterface hsi) {
    state std::unordered_map<string,string> hashmap;
    loop {
        choose {
            when(std::pair<string, string> x = waitNext(hsi.put.getFuture())) {
                hashmap[x.first] = x.second;
            }
            when(std::pair<string, Promise<string>> x = waitNext(hsi.get.getFuture())) {
                auto result = hashmap.find(x.first);
                string sending;
                if(result != hashmap.end()) {
                    sending = result->second;
                }
                x.second.send(sending);
            }
            when(std::pair<string, Promise<bool>> x = waitNext(hsi.deleteKey.getFuture())) {
                auto result = hashmap.find(x.first);
                if(result == hashmap.end()) {
                    x.second.send(false);
                }
                if(result != hashmap.end()) {
                    hashmap.erase(result->first);
                    x.second.send(true);
                }
            }
        }
    }
}

void runServer() {
    try {
        auto tls = TLSConfig(TLSEndpointType::SERVER);
        g_network = newNet2(tls);
        // g_network->run();
        FlowTransport::createInstance(0, 1, WLTOKEN_RESERVED_COUNT);
        auto serverAddress = NetworkAddress::parse("172.20.10.12:8889");
        auto& transport = FlowTransport::transport();
        
        auto endpoint = Endpoint();
        ;
        auto receiver = HashmapReciever();
        // std::cerr<<"111\n";
        // std::cerr<<transport.localA<<'\n';
        // std::cerr<<FlowTransport::getGlobalLocalAddress().ip.toString();
        auto listenFuture = transport.bind(serverAddress, serverAddress);
        transport.addEndpoint(endpoint, &receiver, TaskPriority::ReadSocket);
        std::cerr<<endpoint.token.first()<<"\n"<<endpoint.token.second()<<'\n';
        g_network->run();
    } catch(Error &e) {
        std::cerr<<e.name()<<"\n"<<e.what()<<"\n";
        // TraceEvent(SevError, "runServerError").error(e);
		throw;
    }
}

int main() {
    
    
    serveHashmapServerInterface(hsi);

    runServer();
    // 

}