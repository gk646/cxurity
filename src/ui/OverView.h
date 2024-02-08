#ifndef CXURITY_SRC_UI_OVERVIEW_H_
#define CXURITY_SRC_UI_OVERVIEW_H_

#include "UIComponent.h"

struct OverView : public UIComponent {
  void draw(Entity&, Vec2) final{};
};

#endif  //CXURITY_SRC_UI_OVERVIEW_H_
