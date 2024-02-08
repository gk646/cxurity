#ifndef CXURITY_SRC_ENTITY_UI_SIDEPANEL_H_
#define CXURITY_SRC_ENTITY_UI_SIDEPANEL_H_

#include "UIComponent.h"
#include "UserDisplay.h"

struct SidePanel : public UIComponent {
  UserDisplay uDisplay;
  void draw(Entity& e, Vec2 pos) final;
};

#endif  //CXURITY_SRC_ENTITY_UI_SIDEPANEL_H_
