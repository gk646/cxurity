#ifndef CXURITY_SRC_UTIL_RAYLIB_H_
#define CXURITY_SRC_UTIL_RAYLIB_H_

#include "cxurity/cxuconfig.h"

inline void DrawTextCXU(const char* text, Vec2 pos, float fontSize, Color color,
                        GuiTextAlignment align = TEXT_ALIGN_LEFT, bool isBold = false) {
  Font font = GuiGetFont();
  Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);

  if (align == TEXT_ALIGN_RIGHT) {
    pos.x -= textSize.x;
  } else if (align == TEXT_ALIGN_CENTER) {
    pos.x -= textSize.x / 2.0f;
  }

  if (isBold) {
    DrawTextEx(font, text, {pos.x + 1, pos.y}, fontSize, 1, color);
    DrawTextEx(font, text, {pos.x, pos.y + 1}, fontSize, 1, color);
  }

  DrawTextEx(font, text, {pos.x, pos.y}, fontSize, 1, color);
}

inline Texture LoadTextureCXU(const char* path) {
  auto img = LoadImage(path);
  auto tex = LoadTextureFromImage(img);
  UnloadImage(img);
  return tex;
}

inline void SetWindowIconCXU(){
  auto icon = LoadImage(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity.png"));
  SetWindowIcon(icon);
  UnloadImage(icon);
}
#endif  //CXURITY_SRC_UTIL_RAYLIB_H_
