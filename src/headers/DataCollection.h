#ifndef CXURITY_SRC_HEADERS_DATACOLLECTION_H_
#define CXURITY_SRC_HEADERS_DATACOLLECTION_H_

#include "cxuconfig.h"
#include "../common/common.h"
#include <unordered_map>
#include <iostream>

enum class CXU_ProcessType : uint8_t { SYSTEM, USER_LAUNCHED, UNSET, MALICIOUS, UNKNOWN };
enum CXU_ProcessIndex : uint8_t {
  PI_ID,           // Process ID
  PI_PID,          // Parent Process ID
  PI_BS_PRIORITY,  // Base priority of process's threads (OS-specific normalization may be required)
  PI_CNT_THREADS,  // Count of execution threads started by the process
  PI_USR_TIME,     // CPU time in user mode, in nanoseconds
  PI_KRNL_TIME,    // CPU time in kernel mode, in nanoseconds
  PI_HSH_NAME,     // Process name hashed by std::hash
  PI_PAGE_FAULT_CNT,  // Count of page faults
  PI_PEAK_WRK_SET,    // Peak working set size, in bytes
  PI_CUR_WRK_SET,     // Current working set size, in bytes
  PI_PEAK_PAGE_FILE,  // Peak page file usage, in bytes
  PI_CUR_PAGE_FILE,   // Current page file usage, in bytes
  PI_QUOTA_PEAK_PP,   // Peak paged pool usage, in bytes
  PI_QUOTA_CUR_PP,    // Current paged pool usage, in bytes
  PI_QUOTA_PEAK_NPP,  // Peak non-paged pool usage, in bytes
  PI_QUOTA_CUR_NPP,   // Current non-paged pool usage, in bytes
  PI_VALUES_CNT       // Sentinel value
};

enum CXU_Result : int { CXU_SUCCESS, CXU_ERROR };

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

//"Dumb" data holder with minimal dynamic array components
struct ProcessList {
  uint16_t len = 0;        //Data length
  Process* ptr = nullptr;  //Data pointer
  int64_t timestamp = 0;   //Timestamp in unix millis

  ProcessList();
  ProcessList(const ProcessList&);
  ProcessList(ProcessList&&) noexcept;
  ProcessList& operator=(const ProcessList&) = delete;
  ProcessList& operator=(ProcessList&&) noexcept;
  ~ProcessList();
  Process& operator[](uint32_t idx) const;
  [[nodiscard]] bool hasParent(uint32_t pid) const;

 public:
  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (len >= capacity) {
      grow();
    }
    new (&ptr[len]) Process(std::forward<Args>(args)...);
    len++;
  }
  void reserve(uint16_t);

  friend std::ostream& operator<<(std::ostream& out, const ProcessList& l);

 private:
  uint16_t capacity = 0;
  void grow();
};

struct NetworkFetcher {
  //TODO
};

struct ProcessFetcher {
  //Retrieves a snapshot of the current processes
  static ProcessList getProcessList(uint16_t limit = 0);
  static void network();

 private:
};

struct Entity;
struct ProcessPool {
  using ProcessID = uint32_t;
  std::unordered_map<ProcessID, Process*> idMap;
  ProcessList list;

  explicit ProcessPool();
  void update(Entity&);

 private:
  uint16_t upCounter = 0;

  void createMappings();
  void filterList(CXU_SecurityLevel);
  bool isRefresh(uint16_t);
};

struct Snapshot {};

struct History {
  //TODO
  std::vector<Snapshot> history;
};


#endif  //CXURITY_SRC_HEADERS_DATACOLLECTION_H_
