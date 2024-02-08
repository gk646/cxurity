#ifndef CXURITY_SRC_ENTITY_DATA_PROCESSUPDATER_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESSUPDATER_H_

#include "NetworkFetcher.h"
#include "ProcessFetcher.h"

struct DataBase;
struct ProcessUpdater {

  void update();
 private:
  ProcessFetcher pFetcher;
  NetworkFetcher nFetcher;
};

#endif  //CXURITY_SRC_ENTITY_DATA_PROCESSUPDATER_H_
