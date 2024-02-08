#ifndef CXURITY_SRC_ENTITY_DATA_COMMON_OSUTIL_H_
#define CXURITY_SRC_ENTITY_DATA_COMMON_OSUTIL_H_

#include <cstdint>
//OS header not included here for explicitness -> Needs to be precluded

#ifdef CXU_HOST_SYSTEM_WIN
inline uint64_t fileTimeToUInt64(const FILETIME& ft) {
  ULARGE_INTEGER uli;
  uli.LowPart = ft.dwLowDateTime;
  uli.HighPart = ft.dwHighDateTime;
  return uli.QuadPart;
}
#endif
#endif  //CXURITY_SRC_ENTITY_DATA_COMMON_OSUTIL_H_
