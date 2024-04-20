#include "DeviceInformation.h"


#ifdef CXU_HOST_SYSTEM_WIN
#include <cxurity/WindowsHeaders.h>
#include <cstdlib>

DeviceInformation::DeviceInformation() {
  if (IsWindows10OrGreater()) {
    strcpy_s(osVersion, "Windows 10 or later");
  } else if (IsWindows8OrGreater()) {
    strcpy_s(osVersion, "Windows 8 or later");
  }

  MEMORYSTATUSEX memInfo;
  memInfo.dwLength = sizeof(MEMORYSTATUSEX);
  if (GlobalMemoryStatusEx(&memInfo)) {
    totalPhysicalMemory = memInfo.ullTotalPhys;
    availablePhysicalMemory = memInfo.ullAvailPhys;
  }

  SYSTEM_INFO sysInfo;
  GetSystemInfo(&sysInfo);
  numberOfProcessors = sysInfo.dwNumberOfProcessors;
  switch (sysInfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
      strcpy_s(processorArchitecture, "x64");
      break;
    case PROCESSOR_ARCHITECTURE_INTEL:
      strcpy_s(processorArchitecture, "x86");
      break;
  }

  sysUptimeSec = GetTickCount64();

  FILETIME ft;
  ULARGE_INTEGER li;
  GetSystemTimeAsFileTime(&ft);
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;
  lstBootSec = (li.QuadPart / 10000000ULL) - 11644473600ULL;
  lstBootSec -= sysUptimeSec;

  WCHAR buffer[256];
  DWORD bufferSize = sizeof(buffer) / sizeof(buffer[0]);
  if (GetComputerNameExW(COMPUTER_NAME_FORMAT::ComputerNamePhysicalDnsHostname, buffer,
                         &bufferSize) == 0) {
    wcscpy_s(buffer, L"Unknown");
  }
  size_t _;
  wcstombs_s(&_, name, sizeof(name), buffer, _TRUNCATE);
#else
DeviceInformation::DeviceInformation() {
#endif
}
