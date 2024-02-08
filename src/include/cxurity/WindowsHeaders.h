#ifndef CXURITY_SRC_HEADERS_WINDOWSHEADERS_H_
#define CXURITY_SRC_HEADERS_WINDOWSHEADERS_H_


//Windows Headers
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
#define RPC_USE_NATIVE_WCHAR

#define CloseWindow CloseWindow_Windows
#define ShowCursor ShowCursor_Windows
#define Rectangle Rectangle_Windows

#include <WinSock2.h>
#include <Windows.h>
#include <Psapi.h>
#include <WinUser.h>
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

#endif  //CXURITY_SRC_HEADERS_WINDOWSHEADERS_H_
