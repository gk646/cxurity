#include "ProcessUpdater.h"

ProcessList ProcessUpdater::getProcessList() {
  auto baseList = pFetcher.getBaseProcessList(0);

  //TODO add network information
  nFetcher.addNetworkInformation(baseList);

  return baseList;
}
