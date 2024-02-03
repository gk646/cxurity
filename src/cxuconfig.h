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
#include <atomic>

inline const char CXU_PROCESS_NAME[12] = "cxurity.exe";  //Static array to capture reserved pids

#define CXU_WORKER_THREADS 4

//OS specific
#define CXU_HOST_SYSTEM_WIN
#define CXU_HOST_SYSTEM_UNIX
#undef CXU_HOST_SYSTEM_UNIX

#ifdef CXU_HOST_SYSTEM_WIN
//-----------WINDOWS DEFINES---------------
#define CXU_HOST_SYSTEM 0
inline constexpr int CXU_OS_RESERVED_PIDS[2] = {0, 4};  //Static array to capture reserved pids
#include <windows.h>
#include <tlhelp32.h>
#elif CXU_HOST_SYSTEM_UNIX
#define CXU_HOST_SYSTEM 1
//-------------UNIX DEFINES-------------
inline constexpr int CXU_OS_RESERVED_PIDS[2] = {-1, -1};  //Static array to capture reserved pids
#endif

#endif  //CXURITY_SRC_CXCONFIG_H_
