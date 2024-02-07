#ifndef CXURITY_SRC_CXCONFIG_H_
#define CXURITY_SRC_CXCONFIG_H_

//stdlib
#include <atomic>
#include <cassert>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <ostream>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <thread>
#include <new>
#include <utility>

#define CONCAT_PATH(base, path) (base path)

//Application defines
#define CXU_APP_WORKER_THREADS 4
#define CXU_APP_FPS 120
#define CXU_APP_NAME "cxurity"
#define CXU_APP_PROCESS_NAME "cxurity.exe"
#define CXU_APP_RES_PATH "res/"
#define CXU_APP_UID 646

//OS specific
//#define CXU_HOST_SYSTEM_WIN
//#define CXU_HOST_SYSTEM_UNIX

#ifdef CXU_HOST_SYSTEM_WIN
//-----------WINDOWS DEFINES---------------
#define CXU_HOST_SYSTEM 0
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS      // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES  // VK_*
#define NOSYSMETRICS       // SM_*
#define NOMENUS            // MF_*
#define NOKEYSTATES        // MK_*
#define NOCLIPBOARD        // Clipboard routines
#define NODRAWTEXT         // DrawText() and DT_*
#define NONLS              // All NLS defines and routines
#define NOMB               // MB_* and MessageBox()
#define NOMEMMGR           // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE         // typedef METAFILEPICT
#define NOMINMAX           // Macros min(a,b) and max(a,b)
#define NOOPENFILE         // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL           // SB_* and scrolling routines
#define NOSOUND            // Sound driver routines
#define NOTEXTMETRIC       // typedef TEXTMETRIC and associated routines
#define NOWH               // SetWindowsHook and WH_*
#define NOCOMM             // COMM driver routines
#define NOKANJI            // Kanji support stuff.
#define NOHELP             // Help engine interface.
#define NOPROFILER         // Profiler interface.
#define NODEFERWINDOWPOS   // DeferWindowPos routines
#define NOMCX              // Modem Configuration Extensions

#define CloseWindow CloseWindow_Windows
#define ShowCursor ShowCursor_Windows
#define Rectangle Rectangle_Windows

#include <WinSock2.h>
#include <windows.h>
#include <Psapi.h>
#include <winuser.h>
#include <iphlpapi.h>
#include <VersionHelpers.h>
#include <TlHelp32.h>
#include <wingdi.h>
#include <dwmapi.h>
#include <shellapi.h>

#undef LoadImage

#undef CloseWindow
#undef Rectangle
#undef ShowCursor

inline int CXU_OS_RESERVED_PIDS[2] = {0, 4};  //Static array to capture reserved pids
inline HWND CXU_WIN_HANDLE;
inline WNDPROC CXU_RAYLIB_ORG_WNDPROC = nullptr;
#include <raylib.h>
#include <raygui.h>

#elif CXU_HOST_SYSTEM_UNIX
#define CXU_HOST_SYSTEM 1
//-------------UNIX DEFINES-------------
inline constexpr int CXU_OS_RESERVED_PIDS[2] = {-1, -1};  //Static array to capture reserved pids
#endif

#endif  //CXURITY_SRC_CXCONFIG_H_
