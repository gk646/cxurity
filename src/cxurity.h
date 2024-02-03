#ifndef CXURITY_SRC_CXURITY_H_
#define CXURITY_SRC_CXURITY_H_

#include "cxuconfig.h"
#include "util/Worker.h"

struct Entity;

using ProcessID = uint32_t;

enum class CXU_SecurityLevel : uint8_t { FULL, MAIN_ONLY };
enum class CXU_ProcessType : uint8_t { SYSTEM, USER_LAUNCHED, UNSET, MALICIOUS, UNKNOWN };
enum class CXU_EntityRole : uint8_t { ADMIN, USER, UNSET, SERVER };
enum CXU_Result : uint8_t { CXU_SUCCESS, CXU_ERROR };

struct Process {
  char name[31];          //Process name | 30 characters + null terminator
  uint32_t id;            //Process id
  uint32_t pId;           //Process id of the parent
  uint16_t cntThreads;    //Number of execution threads started by process
  uint16_t basePriority;  //Base priority of process's threads
  CXU_ProcessType infType = CXU_ProcessType::UNSET;

  Process(){};
#ifdef CXU_HOST_SYSTEM_WIN
  explicit Process(const PROCESSENTRY32& pe32);
#endif
  friend std::ostream& operator<<(std::ostream& out, const Process& p);
};

struct ProcessList {
  uint16_t len;
  Process* ptr = nullptr;
  int64_t timestamp = std::time(nullptr);
  ProcessList(Process* ptr, uint16_t len);
  ProcessList& operator=(const ProcessList&);
  ProcessList& operator=(ProcessList&&) noexcept;
  ~ProcessList();
  Process& operator[](uint32_t idx) const;
  friend std::ostream& operator<<(std::ostream& out, const ProcessList& l);
};

struct ProcessFetcher {
  //Retrieves a snapshot of the current processes -limit=limits the number of entries
  static ProcessList getProcessList(uint16_t limit = 0);
};

struct ProcessPool {
  std::unordered_map<Process*, ProcessID> upsMap;
  ProcessList list;
  const CXU_SecurityLevel& sLevel;  //entity security level

  explicit ProcessPool(const CXU_SecurityLevel& eLevel);
  void update(Entity&);

 private:
  void IMPL_update();
};

struct EntityInformation {
  char name[31] = {0};                                      //Name of the entity
  uint16_t rIntervalMil = 2000;                             //Refresh interval in millis
  CXU_SecurityLevel sLevel = CXU_SecurityLevel::MAIN_ONLY;  //Security level for this entity
  CXU_EntityRole eRole = CXU_EntityRole::UNSET;             //Role of this entity
};

struct Entity {
  ProcessPool pPool;        //Process Pool
  EntityInformation eInfo;  //entity Information
  Entity();
  void update(Entity&);

 private:
};

struct CXUEntityApplication {
  Entity entity;

  CXUEntityApplication();
  ~CXUEntityApplication();
  int run();

 private:
};
#endif  //CXURITY_SRC_CXURITY_H_
