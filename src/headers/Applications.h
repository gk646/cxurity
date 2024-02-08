#ifndef CXURITY_SRC_HEADERS_APPLICATIONS_H_
#define CXURITY_SRC_HEADERS_APPLICATIONS_H_

#include "DataCollection.h"
#include "../ui/UIRoot.h"
#include "Entity.h"

struct CXUEntityApplication {
  Entity entity;
  EntityUIRoot uiRoot;
  CXUEntityApplication();
  ~CXUEntityApplication();
  int run();

 private:
  void initOS();
  void exitOS();
  void initRaylib();
};

#endif  //CXURITY_SRC_HEADERS_APPLICATIONS_H_
