#ifndef CXURITY_SRC_ENTITY_DATA_DATABASE_H_
#define CXURITY_SRC_ENTITY_DATA_DATABASE_H_

#include <vector>
#include <mutex>

#include "../common/Events.h"
#include "Snapshot.h"
#include "ProcessUpdater.h"

struct DataBase : public EventListener {
  DataBase();
  void onEvent(const Event& event) final;
  [[nodiscard]] const Snapshot& getLatest() const;
  std::vector<const Snapshot*> getLastX(uint8_t x);

 private:
  mutable std::mutex mtx;
  std::vector<Snapshot> history;
  ProcessUpdater pUpdater{};
};


#endif  //CXURITY_SRC_ENTITY_DATA_DATABASE_H_
