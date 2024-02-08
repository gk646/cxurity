#include <cxurity/Entity.h>

#include "DataBase.h"

DataBase::DataBase() {}

void DataBase::onEvent(const Event& e) {
  if (e.type == CXU_EventType::REQUEST_DB_REFRESH) {
    e.entity.eBus->pushEvent(Event({CXU_EventType::REQUEST_ENTITY_INFO_UPDATE, e.entity}));
  }

  if (e.type == CXU_EventType::ENTITY_INFO_UPDATE_FINISHED) {
    pUpdater.update();
  }
}

std::vector<const Snapshot*> DataBase::getLastX(uint8_t x) {
  std::lock_guard<std::mutex> lock(mtx);
  auto size = history.size();
  if (size >= x) {
    std::vector<Snapshot*> ret(x);
    for (int i = 0; i < x; i++) {
      ret[i] = &history[(size - 1) - i];
    }
  }
  return {nullptr};
}

const Snapshot& DataBase::getLatest() const {
  std::lock_guard<std::mutex> lock(mtx);
  if (history.empty()) {
    throw std::out_of_range("Index out of range.");
  }
  return history.back();
}