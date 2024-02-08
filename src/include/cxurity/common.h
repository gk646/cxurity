#ifndef CXURITY_SRC_SHARED_CXUSHARED_H_
#define CXURITY_SRC_SHARED_CXUSHARED_H_

#include <cstdint>

inline const char* CXU_ROLE_NAMES[4]{"ADMIN", "USER", "UNSET", "SERVER"};
enum class CXU_EntityRole : uint8_t { ADMIN, USER, UNSET, SERVER };
enum class CXU_SecurityLevel : uint8_t { FULL, MAIN_ONLY };
enum class CXU_TabType : uint8_t { DASHBOARD, STATUS_BAR };
enum CXU_Side : uint8_t { CXU_WIDTH, CXU_HEIGHT };
enum CXU_Texture : uint8_t { APP, APP_ROUND };
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

struct Vec2 {
  float x;
  float y;
};
#endif  //CXURITY_SRC_SHARED_CXUSHARED_H_
