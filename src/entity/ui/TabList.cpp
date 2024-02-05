#include "../../cxurity.h"


void TabList::setSelected(Tab* sTab) {
  for (auto& t : tabs) {
    t.isSelected = false;
    if (&t == sTab) {
      t.isSelected = true;
    }
  }
}