#pragma once
#include <type_traits>
#include "componentManager.h"
#include "entity.h"
/*
  This is the base implementation of a component. To create your own component:

  struct Position : Component {
    int x;
    int y;
  }

  What is a component?
  https://medium.com/@savas/nomad-game-engine-part-2-ecs-9132829188e5

  What is a component family?
  https://medium.com/@savas/nomad-game-engine-part-6-the-world-303d305f55cb
*/
namespace nomad {
struct ComponentCounter {
  static int familyCounter;
};

template <typename ComponentType>
struct Component {
  static inline int family() {
    static int family = ComponentCounter::familyCounter++;
    return family;
  }
};

// Util method for getting family given type
template <typename C>
static int GetComponentFamily() {
  return Component<typename std::remove_const<C>::type>::family();
}
}  // namespace nomad
