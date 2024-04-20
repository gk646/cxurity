#ifdef CXU_HOST_SYSTEM_WIN
#include <cxurity/WindowsHeaders.h>
#endif

#include <cxutil/cxtime.h>
using namespace cxstructs;

#include "ProcessFetcher.h"
#include "common/OSUtil.h"

ProcessList ProcessFetcher::getBaseProcessList(uint16_t limit) {
  cxstructs::now();
  ProcessList pList;
  limit = limit == 0 ? 150 : limit > 500 ? 500 : limit;
  pList.reserve(limit);

  iterateProcesses(pList, limit);

  cxstructs::printTime<std::chrono::milliseconds>("Processes fetched in: ");
  return pList;
}

void ProcessFetcher::iterateProcesses(ProcessList& pList, uint16_t limit) {
#ifdef CXU_HOST_SYSTEM_WIN
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    std::cerr << "CreateToolhelp32Snapshot failed." << std::endl;
    return;
  }
  PROCESSENTRY32 pe32;
  PROCESS_MEMORY_COUNTERS pmc;
  uint64_t uTime;
  uint64_t kTime;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(hProcessSnap, &pe32)) {
    do {
      if (pe32.th32ProcessID == 0) continue;
      queryMemCPUInfo(&pe32, &pmc, uTime, kTime);
      pList.emplace_back(&pe32, &pmc, uTime, kTime);
      if (pList.len >= limit) break;
    } while (Process32Next(hProcessSnap, &pe32));
  } else {
    std::cerr << "Process32First failed." << std::endl;
  }
  CloseHandle(hProcessSnap);
#elif CXU_HOST_SYSTEM_UNIX

#endif
}


#ifdef CXU_HOST_SYSTEM_WIN
void ProcessFetcher::queryMemCPUInfo(void* pe32Ptr, void* pmcPtr, uint64_t& uTime,
                                     uint64_t& kTime) {
  auto& pe32 = *(PROCESSENTRY32*)pe32Ptr;
  auto& pmc = *(PROCESS_MEMORY_COUNTERS*)pmcPtr;

  HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe32.th32ProcessID);

  if (hProcess == nullptr) {
    DWORD dwError = GetLastError();
    std::cerr << "OpenProcess " << pe32.th32ProcessID << " failed with error " << dwError
              << std::endl;
  }

  GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

  FILETIME ftCreation, ftExit, ftKernel, ftUser;
  if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
    uTime = fileTimeToUInt64(ftUser);
    kTime = fileTimeToUInt64(ftKernel);
    std::cout << kTime << std::endl;
  }

  CloseHandle(hProcess);
}
#endif