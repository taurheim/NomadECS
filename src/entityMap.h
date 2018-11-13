#pragma once
#include "entity.h"

/*
 * Effectively a bidirectional map
 * Entity <-> ComponentInstance
 */

namespace nomad {
  typedef unsigned int ComponentInstance;

  struct EntityMap {
    Entity getEntity(ComponentInstance instance) {
      return instanceToEntity->at(instance);
    }

    ComponentInstance getInstance(Entity entity) {
      return entityToInstance[entity];
    }

    void update(Entity entity, ComponentInstance instance) {
      entityToInstance[entity] = instance;
      instanceToEntity[instance] = entity;
    }

    void remove(Entity entity, ComponentInstance instance) {
      entityToInstance.erase(entity);
    }

    std::map<Entity, ComponentInstance> entityToInstance;
    std::array<Entity, 1024> instanceToEntity;
  }
}

