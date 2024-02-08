#include "../../headers/DataCollection.h"
#include <chrono>

ProcessList::ProcessList() : ptr(nullptr), len(0), timestamp(std::time(nullptr)) {}
ProcessList::ProcessList(const ProcessList& other)
    : len(other.len),
      capacity(other.capacity),
      ptr(new Process[other.capacity]),
      timestamp(other.timestamp) {
  memcpy_s(ptr, sizeof(Process) * capacity, other.ptr, sizeof(Process) * other.capacity);
}
ProcessList::ProcessList(ProcessList&& other) noexcept
    : len(other.len), capacity(other.capacity), ptr(other.ptr), timestamp(other.timestamp) {
  other.ptr = nullptr;
  other.len = 0;
  other.capacity = 0;
  other.timestamp = 0;
}
ProcessList& ProcessList::operator=(ProcessList&& other) noexcept {
  if (this != &other) {
    delete[] ptr;

    ptr = other.ptr;
    len = other.len;
    capacity = other.capacity;
    timestamp = other.timestamp;

    other.ptr = nullptr;
    other.len = 0;
    other.capacity = 0;
    other.timestamp = 0;
  }
  return *this;
}
ProcessList::~ProcessList() {
  delete[] ptr;
}
Process& ProcessList::operator[](uint32_t idx) const {
  if (!ptr) std::cout << "YOYO" << std::endl;
  if (idx >= len) std::cout << "OUT OF BOUNDS" << std::endl;
  return ptr[idx];
}
void ProcessList::reserve(uint16_t newCap) {
  if (newCap <= capacity) return;
  auto* newPtr = new Process[newCap];
  for (uint16_t i = 0; i < len; ++i) {
    new (&newPtr[i]) Process(ptr[i]);
  }

  delete[] ptr;
  ptr = newPtr;
  capacity = newCap;
}
bool ProcessList::hasParent(uint32_t prntID) const {
  if (prntID == 0 || prntID == 4) return false;
  for (int i = 0; i < len; i++) {
    if (ptr[i][PI_ID] == prntID) {
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
void ProcessList::grow() {
  reserve(capacity + 25);
}
