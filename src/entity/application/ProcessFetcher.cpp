#include "../../cxurity.h"
#include "CXStructs.h"

ProcessList ProcessFetcher::getProcessList(uint16_t limit) {
  cxstructs::now();
  ProcessList pList{};
  pList.reserve(limit == 0 ? 150 : limit > 500 ? 500 : limit);
#ifdef CXU_HOST_SYSTEM_WIN
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    std::cerr << "CreateToolhelp32Snapshot failed." << std::endl;
    return ProcessList{};
  }

  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(hProcessSnap, &pe32)) {
    do {
      pList.emplace_back(pe32);
      if (pList.len >= limit) break;
    } while (Process32Next(hProcessSnap, &pe32));
  } else {
    std::cerr << "Process32First failed." << std::endl;
  }

  CloseHandle(hProcessSnap);
#elif CXU_HOST_SYSTEM_UNIX

#endif
  cxstructs::printTime<std::chrono::milliseconds>("Processes fetched in: ");
  return pList;
}
