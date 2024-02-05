#ifndef CXURITY_SRC_CXURITY_H_
#define CXURITY_SRC_CXURITY_H_

#include "cxuconfig.h"
#include "util/Worker.h"
#include "util/rayadditions.h"
#include <raylib.h>

struct Entity;

using ProcessID = uint32_t;

enum class CXU_SecurityLevel : uint8_t { FULL, MAIN_ONLY };
enum class CXU_ProcessType : uint8_t { SYSTEM, USER_LAUNCHED, UNSET, MALICIOUS, UNKNOWN };
enum class CXU_EntityRole : uint8_t { ADMIN, USER, UNSET, SERVER };
inline const char *CXU_ROLE_NAMES [4]{"ADMIN", "USER","UNSET", "SERVER" };
enum class CXU_TabType : uint8_t { DASHBOARD, STATUS_BAR };
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
  explicit Process(PROCESSENTRY32& pe32);
#endif
  friend std::ostream& operator<<(std::ostream& out, const Process& p);
};

//"Dumb" data holder with minimal dynamic array components
struct ProcessList {
  uint16_t len = 0;        //Data length
  Process* ptr = nullptr;  //Data pointer
  int64_t timestamp = 0;   //Timestamp in unix millis

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

struct ProcessFetcher {
  //Retrieves a snapshot of the current processes -limit=limits the number of entries
  static ProcessList getProcessList(uint16_t limit = 0);
};

struct ProcessPool {
  std::unordered_map<ProcessID, Process*> idMap;
  ProcessList list;

  explicit ProcessPool();
  void update(Entity&);

 private:
  uint16_t upCounter = 0;

  void createMappings();
  void filterList(CXU_SecurityLevel);
  bool isRefresh(uint16_t);
};

struct Snapshot {
  //TODO
};

struct History {
  //TODO
  std::vector<Snapshot> history;
};

struct DeviceInformation {
  char osVersion[64] = {0};              // Operating System Version
  char processorArchitecture[32] = {0};  // Processor Architecture
  char name[31] = {0};                   //Name of the entity
  uint64_t totalPhysicalMemory = 0;      // Total Physical Memory in bytes
  uint64_t availablePhysicalMemory = 0;  // Available Physical Memory in bytes
  uint64_t sysUptimeSec = 0;             // System uptime in seconds
  uint64_t lstBootSec = 0;               // Time since last boot in UNIX seconds
  uint32_t numberOfProcessors = 0;       // Number of Logical Processors
  DeviceInformation();
};

struct EntityInformation {
  DeviceInformation devInfo{};                              //Device information
  uint16_t rIntervalMil = 5000;                             //Refresh interval in millis
  CXU_SecurityLevel sLevel = CXU_SecurityLevel::MAIN_ONLY;  //Security level for this entity
  CXU_EntityRole eRole = CXU_EntityRole::UNSET;             //Role of this entity
  EntityInformation();
};

struct Entity {
  EntityInformation eInfo;  //entity Information
  ProcessPool pPool;        //Process Pool
  History history;          //Historic data
  Entity();
  void update(Entity&);
};

/* |-----------------------------------------------------|
 * |                         UI                          |
 * |-----------------------------------------------------|
 */

#define CXU_DARK_GREY \
  CLITERAL(Color) {   \
    33, 37, 40, 255   \
  }  // Light Gray
#define CXU_WHITE      \
  CLITERAL(Color) {    \
    250, 251, 251, 255 \
  }  // Gray
#define CXU_RED      \
  CLITERAL(Color) {  \
    250, 75, 65, 255 \
  }  // Dark Gray

struct UIComponent {
  Vector2 pos;
  virtual void draw(Entity&, Vector2) = 0;
  virtual ~UIComponent() = default;
  static float getBigFontSize();
  static float getMediumFontSize();
  static float getSmallFontSize();
  static Color getTextColor(int state);
  static Color darken(const Color& , int v = 10);
  static Color lighten(const Color&, int v = 10);
};

struct Tab {
  const char* name = nullptr;
  UIComponent* component = nullptr;
  bool isSelected = false;
  explicit Tab(UIComponent*, const char* name);
  Tab(const Tab&) = delete;
  Tab(Tab&&) noexcept;
  Tab& operator=(const Tab&) = delete;
  Tab& operator=(Tab&&) noexcept;
  ~Tab();
  bool draw(Entity& e, Vector2 pos, CXU_TabType) const;
  [[nodiscard]] float getNameWidth(CXU_TabType) const;
};

struct TabList : public UIComponent {
  std::vector<Tab> tabs;
  void draw(Entity& e, Vector2 pos) override = 0;

 protected:
  void setSelected(Tab*);
};

struct Dashboard : public TabList {
  Dashboard();
  void draw(Entity& e, Vector2 pos) final;
};

struct StatusBar : public TabList {
  StatusBar();
  void draw(Entity& e, Vector2 pos) final;
};
struct OverView : public UIComponent{
  void draw(Entity& e, Vector2 pos) final{};
};
struct UserDisplay : public UIComponent {
  void draw(Entity& e, Vector2 pos) final;
};

struct UISettings : public UIComponent {
  void draw(Entity& e, Vector2 pos) final{};
};

struct SidePanel : public UIComponent {
  UserDisplay uDisplay;
  void draw(Entity& e, Vector2 pos) final;
};

struct ProcessListView : public UIComponent {
  void draw(Entity& e, Vector2 pos) final;
};

struct AnomalyPanel : public UIComponent {
  void draw(Entity& e, Vector2 pos) final;
};

struct EntityUIRoot {
  StatusBar statusBar;
  SidePanel sPanel;
  void draw(Entity&);

 private:
  void styleSelector();
  int visualStyleActive = 8;
  int prevVisualStyleActive = -1;
};

/* |-----------------------------------------------------|
 * |                   APPLICATIONS                      |
 * |-----------------------------------------------------|
 */

struct CXUEntityApplication {
  Entity entity;
  EntityUIRoot uiRoot;
  CXUEntityApplication();
  ~CXUEntityApplication();
  int run();
};

#endif  //CXURITY_SRC_CXURITY_H_
