#ifndef CXURITY_SRC_HEADERS_ENTITY_H_
#define CXURITY_SRC_HEADERS_ENTITY_H_

#include "cxuconfig.h"
#include "DataCollection.h"
#include "../entity/DeviceInformation.h"

enum class CXU_EntityRole : uint8_t { ADMIN, USER, UNSET, SERVER };


struct EntityInformation {
  DeviceInformation devInfo{};                         //Device information
  uint16_t rIntervalMil = 5000;                        //Refresh interval in millis
  CXU_SecurityLevel sLevel = CXU_SecurityLevel::FULL;  //Security level for this entity
  CXU_EntityRole eRole = CXU_EntityRole::UNSET;        //Role of this entity
  EntityInformation();
};

struct Entity {
  EntityInformation eInfo;  //entity Information
  ProcessPool pPool;        //Process Pool
  History history;          //Historic data
  Entity();
  void update(Entity&);
};
#endif  //CXURITY_SRC_HEADERS_ENTITY_H_
