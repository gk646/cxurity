#include <cxurity/Entity.h>
#include <cxurity/cxuconfig.h>

#include "device/EntityInformation.h"
#include "ml/AnomalyDetector.h"
#include "data/DataBase.h"

Entity::Entity()
    : eInfo(new EntityInformation()),
      aDetector(new AnomalyDetector()),
      dBase(new DataBase()),
      eBus(new EventBus()) {
  eBus->registerListener(dBase);
  eBus->registerListener(aDetector);
  eBus->registerListener(eInfo);
}
Entity::~Entity() {
  delete eBus;
  delete eInfo;
  delete dBase;
  delete aDetector;
}
void Entity::update() {
  uint16_t currTime = (1000 / CXU_APP_TPS) * upCounter++;
  if (currTime % eInfo->rIntervalMil == 0) {
    eBus->pushEvent({CXU_EventType::REQUEST_DB_REFRESH, *this});
  }
  eBus->processEvents();
}