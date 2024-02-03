#include "../../../cxurity.h"

ProcessPool::ProcessPool(const CXU_SecurityLevel& sLevel)
    : sLevel(sLevel), list(ProcessFetcher::getProcessList()) {}

void ProcessPool::update(Entity& e) {
  list = ProcessFetcher::getProcessList();
  std::cout << "Refreshed Process List" << std::endl;
}

void ProcessPool::IMPL_update() {
  std::cout << "fetching" << std::endl;
}