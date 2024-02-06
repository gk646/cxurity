#ifndef CXURITY_SRC_UTIL_UTIL_H_
#define CXURITY_SRC_UTIL_UTIL_H_


inline uint64_t fileTimeToUInt64(const FILETIME& ft) {
  ULARGE_INTEGER uli;
  uli.LowPart = ft.dwLowDateTime;
  uli.HighPart = ft.dwHighDateTime;
  return uli.QuadPart;
}


#endif  //CXURITY_SRC_UTIL_UTIL_H_
