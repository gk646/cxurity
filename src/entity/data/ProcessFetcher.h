#ifndef CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_

#include "ProcessList.h"

struct ProcessFetcher {
  //Retrieves a snapshot of the current processes
  ProcessList getProcessList(uint16_t limit = 0);
  void network();

 private:
};




#endif  //CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_
