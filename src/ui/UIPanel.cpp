#include <raylib.h>
#include <raygui.h>

#include "UIPanel.h"

void UIPanel::drawPanel() {
  DrawRectangleRounded(
      {pos.x, pos.y, (float)GetScreenWidth() * rSize.x, (float)GetScreenHeight() * rSize.y}, 0.1F,
      30, lighten(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))));
}