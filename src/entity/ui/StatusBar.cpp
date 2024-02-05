#include "../../cxurity.h"
#include <raylib.h>

StatusBar::StatusBar() {
  tabs.emplace_back(new Dashboard(), "Home");
  tabs.emplace_back(new UISettings(), "Settings");

  if (!tabs.empty()) {
    tabs[0].isSelected = true;
  }
}

void StatusBar::draw(Entity& e, Vector2 pos) {
  Vector2 tabStart = {pos.x + (float)GetScreenWidth() * 0.20F,
                      pos.y + (float)GetScreenHeight() * 0.03F};

  for (auto& t : tabs) {
    if (t.draw(e, tabStart, CXU_TabType::STATUS_BAR)) {
      setSelected(&t);
    }
    tabStart.x += t.getNameWidth(CXU_TabType::STATUS_BAR) + 20;
  }
}