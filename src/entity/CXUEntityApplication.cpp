#include "../cxurity.h"
#include <raylib.h>

CXUEntityApplication::CXUEntityApplication() : entity() {
  cxu::worker::IMPL_initWorkers(CXU_WORKER_THREADS);
  InitWindow(1280, 960, "cxurity");
}

CXUEntityApplication::~CXUEntityApplication() {
  cxu::worker::IMPL_stopAllWorkers();
}

int CXUEntityApplication::run() {
  while (true) {
    entity.update(entity);
    std::this_thread::sleep_for(std::chrono::milliseconds(entity.eInfo.rIntervalMil));
  }

  return CXU_SUCCESS;
}