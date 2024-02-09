#include <cxurity/Entity.h>

#include "DataBase.h"
#include <cxurity/Worker.h>

DataBase::DataBase() {}

void DataBase::onEvent(const Event& e) {
  if (e.type == CXU_EventType::REQUEST_DB_REFRESH) {
    e.entity.eBus->pushEvent({CXU_EventType::REQUEST_ENTITY_INFO_UPDATE, e.entity});
    std::cout << "update request" << std::endl;
  } else if (e.type == CXU_EventType::ENTITY_INFO_UPDATE_FINISHED) {
    std::cout << "starting process update" << std::endl;
    cxu::worker::enqueueTask([e, this]() {
      auto pList = pUpdater.getProcessList();
      history.emplace_back(*e.entity.eInfo, std::move(pList));
      e.entity.eBus->pushEvent({CXU_EventType::DB_REFRESH_FINISHED, e.entity});
      std::cout << "finished process update" << std::endl;
    });
  }

}

std::vector<const Snapshot*> DataBase::getLastX(uint8_t x) const {
  std::lock_guard<std::mutex> lock(mtx);
  auto size = history.size();
  if (size >= x) {
    std::vector<const Snapshot*> ret(x);
    for (int i = 0; i < x; i++) {
      ret[i] = &history[(size - 1) - i];
    }
    return ret;
  }
  return {nullptr};
}

const Snapshot& DataBase::getLatest() const {
  std::lock_guard<std::mutex> lock(mtx);
  if (history.empty()) {
    throw std::exception("Empty!");
  }
  return history.back();
}