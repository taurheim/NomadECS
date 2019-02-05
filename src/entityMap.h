#pragma once
#include "entity.h"
#include <array>
#include <map>

/*
 * Effectively a bidirectional map
 * Entity <-> ComponentInstance
 */

namespace nomad {
typedef unsigned int ComponentInstance;

struct EntityMap {
  Entity getEntity(ComponentInstance instance) {
    return instanceToEntity[instance];
  }

  ComponentInstance getInstance(Entity entity) {
    return entityToInstance[entity];
  }

  void update(Entity entity, ComponentInstance instance) {
    entityToInstance[entity] = instance;
    instanceToEntity[instance] = entity;
  }

  void remove(Entity entity) { entityToInstance.erase(entity); }

  std::map<Entity, ComponentInstance> entityToInstance;
  std::array<Entity, 1024> instanceToEntity;
};
} // namespace nomad
