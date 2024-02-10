#ifndef CXURITY_SRC_ENTITY_UI_UIPANEL_H_
#define CXURITY_SRC_ENTITY_UI_UIPANEL_H_

#include <cxurity/common.h>

#include "UIComponent.h"

struct UIPanel : public UIComponent {
  Vec2 rOffset;  // Offset from the top level coordinates
  Vec2 rSize;    //Relative window size of the component in percentile
  UIPanel(const Vec2& pos, const Vec2& rSize) : rOffset(pos), rSize(rSize){};

 protected:
  void drawPanel(const Vec2& p);
  Vec2 getDrawPos(const Vec2& p);
};

#endif  //CXURITY_SRC_ENTITY_UI_UIPANEL_H_
