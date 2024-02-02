#ifndef CXURITY_SRC_CXURITY_H_
#define CXURITY_SRC_CXURITY_H_

#include "cxuconfig.h"

using ProcessID = uint32_t;

enum CXU_Level : uint8_t { CXU_FULL,
                           CXU_MAIN_ONLY,
                           CXU_UNSET };

enum CXU_ProcessType : uint8_t { CXU_SYSTEM,
                                 CXU_USER_LAUNCHED,
                                 CXU_UNDEFINED,
                                 CXU_MALICIOUS };

enum CXU_Result : uint8_t { CXU_SUCCESS,
                            CXU_ERROR };

struct Process {
  char name[31];        //Process name | 30 characters + null terminator
  uint32_t id;          //Process id
  uint32_t pId;         //Process id of the parent
  uint16_t cntThreads;  //Number of execution threads started by process
  uint16_t basePriority;//Base priority of process's threads
  CXU_ProcessType infType = CXU_UNDEFINED;

  Process(){};
#ifdef CXU_HOST_SYSTEM_WIN
  explicit Process(const PROCESSENTRY32 &pe32);
#endif
  friend std::ostream &operator<<(std::ostream &out, const Process &p);
};

struct ProcessList {
  uint16_t len;
  Process *ptr;
  int64_t timestamp = std::time(nullptr);
  ProcessList(Process *ptr, uint16_t len);
  ~ProcessList();
  Process &operator[](uint32_t idx) const;
  friend std::ostream &operator<<(std::ostream &out, const ProcessList &l);
};

struct ProcessFetcher {
  static ProcessList getProcessList(uint16_t limit = 0);//Retrieves a snapshot of the current processes -limit=limits the number of entries
};

struct ProcessPool {
  std::unordered_map<Process *, ProcessID> upsMap;
  ProcessList list;
  const CXU_Level &eLevel;//entity security level

  explicit ProcessPool(const CXU_Level &eLevel);

 private:
  void IMPL_update();
};

struct EntityInformation {
  char name[31];
  CXU_Level level = CXU_MAIN_ONLY;

  //Role
};

struct Entity {
  ProcessPool pPool;      //Process Pool
  EntityInformation eInfo;//entity Information
  Entity();
};

struct CXUEntityApplication {
  Entity entity;
  std::thread logThread;
  std::thread inputThread;
  std::atomic<bool> running{true};
  std::mutex cout_mutex{};

  CXUEntityApplication();
  ~CXUEntityApplication();
  int run();

 private:
  void loggingThread() {
    while (running.load()) {
      {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Logging information..." << std::endl;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));// Log every second
    }
  }

  void userInputThread() {
    std::string input;
    while (running.load()) {
      std::getline(std::cin, input);
      if (input == "exit") {
        running.store(false);
      }
      {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "You entered: " << input << std::endl;
      }
    }
  }
};
#endif//CXURITY_SRC_CXURITY_H_
