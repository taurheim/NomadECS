#pragma once
#include "entity.h"
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
    std::array<ComponentType, 1024> * data;
  };

  template<typename ComponentType>
  class ComponentManager {
    public:
      ComponentManager() {
        componentData.data = static_cast<std::array<ComponentType, 1024>*>(malloc(sizeof(ComponentType) * 1024));
      }
      ComponentInstance addComponent(Entity entity, ComponentType & component) {
        ComponentInstance newInstance = componentData.size;
        componentData.data->at(newInstance) = component;
        entityMap[entity] = newInstance;
        componentData.size++;
        return newInstance;
      }

      void destroyComponent(Entity entity) {
        // TODO write a blog post about delayed garbage collection
        // For now, there's a bug with concurrency
        ComponentInstance instance = entityMap[entity];
        componentData.data[instance] = componentData.data[componentData.size - 1];
        entityMap.erase(entity);
        componentData.size--;
      }

      ComponentType * lookup(Entity entity) {
        ComponentInstance instance = entityMap[entity];
        return &componentData.data->at(instance);
      }
    private:
      ComponentData<ComponentType> componentData;
      std::map<Entity, ComponentInstance> entityMap;
  };
}
