#ifndef CXURITY_SRC_CXCONFIG_H_
#define CXURITY_SRC_CXCONFIG_H_

#include <cstdint>

#define CONCAT_PATH(base, path) (base path)

//Application defines
#define CXU_APP_WORKER_THREADS 4
#define CXU_APP_FPS 120
#define CXU_APP_TPS 10
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
#elif CXU_HOST_SYSTEM_UNIX
#define CXU_HOST_SYSTEM 1
//-------------UNIX DEFINES-------------
#endif

#endif  //CXURITY_SRC_CXCONFIG_H_
