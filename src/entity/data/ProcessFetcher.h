#ifndef CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_

#include "ProcessList.h"

struct ProcessFetcher {
  //Retrieves a snapshot of the current processes
  static ProcessList getBaseProcessList(uint16_t limit = 0);

 private:
  static void iterateProcesses(ProcessList&, uint16_t);

#ifdef CXU_HOST_SYSTEM_WIN
  static void queryMemCPUInfo(void*, void*, uint64_t&, uint64_t&);
#endif
};

#endif  //CXURITY_SRC_ENTITY_DATA_PROCESSFETCHER_H_
