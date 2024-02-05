#include "../cxurity.h"
#include <raylib.h>

CXUEntityApplication::CXUEntityApplication() : entity() {
  cxu::worker::IMPL_initWorkers(CXU_WORKER_THREADS);
  SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
  SetWindowState(FLAG_MSAA_4X_HINT);
  InitWindow(1196, 820, CXU_APPLICATION_NAME);
  //SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(CXU_APPLICATION_FPS);
}

CXUEntityApplication::~CXUEntityApplication() {
  cxu::worker::IMPL_stopAllWorkers();
}

int CXUEntityApplication::run() {
  while (!WindowShouldClose()) {
    entity.update(entity);
    uiRoot.draw(entity);
  }
  CloseWindow();
  return CXU_SUCCESS;
}
