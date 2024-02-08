#ifndef CXURITY_SRC_ENTITY_UI_DASHBOARD_H_
#define CXURITY_SRC_ENTITY_UI_DASHBOARD_H_

#include "TabList.h"


struct Dashboard : public TabList {
  Dashboard();
  void draw(Entity& e, Vec2 pos) final;
};


#endif  //CXURITY_SRC_ENTITY_UI_DASHBOARD_H_
