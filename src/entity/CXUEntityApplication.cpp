#include "../cxurity.h"
#include "../util/OSHelper.h"
#include <raylib.h>

CXUEntityApplication::CXUEntityApplication() : entity() {
  cxu::worker::IMPL_initWorkers(CXU_APP_WORKER_THREADS);
  initOS();
  initRaylib();
}

CXUEntityApplication::~CXUEntityApplication() {
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
  EnableDebugPrivilege();
#elif CXU_HOST_SYSTEM_UNIX
#endif
}

void CXUEntityApplication::initRaylib() {
  SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
  SetWindowState(FLAG_MSAA_4X_HINT);
  InitWindow(1196, 820, CXU_APP_NAME);
  SetTargetFPS(CXU_APP_FPS);

  SetWindowIconCXU();
  auto n = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity.png"));
  CXU_APP_TEXTURES[APP] = n;
  auto r = LoadTextureCXU(CONCAT_PATH(CXU_APP_RES_PATH, "shared/ui/icons/cxurity_circle.png"));
  CXU_APP_TEXTURES[APP_ROUND] = r;
}