#pragma once
#include "entity.h"
#include "world.h"
#include "componentHandle.h"

/*
 * An entity handle provides an easy interface for interactions with an entity.
 * Even though the entities' components are stored in completely different places,
 * the entityHandle lets them all be accessed as if they were part of the entity itself.
 *
 * Read more here:
 * https://medium.com/@savas/nomad-game-engine-part-4-2-adding-handles-8d299d80c7d0
 */
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
    void removeComponent() {
      world->removeComponent(entity);
    }

    template<typename ComponentType>
    ComponentHandle<ComponentType> getComponent() {
      ComponentHandle<ComponentType> handle;
      world->unpack(entity, handle);
      return handle;
    }
  };
}