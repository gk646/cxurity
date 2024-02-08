#ifndef CXURITY_SRC_ENTITY_UI_STATUSBAR_H_
#define CXURITY_SRC_ENTITY_UI_STATUSBAR_H_

#include <string>
#include <vector>
#include "UIComponent.h"

struct StatusBar : public UIComponent {
  struct ScrollingText {
    std::string msg;
    uint16_t width = 0;
    uint8_t uid = 0;
    explicit ScrollingText(std::string&& s, uint8_t);
    void draw(Vec2& pos);
    void calculate();

   private:
    static void drawSeparator(Vec2&);
  };
  std::vector<ScrollingText> scrollingText;
  float currPos = 0;
  StatusBar();
  void draw(Entity& e, Vec2 pos) final;
};


#endif  //CXURITY_SRC_ENTITY_UI_STATUSBAR_H_
