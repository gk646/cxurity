#include "../../../cxurity.h"

ProcessPool::ProcessPool(const CXU_Level &eLevel) : eLevel(eLevel) , list(ProcessFetcher::getProcessList()) {
  IMPL_update();
}


void ProcessPool::IMPL_update() {
  std::cout<< "fetching" << std::endl;
}