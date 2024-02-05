#include "../../cxurity.h"
#include <raylib.h>

void UserDisplay::draw(Entity& e, Vector2 pos) {
  auto fSize = getMediumFontSize();
  DrawTextCXU(e.eInfo.devInfo.name, {GetScreenWidth() * 0.94F, pos.y}, fSize, getTextColor(0),
              TEXT_ALIGN_RIGHT,true);
  DrawTextCXU(CXU_ROLE_NAMES[(int)e.eInfo.eRole], {GetScreenWidth() * 0.94F, pos.y + fSize},
              getSmallFontSize(), darken(getTextColor(0)), TEXT_ALIGN_RIGHT);
  DrawCircle(pos.x + (float)GetScreenWidth() * 0.07F, (float)GetScreenHeight()*0.05F, 21, darken(getTextColor(0), 20));
}
