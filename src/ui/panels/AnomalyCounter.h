#ifndef CXURITY_SRC_UI_PANELS_ANOMALYCOUNTER_H_
#define CXURITY_SRC_UI_PANELS_ANOMALYCOUNTER_H_

#include "../UIPanel.h"

struct AnomalyCounter : public UIPanel {
  AnomalyCounter(const Vec2& pos, const Vec2& rSize) : UIPanel(pos, rSize) {}
  void draw(Entity& entity, Vec2 offset) final;
};

#endif  //CXURITY_SRC_UI_PANELS_ANOMALYCOUNTER_H_
