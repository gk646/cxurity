#include "../../cxurity.h"

void UserDisplay::draw(Entity& e, Vector2 pos) {
  auto fSize = getMediumFontSize();

  DrawTextCXU(e.eInfo.devInfo.name, {GetScreenWidth() * 0.94F, pos.y}, fSize, getTextColor(0),
              TEXT_ALIGN_RIGHT, true);
  DrawTextCXU(CXU_ROLE_NAMES[(int)e.eInfo.eRole], {getRelSize(0.94F, CXU_WIDTH), pos.y + fSize},
              getSmallFontSize(), darken(getTextColor(0)), TEXT_ALIGN_RIGHT);
  DrawCircle(pos.x + getRelSize(0.07, CXU_WIDTH), getRelSize(0.05F, CXU_HEIGHT), 23,
             darken(getTextColor(0), 20));
}
