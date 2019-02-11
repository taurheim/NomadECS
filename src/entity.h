#pragma once

/*
 * An entity is just an id. For a more detailed explanation read:
 * https://medium.com/@savas/nomad-game-engine-part-2-ecs-9132829188e5
 */
namespace nomad {
class World;
struct Entity {
  int id;

  // To put it in maps
  friend bool operator<(const Entity &l, const Entity &r) { return l.id < r.id; }
};
}  // namespace nomad
