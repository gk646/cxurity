#ifndef CXURITY_SRC_ENTITY_DATA_PROCESSLIST_H_
#define CXURITY_SRC_ENTITY_DATA_PROCESSLIST_H_

#include <cxurity/common.h>
#include "Process.h"

//"Dumb" data holder with minimal dynamic array components
// Cause you don't know the amount of processes beforehand
struct ProcessList {
  uint16_t len = 0;        //Data length
  Process* ptr = nullptr;  //Data pointer

  ProcessList();
  ProcessList(const ProcessList&);
  ProcessList(ProcessList&&) noexcept;
  ProcessList& operator=(const ProcessList&) = delete;
  ProcessList& operator=(ProcessList&&) noexcept;
  ~ProcessList();
  Process& operator[](uint32_t idx) const;
  [[nodiscard]] bool hasParent(uint32_t pid) const;

 public:
  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (len >= capacity) {
      grow();
    }
    new (&ptr[len]) Process(std::forward<Args>(args)...);
    len++;
  }
  void reserve(uint16_t);

  friend std::ostream& operator<<(std::ostream& out, const ProcessList& l);

 private:
  uint16_t capacity = 0;
  void grow();
};
#endif  //CXURITY_SRC_ENTITY_DATA_PROCESSLIST_H_
