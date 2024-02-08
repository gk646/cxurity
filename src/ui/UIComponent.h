#ifndef CXURITY_SRC_ENTITY_UI_UICOMPONENT_H_
#define CXURITY_SRC_ENTITY_UI_UICOMPONENT_H_

struct Entity;
struct Color;
#include <common.h>

struct UIComponent {
  virtual void draw(Entity&, Vec2) = 0;
  virtual ~UIComponent() = default;
  static float getBigFontSize();
  static float getMediumFontSize();
  static float getSmallFontSize();
  static Color getTextColor(int state);
  static Color darken(const Color&, int v = 10);
  static Color lighten(const Color&, int v = 10);
  static float getRelSize(float, CXU_Side);
};

#endif  //CXURITY_SRC_ENTITY_UI_UICOMPONENT_H_
