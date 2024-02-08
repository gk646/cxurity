#ifndef CXURITY_SRC_ENTITY_UI_USERDISPLAY_H_
#define CXURITY_SRC_ENTITY_UI_USERDISPLAY_H_


#include "UIComponent.h"

struct UserDisplay : public UIComponent {
  void draw(Entity& e, Vec2 pos) final;
};

#endif  //CXURITY_SRC_ENTITY_UI_USERDISPLAY_H_
