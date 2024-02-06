#include "../../cxurity.h"

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
  if (s == CXU_WIDTH) {
    return (float)GetScreenWidth() * f;
  } else {
    return (float)GetScreenHeight() * f;
  }
}
Color UIComponent::getTextColor(int state) {
  return GetColor(GuiGetStyle(DEFAULT, 2 + state * 3));
}



void ProcessListView::draw(Entity& e, Vector2 pos) {
  DrawRectangle(pos.x, pos.y, GetScreenWidth() / 4, GetScreenHeight() - 50, LIGHTGRAY);
  int len = e.pPool.list.len;
  auto ptr = e.pPool.list.ptr;
  auto fSize = getMediumFontSize();
  for (int i = 0; i < len; i++) {
    DrawTextCXU(ptr[i].name, pos, fSize, CXU_WHITE);
    pos.y += fSize + 1;
  }
}

void AnomalyPanel::draw(Entity& e, Vector2 pos) {
  int panelWidth = GetScreenWidth() / 3;
  int panelHeight = 150;
  int panelX = GetScreenWidth() - panelWidth - 20;
  int panelY = 30;
  DrawRectangle(panelX, panelY, panelWidth, panelHeight, RED);
  DrawText("Anomaly Detection", panelX + 10, panelY + 10, 10, WHITE);
  // Dummy anomaly data
  DrawText("No anomalies detected", panelX + 10, panelY + 30, 10, WHITE);
}
