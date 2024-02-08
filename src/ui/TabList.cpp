#include "TabList.h"

void TabList::setSelected(Tab* sTab) {
  for (auto& t : tabs) {
    t.isSelected = false;
    if (&t == sTab) {
      t.isSelected = true;
    }
  }
}

void TabList::addTab(Tab&& t) {
  tabs.emplace_back(std::move(t));
}