#ifndef CXURITY_SRC_ENTITY_UI_NAVIGATIONPANE_H_
#define CXURITY_SRC_ENTITY_UI_NAVIGATIONPANE_H_

#include "TabList.h"

struct NavigationPane : public TabList {
  NavigationPane();
  void draw(Entity& e, Vec2 pos) final;

 private:
  char tBox[32] = "Search";
  bool isEditable = false;
};


#endif  //CXURITY_SRC_ENTITY_UI_NAVIGATIONPANE_H_
