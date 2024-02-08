#include <string>

#include "Process.h"

#ifdef CXU_HOST_SYSTEM_WIN
#include <cxurity/WindowsHeaders.h>
Process::Process(void* pe32, void* pmc, uint64_t uTime, uint64_t kTime) {
  const auto& p32r = *(PROCESSENTRY32*)pe32;
  const auto& pmcr = *(PROCESS_MEMORY_COUNTERS*)pmc;
  values[PI_ID] = p32r.th32ProcessID;
  values[PI_PID] = p32r.th32ParentProcessID;
  values[PI_CNT_THREADS] = p32r.cntThreads;
  values[PI_BS_PRIORITY] = p32r.pcPriClassBase;
  values[PI_USR_TIME] = static_cast<double>(uTime);
  values[PI_KRNL_TIME] = static_cast<double>(kTime);
  values[PI_HSH_NAME] = static_cast<double>(std::hash<std::string>{}(p32r.szExeFile));
  values[PI_PAGE_FAULT_CNT] = pmcr.PageFaultCount;
  values[PI_PEAK_WRK_SET] = static_cast<double>(pmcr.PeakWorkingSetSize);
  values[PI_CUR_WRK_SET] = static_cast<double>(pmcr.WorkingSetSize);
  values[PI_PEAK_PAGE_FILE] = static_cast<double>(pmcr.PeakPagefileUsage);
  values[PI_CUR_PAGE_FILE] = static_cast<double>(pmcr.PagefileUsage);
  values[PI_QUOTA_PEAK_PP] = static_cast<double>(pmcr.QuotaPeakPagedPoolUsage);
  values[PI_QUOTA_CUR_PP] = static_cast<double>(pmcr.QuotaPagedPoolUsage);
  values[PI_QUOTA_PEAK_NPP] = static_cast<double>(pmcr.QuotaPeakNonPagedPoolUsage);
  values[PI_QUOTA_CUR_NPP] = static_cast<double>(pmcr.QuotaNonPagedPoolUsage);
}
#endif

std::ostream& operator<<(std::ostream& out, const Process& p) {
  return out;
}
