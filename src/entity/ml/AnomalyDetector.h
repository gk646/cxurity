#ifndef CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_
#define CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_

#include "../common/Events.h"

struct AnomalyDetector : EventListener {

  AnomalyDetector();
  void onEvent(const Event&);
};

#endif  //CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_
