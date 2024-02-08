#ifndef CXURITY_SRC_HEADERS_APPLICATIONS_H_
#define CXURITY_SRC_HEADERS_APPLICATIONS_H_

#include "DataCollection.h"
#include "../ui/UIRoot.h"
#include "Entity.h"

struct CXUEntityApplication {
  Entity entity;
  EntityUIRoot uiRoot;
  std::thread lThread;
  bool shouldStop = false;
  CXUEntityApplication();
  ~CXUEntityApplication();
  int run();

 private:
  void update();
  void initOS();
  void exitOS();
};

#endif  //CXURITY_SRC_HEADERS_APPLICATIONS_H_
