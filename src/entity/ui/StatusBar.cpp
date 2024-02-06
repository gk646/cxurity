#include "../../cxurity.h"

StatusBar::StatusBar() {
  tabs.emplace_back(new Dashboard(), "Home");
  tabs.emplace_back(new UISettings(), "Settings");
  tabs.emplace_back(nullptr, "Help");

  if (!tabs.empty()) {
    tabs[0].isSelected = true;
  }
}

void StatusBar::draw(Entity& e, Vector2 pos) {
  DrawTextureEx(CXU_APP_TEXTURES[APP_ROUND],
                {getRelSize(0.04F, CXU_WIDTH), getRelSize(0.04F, CXU_HEIGHT)}, 0, 1.5F, WHITE);
  Vector2 tabStart = {pos.x + (float)GetScreenWidth() * 0.21F,
                      pos.y + (float)GetScreenHeight() * 0.05F};

  for (auto& t : tabs) {
    if (t.draw(e, tabStart, CXU_TabType::STATUS_BAR)) {
      setSelected(&t);
    }
    tabStart.x += t.getNameWidth(CXU_TabType::STATUS_BAR) + 30;
  }
  Rectangle searchBox = {tabStart.x + 15, getRelSize(0.045F, CXU_HEIGHT),
                         getRelSize(0.2F, CXU_WIDTH), getRelSize(0.04F, CXU_HEIGHT)};

  if (GuiTextBox(searchBox, tBox, 32, isEditable)) {
    isEditable = !isEditable;
  }

  GuiDrawIcon(42, searchBox.x + searchBox.width * 0.85F, searchBox.y, 2,
              getTextColor(STATE_PRESSED));
}