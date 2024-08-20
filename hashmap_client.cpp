
#include "hashmap.h"
// #include "JavaFlowClient.h"

// #include <foundationdb/fdb_c.h>

//#include "hashmap.h"

// #include "flow/actorcompiler.h" // has to be last include

#include <vector>
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <unordered_map>

// using namespace std;
using std::vector, std::pair, std::string;


ACTOR template <class T>
Future<T> stopNetworkAfter(Future<T> what) {
  T t = wait(what);
  g_network->stop();
  return t;
}
UID uid;
ACTOR Future<string> connect(HashmapRequest hashmapReq) {

  try {
    NetworkAddress clientAddress = NetworkAddress::parse("127.0.0.1:8889");
    auto tls = TLSConfig(TLSEndpointType::CLIENT);
    g_network = newNet2(tls);
    FlowTransport::createInstance(1, 1, WLTOKEN_RESERVED_COUNT);

    auto& transport = FlowTransport::transport();
    auto dest = Endpoint();
    auto& serverAddr = dest.addresses.address;
    serverAddr = clientAddress;
    serverAddr.flags &= ~NetworkAddress::FLAG_TLS;
    auto& token = dest.token;
    // token = UID(12508973348854390892ull, 15111981746830180377ull);
    token = uid;

    // state Reference<IListener> listener = INetworkConnections::net()->listen(serverAddress);
    // hashmapReq.keyValueMap["aaa"] = "__query";
    // std::cerr<<1;
    transport.sendUnreliable(SerializeSource(hashmapReq), dest, true);

    // std::cerr<<1;
    // string res = wait(hashmapReq.reply.getFuture());
    auto res = stopNetworkAfter(hashmapReq.reply.getFuture());
    g_network->run();
    return res.get();

    // std::cerr<<res.get()<<" ";

  }
  catch(Error &e) {
    TraceEvent(SevError, "ListenError").error(e);
    throw;
  }
  // return Future<Void>;
}

void put(string key, string value) {
  HashmapRequest hashmapReq = HashmapRequest{};
  hashmapReq.keyValueMap[key]=value;
  connect(hashmapReq);
}

void deleteKey(string key) {
  HashmapRequest hashmapReq = HashmapRequest{};
  hashmapReq.keyValueMap[key]="__delete";
  connect(hashmapReq);
}

Future<string> get(string key) {
  HashmapRequest hashmapReq = HashmapRequest{};
  hashmapReq.keyValueMap[key]="__query";
  return connect(hashmapReq).get();
}

void setConnection(uint64_t id1, uint64_t id2) {
  uid = UID(id1,id2);
}