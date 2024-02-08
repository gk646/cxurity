#include <raylib.h>
#include <raygui.h>

#include "UIComponent.h"

float UIComponent::getBigFontSize() {
  return GetScreenHeight() / 30.0F;
}
float UIComponent::getMediumFontSize() {
  return GetScreenHeight() / 42.0F;
}
float UIComponent::getSmallFontSize() {
  return GetScreenHeight() / 52.0F;
}
Color UIComponent::lighten(const Color& c, int v) {
  return Color{static_cast<unsigned char>(c.r + v), static_cast<unsigned char>(c.g + v),
               static_cast<unsigned char>(c.b + v), c.a};
}
Color UIComponent::darken(const Color& c, int v) {
  return Color{static_cast<unsigned char>(c.r - v), static_cast<unsigned char>(c.g - v),
               static_cast<unsigned char>(c.b - v), c.a};
}
float UIComponent::getRelSize(float f, CXU_Side s) {
  if (s ==  CXU_Side::CXU_WIDTH) {
    return (float)GetScreenWidth() * f;
  } else {
    return (float)GetScreenHeight() * f;
  }
}
Color UIComponent::getTextColor(int state) {
  return GetColor(GuiGetStyle(DEFAULT, 2 + state * 3));
}

