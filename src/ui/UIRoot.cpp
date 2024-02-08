#include <raygui.h>

#include "UIRoot.h"
#include "OSUtil.h"
#include "RaylibAddons.h"
#include "UICommon.h"

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

EntityUIRoot::EntityUIRoot() {
  SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
  SetWindowState(FLAG_MSAA_4X_HINT);
  InitWindow(1196, 820, CXU_APP_NAME);
  SetTargetFPS(CXU_APP_FPS);
  SetExitKey(0);

  SetWindowIconCXU();
  auto n = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity.png"));
  CXU_APP_TEXTURES[APP] = n;
  auto r = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity.png"));
  CXU_APP_TEXTURES[APP_ROUND] = r;
#ifdef CXU_HOST_SYSTEM_WIN
  CXU_WIN_HANDLE = GetWindowHandle();

  AddTrayIcon((HWND)CXU_WIN_HANDLE);
  int borderThickness = 0;
  DwmSetWindowAttribute((HWND)CXU_WIN_HANDLE, DWMWA_VISIBLE_FRAME_BORDER_THICKNESS, &borderThickness,
                        sizeof(borderThickness));
  if (IsWindows10OrGreater()) {
    BOOL useHostBackdropBrush = TRUE;  // TRUE to enable, FALSE to disable
    DwmSetWindowAttribute((HWND)CXU_WIN_HANDLE, DWMWA_USE_HOSTBACKDROPBRUSH, &useHostBackdropBrush,
                          sizeof(useHostBackdropBrush));
  }

  BOOL useImmersiveDarkMode = TRUE;  // TRUE to enable dark mode, FALSE for light mode
  DwmSetWindowAttribute((HWND)CXU_WIN_HANDLE, DWMWA_USE_IMMERSIVE_DARK_MODE, &useImmersiveDarkMode,
                        sizeof(useImmersiveDarkMode));

  DWM_WINDOW_CORNER_PREFERENCE cornerPreference =
      DWMWCP_ROUND;  // Options: DWMWCP_DEFAULT, DWMWCP_ROUND, DWMWCP_DONOTROUND
  DwmSetWindowAttribute((HWND)CXU_WIN_HANDLE, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference,
                        sizeof(cornerPreference));

  CXU_RAYLIB_ORG_WNDPROC = SetWindowLongPtr((HWND)CXU_WIN_HANDLE, GWLP_WNDPROC, (LONG_PTR)WindowProc);
  SetWindowLongPtr((HWND)CXU_WIN_HANDLE, GWLP_WNDPROC, (LONG_PTR)WindowProc);
#endif
}

EntityUIRoot::~EntityUIRoot() {
  CloseWindow();
  for (auto& t : CXU_APP_TEXTURES) {
    UnloadTexture(t);
  }
#ifdef CXU_HOST_SYSTEM_WIN
  RemoveTrayIcon((HWND)CXU_WIN_HANDLE);
#elif CXU_HOST_SYSTEM_UNIX
#endif
}
void EntityUIRoot::draw(Entity& e) {
  BeginDrawing();
  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
  nPane.draw(e, {0, 0});
  sPanel.draw(e, {UIComponent::getRelSize(0.7F, CXU_WIDTH), 0});
  sBar.draw(e, {0, UIComponent::getRelSize(0.975F, CXU_HEIGHT)});
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
  float increment = UIComponent::getRelSize(0.02F, CXU_WIDTH);
  Rectangle caption = {UIComponent::getRelSize(0.94F, CXU_WIDTH), 5, 20, 20};
  bool insideButton = false;

  insideButton += CheckCollisionPointRec(mousePosition, caption);
  if (GuiButton(caption, "#86#")) {
    TriggerHide();
  }

  caption.x += increment;
  insideButton += CheckCollisionPointRec(mousePosition, caption);
  if (GuiButton(caption, "#116#")) {
    TriggerMinimize();
  }

  caption.x += increment;
  insideButton += CheckCollisionPointRec(mousePosition, caption);
  if (GuiButton(caption, "#128#")) {
    TriggerClose();
  }

  if (!insideButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (mousePosition.y < 17) {
      isMoving = true;
      clickOffset = {mousePosition.x, mousePosition.y};
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