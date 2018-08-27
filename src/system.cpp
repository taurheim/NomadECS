
#include "system.h"

namespace nomad {
  void System::registerWorld(World * world) {
    parentWorld = world;
  }

  void System::registerEntity(nomad::Entity & entity) {
    registeredEntities.push_back(entity);
  }

  void System::unRegisterEntity(nomad::Entity &entity) {
    for (auto it = registeredEntities.begin(); it != registeredEntities.end(); ++it) {
      Entity e = *it;
      if (e.id == entity.id) {
        registeredEntities.erase(it);
        return;
      }
    }
  }

  ComponentMask System::getSignature() {
    return signature;
  }
}
