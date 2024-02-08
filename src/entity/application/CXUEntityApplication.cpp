#include "../../headers/Applications.h"
#include "../../util/Worker.h"
#include "../../headers/WindowsHeaders.h"

CXUEntityApplication::CXUEntityApplication() {
  cxu::worker::IMPL_initWorkers(CXU_APP_WORKER_THREADS);
  initOS();
}

CXUEntityApplication::~CXUEntityApplication() {
  exitOS();
  cxu::worker::IMPL_stopAllWorkers();
}

int CXUEntityApplication::run() {
  lThread = std::thread(&CXUEntityApplication::update, this);

  shouldStop = uiRoot.draw(entity);

  if (lThread.joinable()) {
    lThread.join();
  }

  return CXU_SUCCESS;
}

void CXUEntityApplication::update() {
  while (!shouldStop) {
    entity.update(entity);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CXU_APP_TPS));
  }
}

//TODO
inline BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
  TOKEN_PRIVILEGES tp;
  LUID luid;

  if (!LookupPrivilegeValue(nullptr, lpszPrivilege, &luid)) {
    printf("LookupPrivilegeValue error: %u\n", GetLastError());
    return FALSE;
  }

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Luid = luid;
  tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

  if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
    printf("AdjustTokenPrivileges error: %u\n", GetLastError());
    return FALSE;
  }

  if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
    printf("The token does not have the specified privilege. \n");
    return FALSE;
  }

  return TRUE;
}
inline void EnableDebugPrivilege() {
  HANDLE hToken;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    SetPrivilege(hToken, SE_DEBUG_NAME, TRUE);
    CloseHandle(hToken);
  }
}

void CXUEntityApplication::initOS() {
#ifdef CXU_HOST_SYSTEM_WIN
  EnableDebugPrivilege();
#elif CXU_HOST_SYSTEM_UNIX
#endif
}

void CXUEntityApplication::exitOS() {}