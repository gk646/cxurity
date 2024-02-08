#ifndef CXURITY_SRC_ENTITY_UI_TAB_H_
#define CXURITY_SRC_ENTITY_UI_TAB_H_

#include <cxurity/common.h>

struct UIComponent;
struct Entity;
struct Vec2;

struct Tab {
  const char* name = nullptr;
  UIComponent* component = nullptr;
  bool isSelected = false;
  explicit Tab(UIComponent*, const char* name);
  Tab(const Tab&) = delete;
  Tab(Tab&&) noexcept;
  Tab& operator=(const Tab&) = delete;
  Tab& operator=(Tab&&) noexcept;
  ~Tab();
  bool draw(Entity& e, Vec2 pos, CXU_TabType) const;
  [[nodiscard]] float getNameWidth() const;
};

#endif  //CXURITY_SRC_ENTITY_UI_TAB_H_
