#ifndef CXURITY_SRC_UTIL_WORKER_H_
#define CXURITY_SRC_UTIL_WORKER_H_

namespace cxu::worker {
inline static std::queue<std::function<void()>> TASKS;
inline static std::mutex queue_mutex;
inline static std::condition_variable condition;
inline static bool finished = false;

inline void enqueueTask(std::function<void()> task) noexcept {
  {
    std::lock_guard<std::mutex> lock(queue_mutex);
    TASKS.push(std::move(task));
  }
  condition.notify_one();
}

[[noreturn]] inline void IMPL_worker() noexcept {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      condition.wait(lock, [] { return !TASKS.empty() || finished; });
      task = std::move(TASKS.front());
      TASKS.pop();
    }
    task();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
inline void IMPL_initWorker() noexcept {
  std::thread(IMPL_worker).detach();
  std::cout << "Registered Worker" << std::endl;
}
}  // namespace cxu::worker
#endif  //CXURITY_SRC_UTIL_WORKER_H_
