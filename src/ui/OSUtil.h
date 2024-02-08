#ifndef CXURITY_SRC_UI_OSUTIL_H_
#define CXURITY_SRC_UI_OSUTIL_H_

#include "UICommon.h"
#include <cxuconfig.h>

#ifdef CXU_HOST_SYSTEM_WIN
#include <WindowsHeaders.h>

inline void TriggerClose() {
  PostMessage((HWND)CXU_WIN_HANDLE, WM_CLOSE, 0, 0);
}
inline void TriggerMinimize() {
  ShowWindow((HWND)CXU_WIN_HANDLE, SW_MINIMIZE);
}
inline void TriggerHide() {
  ShowWindow((HWND)CXU_WIN_HANDLE, SW_HIDE);
}
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
inline LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_APP + CXU_APP_UID:
      switch (lParam) {
        case WM_LBUTTONUP:
          if (IsWindowVisible(hwnd)) {
            ShowWindow(hwnd, SW_HIDE);
          } else {
            ShowWindow(hwnd, SW_RESTORE);
            SetForegroundWindow(hwnd);
          }
          return 0;
      }
      break;
    case WM_CLOSE:
      DestroyWindow(hwnd);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      if (CXU_RAYLIB_ORG_WNDPROC) {
        return CallWindowProc((WNDPROC)CXU_RAYLIB_ORG_WNDPROC, hwnd, uMsg, wParam, lParam);
      }
      break;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
inline void EnableDebugPrivilege() {
  HANDLE hToken;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
    SetPrivilege(hToken, SE_DEBUG_NAME, TRUE);
    CloseHandle(hToken);
  }
}
inline void AddTrayIcon(HWND hwnd) {
  NOTIFYICONDATA nid = {};
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.hWnd = hwnd;
  nid.uID = CXU_APP_UID;
  nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid.uCallbackMessage = WM_APP + CXU_APP_UID;  // Custom message for tray interaction
  nid.hIcon = (HICON)LoadImageA(nullptr, "res/shared/ui/icons/cxurity.ico", IMAGE_ICON, 0, 0,
                                LR_LOADFROMFILE);
  strcpy_s(nid.szTip, "Open cxurity");  // Tooltip text
  Shell_NotifyIcon(NIM_ADD, &nid);
}
inline void RemoveTrayIcon(HWND hwnd) {
  NOTIFYICONDATA nid = {};
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.hWnd = hwnd;
  nid.uID = CXU_APP_UID;
  Shell_NotifyIcon(NIM_DELETE, &nid);
}
#endif

#endif  //CXURITY_SRC_UI_OSUTIL_H_
