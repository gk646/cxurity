#ifndef CXURITY_SRC_ENTITY_DATA_PROCESSPOOL_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESSPOOL_H_

#include <unordered_map>
#include <cxurity/common.h>
#include "ProcessList.h"

struct Process;
struct Entity;
struct ProcessPool {
  using ProcessID = uint32_t;
  std::unordered_map<ProcessID, Process*> idMap;
  ProcessList list;

  explicit ProcessPool();
  void update(Entity&);

 private:
  uint16_t upCounter = 0;

  void createMappings();
  void filterList(CXU_SecurityLevel);
  bool isRefresh(uint16_t);
};
#endif  //CXURITY_SRC_ENTITY_DATA_PROCESSPOOL_H_
