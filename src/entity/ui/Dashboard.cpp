#include "../../cxurity.h"

Dashboard::Dashboard() {
  tabs.emplace_back(new OverView(), "Overview");
  tabs.emplace_back(new ProcessListView(), "Processes");

  if (!tabs.empty()) {
    tabs[0].isSelected = true;
  }
}

void Dashboard::draw(Entity& e, Vector2 pos) {
  float fSize = getBigFontSize();
  DrawTextCXU("Dashboard", pos, fSize, getTextColor(0), TEXT_ALIGN_LEFT, true);
  pos.y += fSize * 1.2F;
  for (auto& t : tabs) {
    if (t.draw(e, pos, CXU_TabType::DASHBOARD)) {
      setSelected(&t);
    }
    pos.x += t.getNameWidth(CXU_TabType::DASHBOARD) + 30;
  }
}