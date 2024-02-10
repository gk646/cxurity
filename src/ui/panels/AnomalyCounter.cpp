#include "AnomalyCounter.h"

#include <raylib.h>
#include <raygui/raygui.h>
#include "../common/RaylibAddons.h"

void AnomalyCounter::draw(Entity&, Vec2 pos) {
  drawPanel(pos);
  DrawTextCXU("No anomalies detected", getDrawPos(pos), UIComponent::getSmallFontSize(),
              UIComponent::getTextColor(0), TEXT_ALIGN_LEFT);
}
