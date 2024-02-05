#include "../../cxurity.h"
#include <raygui.h>

Tab::Tab(UIComponent* component, const char* name) : component(component), name(name) {}

Tab::Tab(Tab&& other) noexcept
    : name(other.name), component(other.component), isSelected(other.isSelected) {
  other.component = nullptr;
}

Tab& Tab::operator=(Tab&& other) noexcept {
  if (this != &other) {
    delete component;

    name = other.name;
    component = other.component;
    isSelected = other.isSelected;

    other.component = nullptr;
  }
  return *this;
}
Tab::~Tab() {
  delete component;
}

bool Tab::draw(Entity& e, Vector2 pos, CXU_TabType tType) const {
  float fHeight = UIComponent::getMediumFontSize();
  int state = 0;
  bool isPressed = false;
  Rectangle bounds = {pos.x, pos.y, getNameWidth(tType), fHeight};

  if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      state = STATE_PRESSED;
    } else {
      state = STATE_FOCUSED;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) isPressed = true;
  }

  if (isSelected) {
    state = STATE_PRESSED;
    if (component) {
      if (tType == CXU_TabType::DASHBOARD) {
        component->draw(e, {GetScreenWidth() * 0.04F, pos.y + GetScreenHeight() * 0.05F});
      } else {
        component->draw(e, {GetScreenWidth() * 0.04F, pos.y + GetScreenHeight() * 0.07F});
      }
    }
  }
  DrawTextCXU(name, pos, fHeight, UIComponent::getTextColor(state), TEXT_ALIGN_LEFT, isSelected);
  return isPressed;
}

float Tab::getNameWidth(CXU_TabType t) const {
  float fHeight = UIComponent::getMediumFontSize();
  return MeasureTextEx(GuiGetFont(), name, fHeight, 1).x;
}
