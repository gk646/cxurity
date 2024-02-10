#ifndef CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_
#define CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_

#include "../common/Events.h"

#include "ProcessDetector.h"

struct AnomalyDetector : EventListener {
  ProcessDetector pDetector{};
  AnomalyDetector();
  void onEvent(const Event&) final;
};

#endif  //CXURITY_SRC_ENTITY_ML_ANOMALYDETECTOR_H_
