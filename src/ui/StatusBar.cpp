#include <common.h>
#include <cxuconfig.h>
#include <raygui.h>
#include <raylib.h>

#include "StatusBar.h"
#include "common/RaylibAddons.h"

StatusBar::StatusBar() {
  scrollingText.emplace_back("Thank you for using cxurity", 0);
  scrollingText.emplace_back("No anomalies detected!", 1);
  scrollingText.emplace_back("Check out https://github.com/gk646/cxurity", 1);
}

void StatusBar::draw(Entity& e, Vec2 pos) {
  GuiStatusBar({pos.x, pos.y, (float)GetScreenWidth(), getRelSize(0.05F, CXU_HEIGHT)}, nullptr);
  pos.x = currPos;
  pos.y += 3;
  float sw = GetScreenWidth();
  for (auto& s : scrollingText) {
    if (pos.x > sw) {
      pos.x = pos.x - (sw + 50);
    }
    s.draw(pos);
  }

  currPos += 30.0F / CXU_APP_FPS;
  if (currPos >= sw) {
    currPos = -50;
  }
}

StatusBar::ScrollingText::ScrollingText(std::string&& s, uint8_t uid) : msg(s), uid(uid) {}

void StatusBar::ScrollingText::calculate() {
  width = (int)MeasureTextEx(GuiGetFont(), msg.c_str(), 15, 1).x;
}
void StatusBar::ScrollingText::draw(Vec2& pos) {
  calculate();
  DrawTextCXU(msg.c_str(), pos, 15, getTextColor(STATE_NORMAL));
  pos.x += width;
  drawSeparator(pos);
}

void StatusBar::ScrollingText::drawSeparator(Vec2& pos) {
  pos.x += 7;
  DrawTextCXU(" // ", pos, 15, getTextColor(STATE_NORMAL));
  pos.x += 30;
}