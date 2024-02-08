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

  eBus->registerListener(CXU_EventType::REQUEST_DB_REFRESH, dBase);
  eBus->registerListener(CXU_EventType::DB_REFRESH_FINISHED, dBase);

  eBus->registerListener(CXU_EventType::REQUEST_ANOMALY_DETECTION, aDetector);
  eBus->registerListener(CXU_EventType::ANOMALY_DETECTION_FINISHED, aDetector);

  eBus->registerListener(CXU_EventType::REQUEST_ENTITY_INFO_UPDATE, eInfo);
  eBus->registerListener(CXU_EventType::ENTITY_INFO_UPDATE_FINISHED, eInfo);
}
Entity::~Entity() {
  delete eBus;
  delete eInfo;
  delete dBase;
  delete aDetector;
}
void Entity::update() {
  if ((1000.0F / CXU_APP_TPS) * upCounter++ >= eInfo->rIntervalMil) {
    upCounter = 0;
    eBus->pushEvent({CXU_EventType::REQUEST_DB_REFRESH, *this});
  }

  eBus->processEvents();
}