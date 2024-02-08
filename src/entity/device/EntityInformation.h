#ifndef CXURITY_SRC_ENTITY_DEVICE_ENTITYINFORMATION_H_
#define CXURITY_SRC_ENTITY_DEVICE_ENTITYINFORMATION_H_

#include <cxurity/common.h>

#include "../common/Events.h"
#include "DeviceInformation.h"

struct EntityInformation : public EventListener {
  DeviceInformation devInfo{};                         //Device information
  uint16_t rIntervalMil = 5000;                        //Refresh interval in millis
  CXU_SecurityLevel sLevel = CXU_SecurityLevel::FULL;  //Security level for this entity
  CXU_EntityRole eRole = CXU_EntityRole::UNSET;        //Role of this entity

  EntityInformation();
  void onEvent(const Event& event) final;
};

#endif  //CXURITY_SRC_ENTITY_DEVICE_ENTITYINFORMATION_H_
