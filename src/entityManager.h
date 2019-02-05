#pragma once
#include "entity.h"

/*
 * The entity manager exists to keep track of entity IDs to make sure that
 * conflicts don't happen. Read more here:
 * https://medium.com/@savas/nomad-game-engine-part-3-the-big-picture-743cec145685
 */
namespace nomad {
class EntityManager {
public:
  Entity createEntity();
  void destroy(Entity entity);

private:
  int lastEntity = 0;
};
} // namespace nomad
