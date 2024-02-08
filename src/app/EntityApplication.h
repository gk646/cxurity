#ifndef CXURITY_SRC_ENTITY_ML_ENTITYAPPLICATION_H_
#define CXURITY_SRC_ENTITY_ML_ENTITYAPPLICATION_H_

#include <cxurity/Entity.h>
#include "../ui/UIRoot.h"

struct EntityApplication {
  Entity entity;
  EntityUIRoot uiRoot;
  std::thread lThread;
  bool shouldStop = false;
  EntityApplication();
  ~EntityApplication();
  int run();

 private:
  void update();
  void initOS();
  void exitOS();
};

#endif  //CXURITY_SRC_ENTITY_ML_ENTITYAPPLICATION_H_
