#ifndef CXURITY_SRC_ENTITY_DATA_PROCESS_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESS_H_

#include <cxurity/common.h>
#include <iostream>

struct Process {
  double values[PI_VALUES_CNT];
  CXU_ProcessType infType = CXU_ProcessType::UNSET;
  Process(){};
#ifdef CXU_HOST_SYSTEM_WIN
  // PROCESSENTRY32 |  PROCESS_MEMORY_COUNTERS
  explicit Process(void*, void*, uint64_t, uint64_t);
#endif
  Process(const Process&) = default;
  Process(Process&&) = default;
  Process& operator=(const Process&) = default;
  Process& operator=(Process&&) = default;
  inline double operator[](uint8_t idx) const noexcept { return values[idx]; }
  friend std::ostream& operator<<(std::ostream& out, const Process& p);
};

#endif  //CXURITY_SRC_ENTITY_DATA_PROCESS_H_
