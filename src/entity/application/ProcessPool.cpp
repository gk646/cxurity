#include "../../headers/DataCollection.h"
#include "../../util/Worker.h"
#include "../../headers/Entity.h"

ProcessPool::ProcessPool() {}

void ProcessPool::update(Entity& e) {
  if (isRefresh(e.eInfo.rIntervalMil)) {
    cxu::worker::enqueueTask([&]() {
      list = ProcessFetcher::getProcessList();
      filterList(e.eInfo.sLevel);
      createMappings();
    });
  }
  upCounter++;
}

void ProcessPool::filterList(CXU_SecurityLevel sLevel) {
  if (!list.ptr || sLevel == CXU_SecurityLevel::FULL) return;

  if (sLevel == CXU_SecurityLevel::MAIN_ONLY) {
    int sortBackCounter = 1;
    for (int i = 0; i < list.len; i++) {
      auto pid = list[i][PI_PID];
      if (list.hasParent(pid)) {
        std::swap(list[i], list[list.len - sortBackCounter++]);
      }
    }
    list.len -= sortBackCounter - 1;
  }
}

void ProcessPool::createMappings() {
  for (int i = 0; i < list.len; i++) {
    idMap.insert({list[i][PI_ID], &list[i]});
  }
}

bool ProcessPool::isRefresh(uint16_t rIntervalMil) {
  if ((1000.0F / CXU_APP_TPS) * upCounter >= rIntervalMil) {
    upCounter = 0;
    return true;
  }
  return false;
}