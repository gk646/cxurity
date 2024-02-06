#ifndef CXURITY_SRC_UTIL_WORKER_H_
#define CXURITY_SRC_UTIL_WORKER_H_

#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

namespace cxu::worker {
inline std::queue<std::function<void()>> TASKS{};
inline std::mutex queue_mutex{};
inline std::condition_variable condition{};
inline bool stopWorkers = false;
inline std::vector<std::thread> workers;

inline void enqueueTask(std::function<void()> task) noexcept {
  {
    std::lock_guard<std::mutex> lock(queue_mutex);
    TASKS.push(std::move(task));
  }
  condition.notify_one();
}

inline void IMPL_worker() noexcept {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      condition.wait(lock, [] { return !TASKS.empty() || stopWorkers; });
      if (stopWorkers && TASKS.empty()) break;
      task = std::move(TASKS.front());
      TASKS.pop();
    }
    task();
  }
}

inline void IMPL_initWorkers(uint8_t numWorkers) noexcept {
  for (uint8_t i = 0; i < numWorkers; ++i) {
    workers.emplace_back(IMPL_worker);
  }
  std::cout << "Registered " << (int)numWorkers << " Workers" << std::endl;
}

inline void IMPL_stopAllWorkers() noexcept {
  {
    std::lock_guard<std::mutex> lock(queue_mutex);
    stopWorkers = true;
  }
  condition.notify_all();
  for (auto& t : workers) {
    if (t.joinable()) {
      t.join();
    }
  }
  std::cout << "Successfully closed " << workers.size() << " Workers" << std::endl;
}
}  // namespace cxu::worker
#endif  //CXURITY_SRC_UTIL_WORKER_H_
