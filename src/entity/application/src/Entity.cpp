#include "../../../cxurity.h"

Entity::Entity() : eInfo({}), pPool(eInfo.sLevel) {}

void Entity::update(Entity& e) {
  pPool.update(e);
}