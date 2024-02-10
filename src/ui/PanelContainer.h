#ifndef CXURITY_SRC_UI_PANELCONTAINER_H_
#define CXURITY_SRC_UI_PANELCONTAINER_H_

#include <vector>
#include "UIPanel.h"

struct PanelContainer : UIComponent {
  std::vector<UIPanel*> panels;
  ~PanelContainer() override;
};

#endif  //CXURITY_SRC_UI_PANELCONTAINER_H_
