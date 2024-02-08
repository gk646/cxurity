#ifndef CXURITY_SRC_ENTITY_UI_UIPANEL_H_
#define CXURITY_SRC_ENTITY_UI_UIPANEL_H_

#include <cxurity/common.h>

#include "UIComponent.h"


struct UIPanel : public UIComponent {
  Vec2 pos;
  Vec2 rSize;  //Relative size of the component in percentile
  void draw(Entity&, Vec2) override = 0;

 protected:
  void drawPanel();
};

#endif  //CXURITY_SRC_ENTITY_UI_UIPANEL_H_
