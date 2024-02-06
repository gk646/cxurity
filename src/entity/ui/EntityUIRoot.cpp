#include "../../cxurity.h"
#include "style_jungle.h"
#include "style_candy.h"
#include "style_lavanda.h"
#include "style_cyber.h"
#include "style_terminal.h"
#include "style_ashes.h"
#include "style_bluish.h"
#include "style_dark.h"
#include "style_cherry.h"
#include "style_sunny.h"
#include "style_enefete.h"

void EntityUIRoot::draw(Entity& e) {
  BeginDrawing();
  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
  statusBar.draw(e, {0, 0});
  sPanel.draw(e, {UIComponent::getRelSize(0.7F, CXU_WIDTH), 0});
  styleSelector();
  drawOS();
  EndDrawing();
}

void EntityUIRoot::styleSelector() {
  if (visualStyleActive != prevVisualStyleActive) {
    GuiLoadStyleDefault();

    switch (visualStyleActive) {
      case 1:
        GuiLoadStyleJungle();
        break;
      case 2:
        GuiLoadStyleCandy();
        break;
      case 3:
        GuiLoadStyleLavanda();
        break;
      case 4:
        GuiLoadStyleCyber();
        break;
      case 5:
        GuiLoadStyleTerminal();
        break;
      case 6:
        GuiLoadStyleAshes();
        break;
      case 7:
        GuiLoadStyleBluish();
        break;
      case 8:
        GuiLoadStyleDark();
        break;
      case 9:
        GuiLoadStyleCherry();
        break;
      case 10:
        GuiLoadStyleSunny();
        break;
      case 11:
        GuiLoadStyleEnefete();
        break;
      default:
        break;
    }

    prevVisualStyleActive = visualStyleActive;
  }
  GuiComboBox({GetScreenWidth() * 0.90F, GetScreenHeight() * 0.96F, 100, 20},
              "default;Jungle;Candy;Lavanda;Cyber;Terminal;Ashes;Bluish;Dark;Cherry;Sunny;Enefete",
              &visualStyleActive);
}

void EntityUIRoot::drawOS() {
#ifdef CXU_HOST_SYSTEM_WIN
  auto mousePosition = GetMousePosition();
  float increment = UIComponent::getRelSize(0.015F, CXU_WIDTH);
  Rectangle caption = {UIComponent::getRelSize(0.9F, CXU_WIDTH), 3, 16, 16};
  bool insideButton = false;

  insideButton += CheckCollisionPointRec(mousePosition,caption);
  if (GuiButton(caption, "#86#")) {
    TriggerHide();
  }

  caption.x += increment;
  insideButton += CheckCollisionPointRec(mousePosition,caption);
  if (GuiButton(caption, "#116#")) {
    TriggerMinimize();
  }

  caption.x += increment;
  insideButton += CheckCollisionPointRec(mousePosition,caption);
  if (GuiButton(caption, "#128#")) {
    TriggerClose();
  }

  if (!insideButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (mousePosition.y < 17) {
      isMoving = true;
      clickOffset = mousePosition;
    }
  }

  if (isMoving) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      auto windowPosition = GetWindowPosition();
      SetWindowPosition(windowPosition.x + (mousePosition.x - clickOffset.x),
                        windowPosition.y + (mousePosition.y - clickOffset.y));
    } else {
      isMoving = false;
    }
  }
#elif CXU_HOST_SYSTEM_UNIX
#endif
}