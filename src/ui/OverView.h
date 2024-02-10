#ifndef CXURITY_SRC_UI_OVERVIEW_H_
#define CXURITY_SRC_UI_OVERVIEW_H_

#include "PanelContainer.h"

struct OverView : public PanelContainer {
  OverView();
  void draw(Entity&, Vec2) final;
};

#endif  //CXURITY_SRC_UI_OVERVIEW_H_
