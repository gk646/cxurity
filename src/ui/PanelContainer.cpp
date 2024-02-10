#include "PanelContainer.h"

PanelContainer::~PanelContainer() {
  for(auto panel : panels){
    delete panel;
  }
}
