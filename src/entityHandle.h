#pragma once
#include "entity.h"
#include "world.h"
#include "componentHandle.h"

namespace nomad {
  struct EntityHandle {
    Entity entity;
    World * world;

    void destroy() {
      world->destroyEntity(entity);
    }

    template<typename ComponentType>
    void addComponent(ComponentType && component) {
      world->addComponent<ComponentType>(entity, std::forward<ComponentType>(component));
    }

    template<typename ComponentType>
    ComponentHandle<ComponentType> getComponent() {
      ComponentHandle<ComponentType> handle;
      world->unpack(entity, handle);
      return handle;
    }
  };
}