#ifdef CXU_HOST_SYSTEM_WIN
#include <cxurity/WindowsHeaders.h>
#endif

#include <cxutil/cxtime.h>
using namespace cxstructs;

#include "ProcessFetcher.h"
#include "common/OSUtil.h"
ProcessList ProcessFetcher::getProcessList(uint16_t limit) {
  network();
  uint16_t errCnt = 0;
  cxstructs::now();
  ProcessList pList{};
  limit = limit == 0 ? 150 : limit > 500 ? 500 : limit;
  pList.reserve(limit);
#ifdef CXU_HOST_SYSTEM_WIN
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    std::cerr << "CreateToolhelp32Snapshot failed." << std::endl;
    return ProcessList{};
  }

  PROCESSENTRY32 pe32;
  PROCESS_MEMORY_COUNTERS pmc;
  uint64_t uTime;
  uint64_t kTime;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(hProcessSnap, &pe32)) {
    do {
      HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe32.th32ProcessID);

      if (hProcess == nullptr) {
        errCnt++;
        if (errCnt < 10) {
          DWORD dwError = GetLastError();
          std::cerr << "OpenProcess " << pe32.th32ProcessID << " failed with error " << dwError
                    << std::endl;
        }
      }

      if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {}

      FILETIME ftCreation, ftExit, ftKernel, ftUser;
      if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
        uTime = fileTimeToUInt64(ftUser);
        kTime = fileTimeToUInt64(ftKernel);
      }

      CloseHandle(hProcess);

      pList.emplace_back(&pe32, &pmc, uTime, kTime);
      if (pList.len >= limit) break;
    } while (Process32Next(hProcessSnap, &pe32));
  } else {
    std::cerr << "Process32First failed." << std::endl;
  }
  CloseHandle(hProcessSnap);
#elif CXU_HOST_SYSTEM_UNIX

#endif
  std::cout << errCnt << " calls failed" << std::endl;
  cxstructs::printTime<std::chrono::milliseconds>("Processes fetched in: ");
  return pList;
}

void ProcessFetcher::network() {
  DWORD dwSize = 0;
  DWORD dwRetVal = 0;

  dwRetVal = GetExtendedTcpTable(nullptr, &dwSize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
  if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) {
    std::vector<BYTE> buffer(dwSize);
    auto pTcpTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());

    if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL,
                                        0)) == NO_ERROR) {
      for (DWORD i = 0; i < pTcpTable->dwNumEntries; i++) {
        std::cout << "PID: " << pTcpTable->table[i].dwOwningPid << std::endl;
      }
    }
  }
}