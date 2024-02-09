#ifndef CXURITY_SRC_ENTITY_DATA_NETWORKFETCHER_H_
#define CXURITY_SRC_ENTITY_DATA_NETWORKFETCHER_H_

#include <cstdint>
#include <unordered_map>

struct ProcessList;

struct ProcessNetworkInfo {
  uint64_t bytesSent;
  uint64_t bytesReceived;
};

struct NetworkFetcher {
  std::unordered_map<uint32_t, ProcessNetworkInfo> netMap;
  //TODO fetch packets and keep statistics for each process
  void update();
  void addNetworkInformation(ProcessList&);
};

#endif  //CXURITY_SRC_ENTITY_DATA_NETWORKFETCHER_H_
