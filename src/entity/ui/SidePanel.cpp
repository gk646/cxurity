#include "../../cxurity.h"
#include <raylib.h>

void SidePanel::draw(Entity& e, Vector2 pos) {
  DrawRectangleRounded({pos.x, pos.y, (float)GetScreenWidth()*0.4F, (float)GetScreenHeight()}, 0.1F, 30,
                       lighten(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))));
  uDisplay.draw(e, {(float)GetScreenWidth()*0.90F, (float)GetScreenHeight() * 0.03F});
}
