#include "../../cxurity.h"

CXUEntityApplication::CXUEntityApplication() : entity() {
  cxu::worker::IMPL_initWorkers(4);
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