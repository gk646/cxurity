#include "../cxurity.h"

CXUEntityApplication::CXUEntityApplication() {
  cxu::worker::IMPL_initWorkers(CXU_APP_WORKER_THREADS);
  initRaylib();
  initOS();
}

CXUEntityApplication::~CXUEntityApplication() {
  exitOS();
  cxu::worker::IMPL_stopAllWorkers();
  for (auto& tex : CXU_APP_TEXTURES) {
    UnloadTexture(tex);
  }
}

int CXUEntityApplication::run() {
  while (!WindowShouldClose()) {
    entity.update(entity);
    uiRoot.draw(entity);
  }
  CloseWindow();
  return CXU_SUCCESS;
}

void CXUEntityApplication::initOS() {
#ifdef CXU_HOST_SYSTEM_WIN
  SetWindowState(FLAG_WINDOW_UNDECORATED);
  EnableDebugPrivilege();

  CXU_WIN_HANDLE = (HWND)GetWindowHandle();
  int borderThickness = 0;
  DwmSetWindowAttribute(CXU_WIN_HANDLE, DWMWA_VISIBLE_FRAME_BORDER_THICKNESS, &borderThickness,
                        sizeof(borderThickness));

  if (IsWindows10OrGreater()) {
    BOOL useHostBackdropBrush = TRUE;  // TRUE to enable, FALSE to disable
    DwmSetWindowAttribute(CXU_WIN_HANDLE, DWMWA_USE_HOSTBACKDROPBRUSH, &useHostBackdropBrush,
                          sizeof(useHostBackdropBrush));
  }

  BOOL useImmersiveDarkMode = TRUE;  // TRUE to enable dark mode, FALSE for light mode
  DwmSetWindowAttribute(CXU_WIN_HANDLE, DWMWA_USE_IMMERSIVE_DARK_MODE, &useImmersiveDarkMode,
                        sizeof(useImmersiveDarkMode));

  DWM_WINDOW_CORNER_PREFERENCE cornerPreference =
      DWMWCP_ROUND;  // Options: DWMWCP_DEFAULT, DWMWCP_ROUND, DWMWCP_DONOTROUND
  DwmSetWindowAttribute(CXU_WIN_HANDLE, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference,
                        sizeof(cornerPreference));

  AddTrayIcon(CXU_WIN_HANDLE);

  CXU_RAYLIB_ORG_WNDPROC = (WNDPROC)SetWindowLongPtr(CXU_WIN_HANDLE, GWLP_WNDPROC, (LONG_PTR)WindowProc);
  SetWindowLongPtr(CXU_WIN_HANDLE, GWLP_WNDPROC, (LONG_PTR)WindowProc);
#elif CXU_HOST_SYSTEM_UNIX
#endif
}

void CXUEntityApplication::initRaylib() {
  SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
  SetWindowState(FLAG_MSAA_4X_HINT);
  InitWindow(1196, 820, CXU_APP_NAME);
  SetTargetFPS(CXU_APP_FPS);
  SetExitKey(0);

  SetWindowIconCXU();
  auto n = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity.png"));
  CXU_APP_TEXTURES[APP] = n;
  auto r = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity_circle.png"));
  CXU_APP_TEXTURES[APP_ROUND] = r;
}

void CXUEntityApplication::exitOS() {
#ifdef CXU_HOST_SYSTEM_WIN
  RemoveTrayIcon(CXU_WIN_HANDLE);
#elif CXU_HOST_SYSTEM_UNIX
#endif
}