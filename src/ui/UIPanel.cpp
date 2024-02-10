#include <raylib.h>
#include "raygui/raygui.h"

#include "UIPanel.h"

void UIPanel::drawPanel(const Vec2& base) {
  auto p = getDrawPos(base);
  DrawRectangleRounded(
      {p.x, p.y, (float)GetScreenWidth() * rSize.x, (float)GetScreenHeight() * rSize.y}, 0.1F, 30,
      UIComponent::lighten(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))));
}
Vec2 UIPanel::getDrawPos(const Vec2& p) {
  return {p.x + rOffset.x * GetScreenWidth(), p.y + rOffset.y * GetScreenHeight()};
}
