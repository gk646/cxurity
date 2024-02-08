#include <cxurity/Worker.h>
#include <cxurity/cxuconfig.h>

#include "common/OSUtil.h"
#include "EntityApplication.h"


EntityApplication::EntityApplication() {
  cxu::worker::IMPL_initWorkers(CXU_APP_WORKER_THREADS);
  initOS();
}

EntityApplication::~EntityApplication() {
  exitOS();
  cxu::worker::IMPL_stopAllWorkers();
}

int EntityApplication::run() {
  lThread = std::thread(&EntityApplication::update, this);

  shouldStop = uiRoot.draw(entity);

  if (lThread.joinable()) {
    lThread.join();
  }

  return CXU_SUCCESS;
}

void EntityApplication::update() {
  while (!shouldStop) {
    entity.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CXU_APP_TPS));
  }
}

void EntityApplication::initOS() {
#ifdef CXU_HOST_SYSTEM_WIN
  EnableDebugPrivilege();
#elif CXU_HOST_SYSTEM_UNIX
#endif
}

void EntityApplication::exitOS() {

}