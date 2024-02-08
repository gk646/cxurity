#include "../../headers/Applications.h"
#include "../../util/Worker.h"
#include "../../headers/WindowsHeaders.h"

CXUEntityApplication::CXUEntityApplication() {
  cxu::worker::IMPL_initWorkers(CXU_APP_WORKER_THREADS);
  initRaylib();
  initOS();
}

CXUEntityApplication::~CXUEntityApplication() {
  exitOS();
  cxu::worker::IMPL_stopAllWorkers();
  //for (auto& tex : CXU_APP_TEXTURES) {
  //  UnloadTexture(tex);
  //}
}

int CXUEntityApplication::run() {
  while (!WindowShouldClose()) {
    entity.update(entity);
    uiRoot.draw(entity);
  }
  return CXU_SUCCESS;
}

//TODO
inline BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
  TOKEN_PRIVILEGES tp;
  LUID luid;

  if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid)) {
    printf("LookupPrivilegeValue error: %u\n", GetLastError());
    return FALSE;
  }

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Luid = luid;
  tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

  if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
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
  SetWindowState(FLAG_WINDOW_UNDECORATED);

  EnableDebugPrivilege();  //Elevated privileges

#elif CXU_HOST_SYSTEM_UNIX
#endif
}

void CXUEntityApplication::initRaylib() {

}

void CXUEntityApplication::exitOS() {

}