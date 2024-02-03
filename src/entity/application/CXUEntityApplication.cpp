#include "../../cxurity.h"

CXUEntityApplication::CXUEntityApplication() : entity({}) {
  for (int i = 0; i < CXU_WORKER_THREADS; i++) {
    cxu::worker::IMPL_initWorker();
  }
}

CXUEntityApplication::~CXUEntityApplication() {}

int CXUEntityApplication::run() {

  while (true) {
    entity.update(entity);
    std::this_thread::sleep_for(std::chrono::milliseconds(entity.eInfo.rIntervalMil));
  }

  return CXU_SUCCESS;
}