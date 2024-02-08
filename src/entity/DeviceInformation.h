#ifndef CXURITY_SRC_ENTITY_DEVICEINFORMATION_H_
#define CXURITY_SRC_ENTITY_DEVICEINFORMATION_H_

#include <cstdint>

struct DeviceInformation {
  char osVersion[64] = {0};              // Operating System Version
  char processorArchitecture[32] = {0};  // Processor Architecture
  char name[31] = {0};                   //Name of the entity
  uint64_t totalPhysicalMemory = 0;      // Total Physical Memory in bytes
  uint64_t availablePhysicalMemory = 0;  // Available Physical Memory in bytes
  uint64_t sysUptimeSec = 0;             // System uptime in seconds
  uint64_t lstBootSec = 0;               // Time since last boot in UNIX seconds
  uint32_t numberOfProcessors = 0;       // Number of Logical Processors
  DeviceInformation();
};
#endif  //CXURITY_SRC_ENTITY_DEVICEINFORMATION_H_
