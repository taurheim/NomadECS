#pragma once
namespace nomad {
  class World;
  struct Entity {
    int id;

    //To put it in maps
    friend bool operator<(const Entity& l, const Entity& r) {
      return l.id < r.id;
    }
  };

  struct EntityHandle {
    Entity entity;
    World * world;

    void destroy();
  };
}
