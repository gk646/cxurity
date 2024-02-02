#include "cxurity.h"
#include <CXStructs.h>

using namespace std;
using namespace cxstructs;

int main() {
  auto cxu = new CXUEntityApplication();
  return cxu->run();
  now();
  auto list = ProcessFetcher::getProcessList();
  printTime<std::chrono::milliseconds>();

  std::cout << list << std::endl;
  //ProcessFetcher::printProcessInfo();

  return 0;
}