#ifndef CXURITY_SRC_ENTITY_UI_TABLIST_H_
#define CXURITY_SRC_ENTITY_UI_TABLIST_H_

#include <vector>

#include "UIComponent.h"
#include "Tab.h"


struct TabList : public UIComponent {
  std::vector<Tab> tabs;
  void draw(Entity& e, Vec2 pos) override = 0;
  void addTab(Tab &&);
 protected:
  void setSelected(Tab*);
};

#endif  //CXURITY_SRC_ENTITY_UI_TABLIST_H_
