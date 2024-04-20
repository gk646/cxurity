#include "ProcessDetector.h"

#include "../data/Snapshot.h"

ProcessDetector::ProcessDetector() {

}

float ProcessDetector::getReconstructionError(uint32_t pid, const Snapshot& s) {
  Process* process = nullptr;
  for (uint_fast32_t i = 0; i < s.pList.len; i++) {
    if (s.pList[i].values[PI_ID] == pid) {
      process = &s.pList[i];
      break;
    }
  }

  if (!process) {
    return -1.0f;
  }

  torch::Tensor mse;
  torch::manual_seed(42);  // For reproducible results
  for (uint_fast32_t i = 0; i < 100; i++) {
    auto in = torch::randn({PI_VALUES_CNT});
    auto output = autoEncoder.forward(in);
    mse = torch::mse_loss(in, output);
  }

  return mse.item<float>();
}