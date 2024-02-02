#include "../../../cxurity.h"
#include "CXStructs.h"

ProcessList ProcessFetcher::getProcessList(uint16_t limit) {
  cxstructs::vec<Process, false> localList;
#ifdef CXU_HOST_SYSTEM_WIN
  if (limit == 0) limit = UINT16_MAX;

  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    std::cerr << "CreateToolhelp32Snapshot failed." << std::endl;
    return ProcessList{nullptr, 0};
  }

  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  localList.reserve(limit > 1000 ? 1000 : limit);

  if (Process32First(hProcessSnap, &pe32)) {
    do {
      localList.emplace_back(pe32);
      if (localList.size() >= limit) break;
    } while (Process32Next(hProcessSnap, &pe32));
  } else {
    std::cerr << "Process32First failed." << std::endl;
  }

  CloseHandle(hProcessSnap);
#elif CXU_HOST_SYSTEM_UNIX

#endif

  auto ptr = localList.get_raw();
  localList.get_raw() = nullptr;

  return {ptr, (uint16_t) localList.size()};
}
