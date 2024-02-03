#include "../../../cxurity.h"

ProcessPool::ProcessPool(const CXU_SecurityLevel& sLevel)
    : list(ProcessFetcher::getProcessList()) {}

void ProcessPool::update(Entity& e) {

  cxu::worker::enqueueTask([&]() {
    list = ProcessFetcher::getProcessList();
    std::cout << list << std::endl;
    filterList(e.eInfo.sLevel);
    std::cout << list << std::endl;
  });
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

void ProcessPool::IMPL_update() {
  list = ProcessFetcher::getProcessList();
}