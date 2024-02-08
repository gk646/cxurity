#ifndef CXURITY_SRC_UI_OSUTIL_H_
#define CXURITY_SRC_UI_OSUTIL_H_

#include "cxurity/cxuconfig.h"
#include "UICommon.h"

#ifdef CXU_HOST_SYSTEM_WIN
inline void TriggerClose() {
  PostMessage((HWND)CXU_WIN_HANDLE, WM_CLOSE, 0, 0);
}
inline void TriggerMinimize() {
  ShowWindow((HWND)CXU_WIN_HANDLE, SW_MINIMIZE);
}
inline void TriggerHide() {
  ShowWindow((HWND)CXU_WIN_HANDLE, SW_HIDE);
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
