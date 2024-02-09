#ifndef CXURITY_SRC_HEADERS_ENTITY_H_
#define CXURITY_SRC_HEADERS_ENTITY_H_

#include <memory>

struct EntityInformation;
struct AnomalyDetector;
struct DataBase;
struct EventBus;

struct Entity {
  EntityInformation* eInfo;    //entity Information
  AnomalyDetector* aDetector;  //Process Pool
  DataBase* dBase;             //Historic data
  EventBus* eBus;              //Global event bus

  Entity();
  ~Entity();
  void update();

 private:
  uint64_t upCounter = 0;
};
#endif  //CXURITY_SRC_HEADERS_ENTITY_H_
