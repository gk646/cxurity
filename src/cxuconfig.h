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

inline const char CXU_PROCESS_NAME[12] = "cxurity.exe";  //Static array to capture reserved pids

#define CXU_WORKER_THREADS 4

//OS specific
#define CXU_HOST_SYSTEM_WIN
#define CXU_HOST_SYSTEM_UNIX
#undef CXU_HOST_SYSTEM_UNIX

#ifdef CXU_HOST_SYSTEM_WIN
//-----------WINDOWS DEFINES---------------
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS      // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES  // VK_*
#define NOWINMESSAGES      // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES        // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS       // SM_*
#define NOMENUS            // MF_*
#define NOICONS            // IDI_*
#define NOKEYSTATES        // MK_*
#define NOSYSCOMMANDS      // SC_*
#define NORASTEROPS        // Binary and Tertiary raster ops
#define NOSHOWWINDOW       // SW_*
#define OEMRESOURCE        // OEM Resource values
#define NOATOM             // Atom Manager routines
#define NOCLIPBOARD        // Clipboard routines
#define NOCOLOR            // Screen colors
#define NOCTLMGR           // Control and Dialog routines
#define NODRAWTEXT         // DrawText() and DT_*
#define NOGDI              // All GDI defines and routines
#define NOKERNEL           // All KERNEL defines and routines
#define NOUSER             // All USER defines and routines
//#define NONLS            // All NLS defines and routines
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions
#define CXU_HOST_SYSTEM 0
inline constexpr int CXU_OS_RESERVED_PIDS[2] = {0, 4};  //Static array to capture reserved pids
#include <windows.h>
#include <VersionHelpers.h>
#include <tlhelp32.h>
#elif CXU_HOST_SYSTEM_UNIX
#define CXU_HOST_SYSTEM 1
//-------------UNIX DEFINES-------------
inline constexpr int CXU_OS_RESERVED_PIDS[2] = {-1, -1};  //Static array to capture reserved pids
#endif

#endif  //CXURITY_SRC_CXCONFIG_H_
