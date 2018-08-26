#pragma once
#include <type_traits>
#include "entity.h"
#include "componentManager.h"
/*
  This is the base implementation of a component.
  https://medium.com/@savas/nomad-game-engine-part-6-the-world-303d305f55cb
  https://medium.com/@savas/nomad-game-engine-part-4-2-adding-handles-8d299d80c7d0
*/
namespace nomad {
  struct ComponentCounter {
    static int counter;
  };

  template<typename ComponentType>
  struct Component {
    static inline int family() {
      static int family = ComponentCounter::counter++;
      return family;
    }
  };

  // Util method for getting family given type
  template <typename C>
  static int GetComponentFamily() {
    return Component<typename std::remove_const<C>::type>::family();
  }

  /*
   * A handle is only valid for this update. Don't hold on to handles anywhere.
   */
  template<typename ComponentType>
  struct ComponentHandle {
      Entity owner;
      ComponentType * component;
      ComponentManager<ComponentType> * manager;

      // handle->member is the same as handle.component->member
      ComponentType * operator->() const {
        return component;
      }
  };
}

