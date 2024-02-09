#include <iostream>
#include "EntityInformation.h"

#include <cxurity/Entity.h>

EntityInformation::EntityInformation() {

}

void EntityInformation::onEvent(const Event& e) {

  if (e.type == CXU_EventType::REQUEST_ENTITY_INFO_UPDATE) {
    //eInfo.update();
    std::cout << "entity update finished" << std::endl;
    e.entity.eBus->pushEvent({CXU_EventType::ENTITY_INFO_UPDATE_FINISHED, e.entity});
  }
}