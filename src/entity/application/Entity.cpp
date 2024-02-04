#include "../../cxurity.h"

Entity::Entity() : eInfo{}, pPool{} {}

void Entity::update(Entity& e) {
  pPool.update(e);
}