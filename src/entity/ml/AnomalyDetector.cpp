#include "AnomalyDetector.h"

#include <cxurity/Entity.h>
#include "../data/DataBase.h"

AnomalyDetector::AnomalyDetector() {

}

void AnomalyDetector::onEvent(const Event& e) {
  if (e.type == CXU_EventType::REQUEST_ANOMALY_DETECTION) {
    std::cout << pDetector.getReconstructionError(172, e.entity.dBase->getLatest()) << std::endl;
    e.entity.eBus->pushEvent({CXU_EventType::ANOMALY_DETECTION_FINISHED, e.entity});
  }
}