#include "componentManager.h"

namespace nomad {
  template<typename ComponentType>
  ComponentInstance ComponentManager<ComponentType>::addComponent(nomad::Entity entity, ComponentType &component) {
    ComponentInstance newInstance = componentData.size;
    componentData.data[newInstance] = component;
    entityMap[entity] = newInstance;
    componentData.size++;
    return newInstance;
  }

  template<typename ComponentType>
  void ComponentManager<ComponentType>::destroyComponent(nomad::Entity entity) {
    // TODO write a blog post about delayed garbage collection
    // For now, there's a bug with concurrency
    ComponentInstance instance = entityMap[entity];
    componentData.data[instance] = componentData.data[componentData.size - 1];
    entityMap.erase(entity);
    componentData.size--;
  }

  template<typename ComponentType>
  ComponentType* ComponentManager<ComponentType>::lookup(nomad::Entity entity) {
    ComponentInstance instance = entityMap[entity];
    return &componentData.data[instance];
  }
}