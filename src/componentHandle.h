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
    ComponentHandle(Entity owner, ComponentType * component, ComponentManager<ComponentType> * manager) {
      this->owner = owner;
      this->component = component;
      this->manager = manager;
    }
    Entity owner;
    ComponentType * component;
    ComponentManager<ComponentType> * manager;

    // handle->member is the same as handle.component->member
    ComponentType * operator->() const {
      return component;
    }

    void destroy() {
      manager->destroyComponent(owner);
    }
  };
}