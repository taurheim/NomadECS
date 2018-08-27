#pragma once

namespace nomad {
  class World;
  template<typename ComponentType> struct ComponentHandle;
  struct Entity {
    int id;

    //To put it in maps
    friend bool operator<(const Entity& l, const Entity& r) {
      return l.id < r.id;
    }
  };
}
