#pragma once
#include "entity.h"
#include "componentManager.h"

namespace nomad {
  /*
   * A handle is only valid for this update. Don't hold on to handles anywhere.
   */
  template<typename ComponentType>
  struct ComponentHandle {
    ComponentHandle() {}
    ComponentHandle(Entity owner, typename ComponentManager<ComponentType>::LookupType * component, ComponentManager<ComponentType> * manager) {
      this->owner = owner;
      this->component = component;
      this->manager = manager;
    }
    Entity owner;
    typename ComponentManager<ComponentType>::LookupType * component;
    ComponentManager<ComponentType> * manager;

    // handle->member is the same as handle.component->member
    typename ComponentManager<ComponentType>::LookupType * operator->() const {
      return component;
    }

    void destroy() {
      manager->destroyComponent(owner);
    }
  };
}