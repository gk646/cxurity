#include <common.h>
#include <raylib.h>
#include <raygui.h>

#include "UIComponent.h"
#include "common/RaylibAddons.h"
#include "Tab.h"

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

bool Tab::draw(Entity& e, Vec2 pos, CXU_TabType tType) const {
  float fSize = UIComponent::getMediumFontSize();
  int state = 0;
  bool isPressed = false;
  Rectangle bounds = {pos.x, pos.y, getNameWidth(), fSize};

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
        DrawRectangleRounded({bounds.x + (bounds.width / 2) * 0.5F,
                              bounds.y + bounds.height + (bounds.height / 2) * 0.5F,
                              bounds.width / 3.0F, bounds.height / 4.5F},
                             0.3F, 30, UIComponent::getTextColor(1));
        component->draw(e, {GetScreenWidth() * 0.04F, pos.y + GetScreenHeight() * 0.05F});
      } else {
        component->draw(e, {GetScreenWidth() * 0.04F, pos.y + GetScreenHeight() * 0.10F});
      }
    }
  }
  DrawTextCXU(name, pos, fSize, UIComponent::getTextColor(state), TEXT_ALIGN_LEFT, isSelected);
  return isPressed;
}

float Tab::getNameWidth() const {
  float fHeight = UIComponent::getMediumFontSize();
  return MeasureTextEx(GuiGetFont(), name, fHeight, 1).x;
}
