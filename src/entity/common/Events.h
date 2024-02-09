#ifndef CXURITY_SRC_ENTITY_DATA_COMMON_EVENTS_H_
#define CXURITY_SRC_ENTITY_DATA_COMMON_EVENTS_H_

#include <queue>
#include <map>

enum class CXU_EventType {
  UNDEFINED,
  REQUEST_DB_REFRESH,           // Request to refresh the database
  DB_REFRESH_FINISHED,          // Notification that database refresh is complete
  REQUEST_ENTITY_INFO_UPDATE,   // Request to update entity information
  ENTITY_INFO_UPDATE_FINISHED,  // Notification that entity information update is complete
  REQUEST_ANOMALY_DETECTION,    // Request to perform anomaly detection
  ANOMALY_DETECTION_FINISHED,   // Notification that anomaly detection is complete
};

struct Entity;
struct Event {
  CXU_EventType type = CXU_EventType::UNDEFINED;
  Entity& entity;
  Event(CXU_EventType t, Entity& e) : type(t), entity(e) {}
};

struct EventListener {
  virtual void onEvent(const Event& event) = 0;
};

struct EventBus {
  void registerListener(EventListener* listener) { listeners.push_back(listener); }
  void pushEvent(const Event& event) { eventQueue.push(event); }
  void processEvents() {
    while (!eventQueue.empty()) {
      auto event = eventQueue.front();
      eventQueue.pop();
      for (auto& handler : listeners) {
        handler->onEvent(event);
      }
    }
  }

 private:
  std::queue<Event> eventQueue;
  std::vector<EventListener*> listeners;
};
#endif  //CXURITY_SRC_ENTITY_DATA_COMMON_EVENTS_H_
