#pragma once
#include "entity.h"
#include "system.h"
#include "componentManager.h"
#include "componentMask.h"
#include "entityManager.h"

namespace nomad {
  class World {
    public:
      World(EntityManager * entityManager);
      void init();
      void update(int dt);
      EntityHandle createEntity();
      void addSystem(System * system);
      void destroyEntity(Entity entity);

      template<typename ComponentType>
      void addComponent(Entity & entity, ComponentType && component);

      template<typename ComponentType>
      void removeComponent(Entity & entity);

    private:
      EntityManager * entityManager;
      std::vector<System *> systems;
      std::vector<void *> componentManagers;
      std::map<Entity, ComponentMask> entityMasks;

      void updateEntityMask(Entity & entity, ComponentMask oldMask);

      template<typename ComponentType>
      ComponentManager<ComponentType> * getComponentManager();
  };
}
