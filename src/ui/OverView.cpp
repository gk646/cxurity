#include "OverView.h"
#include "panels/AnomalyCounter.h"

OverView::OverView() {
  panels.push_back(new AnomalyCounter({0, 0}, {0.15F, 0.2F}));
  panels.push_back(new AnomalyCounter({0, 0.21F}, {0.15F, 0.1F}));

  panels.push_back(new AnomalyCounter({0.16F, 0}, {0.15F, 0.15F}));
  panels.push_back(new AnomalyCounter({0.16F, 0.16F}, {0.15F, 0.15F}));

  panels.push_back(new AnomalyCounter({0.32F, 0}, {0.31F, 0.31F}));

  panels.push_back(new AnomalyCounter({0, 0.32}, {0.45F, 0.35F}));

  panels.push_back(new AnomalyCounter({0.46F, 0.32}, {0.17F, 0.35F}));


}

void OverView::draw(Entity& e, Vec2 pos) {

  for (auto& panel : panels) {
    panel->draw(e, {pos.x, pos.y + 15});
  }
}
