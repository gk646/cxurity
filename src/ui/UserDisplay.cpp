#include <cxurity/common.h>
#include <raylib.h>

#include "UserDisplay.h"

void UserDisplay::draw(Entity& e, Vec2 pos) {
  auto fSize = getMediumFontSize();

  //DrawTextCXU(e.eInfo.devInfo.name, {GetScreenWidth() * 0.94F, pos.y}, fSize, getTextColor(0),
           //   TEXT_ALIGN_RIGHT, true);
 // DrawTextCXU(CXU_ROLE_NAMES[(int)e.eInfo.eRole], {getRelSize(0.94F, CXU_WIDTH), pos.y + fSize},
              //getSmallFontSize(), darken(getTextColor(0)), TEXT_ALIGN_RIGHT);

  DrawCircle(pos.x + getRelSize(0.067F, CXU_WIDTH), pos.y + fSize*0.9F, 25,
             darken(getTextColor(0), 20));
}
