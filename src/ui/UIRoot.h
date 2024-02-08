#ifndef CXURITY_SRC_ENTITY_UI_UIROOT_H_
#define CXURITY_SRC_ENTITY_UI_UIROOT_H_

#include "NavigationPane.h"
#include "SidePanel.h"
#include "StatusBar.h"
#include "NavigationPane.h"

struct EntityUIRoot {
  NavigationPane nPane;
  SidePanel sPanel;
  StatusBar sBar;
  bool draw(Entity&);
  EntityUIRoot();
  ~EntityUIRoot();
 private:
  int visualStyleActive = 8;
  int prevVisualStyleActive = -1;
  bool isMoving = false;
  Vec2 clickOffset{};

  void styleSelector();
  void drawOS();
};

#endif  //CXURITY_SRC_ENTITY_UI_UIROOT_H_
