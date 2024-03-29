#ifndef CXURITY_SRC_ENTITY_DATA_SNAPSHOT_H_
#define CXURITY_SRC_ENTITY_DATA_SNAPSHOT_H_

#include "../device/EntityInformation.h"
#include "ProcessList.h"

struct Snapshot {
  EntityInformation eInfo;  // The current EInformation
  ProcessList pList;        // The current processes
  int64_t timestamp = 0;    //Timestamp in unix millis
  Snapshot(const EntityInformation& eInfo, ProcessList&& pList)
      : eInfo(eInfo), pList(pList), timestamp(std::time(nullptr)) {}
};

#endif  //CXURITY_SRC_ENTITY_DATA_SNAPSHOT_H_
