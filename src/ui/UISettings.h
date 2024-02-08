#ifndef CXURITY_SRC_UI_UISETTINGS_H_
#define CXURITY_SRC_UI_UISETTINGS_H_

#include "UIComponent.h"

struct UISettings : public UIComponent {

  void draw(Entity&, Vec2) final{};
};

#endif  //CXURITY_SRC_UI_UISETTINGS_H_
