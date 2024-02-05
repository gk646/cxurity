#ifndef CXURITY_SRC_UTIL_RAYADDITIONS_H_
#define CXURITY_SRC_UTIL_RAYADDITIONS_H_

#include <raylib.h>
#include <raygui.h>

inline void DrawTextCXU(const char* text, Vector2 pos, float fontSize, Color color,
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

  DrawTextEx(font, text, pos, fontSize, 1, color);
}

#endif  //CXURITY_SRC_UTIL_RAYADDITIONS_H_