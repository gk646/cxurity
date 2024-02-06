#include "../../cxurity.h"
#include <raylib.h>

StatusBar::StatusBar() {
  tabs.emplace_back(new Dashboard(), "Home");
  tabs.emplace_back(new UISettings(), "Settings");
  tabs.emplace_back(nullptr, "Help");

  if (!tabs.empty()) {
    tabs[0].isSelected = true;
  }
}

void StatusBar::draw(Entity& e, Vector2 pos) {
  Vector2 tabStart = {pos.x + (float)GetScreenWidth() * 0.21F,
                      pos.y + (float)GetScreenHeight() * 0.04F};

  for (auto& t : tabs) {
    if (t.draw(e, tabStart, CXU_TabType::STATUS_BAR)) {
      setSelected(&t);
    }
    tabStart.x += t.getNameWidth(CXU_TabType::STATUS_BAR) + 30;
  }
  Rectangle searchBox = {tabStart.x + 15, (float)GetScreenHeight() * 0.035F,
                         (float)GetScreenWidth() * 0.2F, (float)GetScreenHeight() * 0.04F};

  if (GuiTextBox(searchBox, textBoxText, 54, textBoxEditMode)) {
    textBoxEditMode = !textBoxEditMode;
  }

  GuiDrawIcon(42, searchBox.x + searchBox.width * 0.85F, searchBox.y, 2,
              getTextColor(STATE_PRESSED));
}