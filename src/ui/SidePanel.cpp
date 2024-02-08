
#include <raylib.h>
#include <raygui.h>
#include <common.h>
#include "SidePanel.h"

void SidePanel::draw(Entity& e, Vec2 pos) {
  DrawRectangleRounded({pos.x, pos.y, (float)GetScreenWidth() * 0.4F, (float)GetScreenHeight()},
                       0.1F, 30, lighten(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))));
  uDisplay.draw(e, {getRelSize(0.9F, CXU_WIDTH), getRelSize(0.05F, CXU_HEIGHT)});
}
