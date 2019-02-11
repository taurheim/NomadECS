#pragma once

#include <bitset>
#include <vector>
#include "componentMask.h"
#include "entity.h"

/*
 * Systems are where the bulk of the game interaction code goes. Read more here:
 *
 * https://medium.com/@savas/nomad-game-engine-part-3-the-big-picture-743cec145685
 * https://medium.com/@savas/nomad-game-engine-part-5-systems-b7e86b572d7b
 */
namespace nomad {
class World;

class System {
 public:
  System() = default;
  virtual ~System() = default;
  System(const System &) = default;
  System &operator=(const System &) = default;
  System(System &&) = default;
  System &operator=(System &&) = default;

  /*
   * Called before the game starts but after the world initializes
   */
  virtual void init(){};

  /*
   * Called every game update
   */
  virtual void update(int dt){};

  /*
   * Called every frame
   */
  virtual void render(){};

  /*
   * When a system is added to the world, the world will register itself
   */
  void registerWorld(World *world);

  /*
   * When a component is added such that this system should begin acting on it,
   * register will be called.
   */
  void registerEntity(Entity const &entity);

  /*
   * If a component is removed from an entity such that the system should stop
   * acting on it, unRegister will be called.
   */
  void unRegisterEntity(Entity const &entity);
  ComponentMask getSignature();

 protected:
  std::vector<Entity> registeredEntities;
  World *parentWorld;
  ComponentMask signature;
};
}  // namespace nomad
