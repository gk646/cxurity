#ifndef CXURITY_SRC_ENTITY_ML_PROCESSDETECTOR_H_
#define CXURITY_SRC_ENTITY_ML_PROCESSDETECTOR_H_
#include <cstdint>
#include <cxurity/common.h>

#include "AutoEncoder.h"

struct Snapshot;

struct ProcessDetector {
  AutoEncoder autoEncoder{PI_VALUES_CNT, PI_VALUES_CNT / 2, 3};

  ProcessDetector();
  float getReconstructionError(uint32_t pid, const Snapshot&);
};

#endif  //CXURITY_SRC_ENTITY_ML_PROCESSDETECTOR_H_
