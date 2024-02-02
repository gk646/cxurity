#include "../../cxurity.h"

CXUEntityApplication::CXUEntityApplication() : entity({}) {
}

CXUEntityApplication::~CXUEntityApplication() {
  if (logThread.joinable()) logThread.join();
  if (inputThread.joinable()) inputThread.join();
}

int CXUEntityApplication::run() {

  logThread = std::thread(&CXUEntityApplication::loggingThread, this);
  inputThread = std::thread(&CXUEntityApplication::userInputThread, this);

  logThread.detach();
  inputThread.join();

  return CXU_SUCCESS;
}