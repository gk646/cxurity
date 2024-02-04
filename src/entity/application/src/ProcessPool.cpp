#include "../../../cxurity.h"

ProcessPool::ProcessPool(const CXU_SecurityLevel& sLevel) : list(nullptr, 0) {}

void ProcessPool::update(Entity& e) {
  cxu::worker::enqueueTask([&]() { IMPL_update(e); });
}

void ProcessPool::filterList(CXU_SecurityLevel sLevel) {
  if (!list.ptr || sLevel == CXU_SecurityLevel::FULL) return;

  if (sLevel == CXU_SecurityLevel::MAIN_ONLY) {
    int sortBackCounter = 1;
    for (int i = 0; i < list.len; i++) {
      auto pid = list[i].pId;
      if (list.hasParent(pid)) {
        std::swap(list[i], list[list.len - sortBackCounter++]);
      }
    }
    list.len -= sortBackCounter - 1;
  }
}

void ProcessPool::createMappings() {
  for (int i = 0; i < list.len; i++) {
    idMap.insert({list[i].id, &list[i]});
  }
}

void ProcessPool::IMPL_update(Entity& e) {
  list = ProcessFetcher::getProcessList();
  filterList(e.eInfo.sLevel);
  createMappings();
}