#include "raygui/raygui.h"
#include <cxurity/common.h>

#include "Dashboard.h"
#include "common/RaylibAddons.h"
#include "OverView.h"

Dashboard::Dashboard() {
  tabs.emplace_back(new OverView(), "Overview");
  tabs.emplace_back(nullptr, "Processes");
  tabs.emplace_back(nullptr, "Anomalies");

  if (!tabs.empty()) {
    tabs[0].isSelected = true;
  }
}

void Dashboard::draw(Entity& e, Vec2 pos) {
  float fSize = getBigFontSize();
  DrawTextCXU("Dashboard", pos, fSize, getTextColor(0), TEXT_ALIGN_LEFT, true);
  pos.y += fSize * 1.7F;

  for (auto& t : tabs) {
    if (t.draw(e, pos, CXU_TabType::DASHBOARD)) {
      setSelected(&t);
    }
    pos.x += t.getNameWidth() + 40;
  }
}