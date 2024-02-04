#include "../../cxurity.h"

#ifdef CXU_HOST_SYSTEM_WIN

Process::Process(PROCESSENTRY32& pe32)
    : id(pe32.th32ProcessID),
      pId(pe32.th32ParentProcessID),
      cntThreads(pe32.cntThreads),
      basePriority(pe32.pcPriClassBase) {
  strncpy_s(name, pe32.szExeFile, 30);
  name[30] = '\0';
}

#endif

std::ostream& operator<<(std::ostream& out, const Process& p) {
  out << "Process Name: " << std::setw(30) << std::left << p.name << "ID: " << p.id << ", "
      << "Parent ID: " << p.pId << ", "
      << "Thread Count: " << p.cntThreads << ", "
      << "Base Priority: " << p.basePriority << ", "
      << "Inferred Type: " << (int)p.infType;
  return out;
}
