#pragma once
#include "nomad.h"
#include <array>
#include <map>

/*
 * https://medium.com/@savas/nomad-game-engine-part-4-1-generic-component-managers-dbe376f10836
 */
namespace nomad {
  typedef unsigned int ComponentInstance;

  template<typename ComponentType>
  struct ComponentData {
    unsigned int size = 1;
    std::array<ComponentType, 1024> data;
  };

  template<typename ComponentType>
  class ComponentManager {
    public:
      ComponentInstance addComponent(Entity entity, ComponentType & component);
      void destroyComponent(Entity entity);
      ComponentType * lookup(Entity entity);
    private:
      ComponentData<ComponentType> componentData;
      std::map<Entity, ComponentInstance> entityMap;
  };
}
