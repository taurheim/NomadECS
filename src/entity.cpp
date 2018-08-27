#include "entity.h"
#include "world.h"

namespace nomad {
  void EntityHandle::destroy() {
    world->destroyEntity(entity);
  }
}