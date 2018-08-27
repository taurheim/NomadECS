#pragma once

#include <bitset>
#include <vector>
#include "entity.h"
#include "componentMask.h"

namespace nomad {
  class World;

  class System {
    public:
      /*
       * Called before the game starts but after the world initializes
       */
      virtual void init() {};

      /*
       * Called every game update
       */
      virtual void update(int dt) {};

      /*
       * Called every frame
       */
      virtual void render() {};

      void registerWorld(World * world);
      void registerEntity(Entity & entity);
      void unRegisterEntity(Entity &entity);
      ComponentMask getSignature();
    private:
      ComponentMask signature;
      std::vector<Entity> registeredEntities;
      World * parentWorld;
  };
}
