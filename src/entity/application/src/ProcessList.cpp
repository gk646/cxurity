#include "../../../cxurity.h"

ProcessList::ProcessList(Process* ptr, uint16_t len)
    : ptr(ptr), len(len), timestamp(std::time(nullptr)) {}
ProcessList::ProcessList(ProcessList&& o) noexcept
    : ptr(o.ptr), len(o.len), timestamp(o.timestamp) {
  o.ptr = nullptr;
  o.timestamp = 0;
  o.len = 0;
}
ProcessList& ProcessList::operator=(ProcessList&& o) noexcept {
  if (&o != this) {
    delete ptr;
    ptr = o.ptr;
    len = o.len;
    timestamp = o.timestamp;

    o.ptr = nullptr;
    o.len = 0;
    o.timestamp = 0;

    return *this;
  }
}
ProcessList::~ProcessList() {
  delete ptr;
}
Process& ProcessList::operator[](uint32_t idx) const {
  if (!ptr) std::cout << "YOYO" << std::endl;
  if (idx >= len) std::cout << "OUT OF BOUNDS" << std::endl;
  return ptr[idx];
}
bool ProcessList::hasParent(uint32_t prntID) const {
  if (prntID == 0 || prntID == 4) return false;
  for (int i = 0; i < len; i++) {
    if (ptr[i].id == prntID) {
      return true;
    }
  }
  return false;
}
std::ostream& operator<<(std::ostream& out, const ProcessList& l) {
  std::time_t t = l.timestamp;
  std::tm* tm = std::localtime(&t);
  out << "Timestamp: " << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << std::endl;
  out << "Size: " << (int)l.len << std::endl;

  if (l.ptr != nullptr) {
    for (uint16_t i = 0; i < l.len; ++i) {
      out << "[" << i << "] " << l[i] << std::endl;
    }
  } else {
    out << "Empty list" << std::endl;
  }
  return out;
}
