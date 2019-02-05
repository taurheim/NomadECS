#include "world.h"
#include "entityHandle.h"
#include <iostream>

namespace nomad {
World::World(nomad::EntityManager *entityManager)
    : entityManager(entityManager) {}

void World::init() {
  for (auto &system : systems) {
    system->init();
  }
}

void World::update(int dt) {
  // TODO(taurheim) check to make sure that the world has called init
  for (auto &system : systems) {
    system->update(dt);
  }
}

void World::render() {
  for (auto &system : systems) {
    system->render();
  }
}

EntityHandle World::createEntity() {
  return {entityManager->createEntity(), this};
}

void World::destroyEntity(nomad::Entity entity) {
  for (auto &system : systems) {
    system->unRegisterEntity(entity);
  }

  entityManager->destroy(entity);
}

void World::addSystem(nomad::System *system) {
  system->registerWorld(this);
  systems.push_back(system);
}

void World::updateEntityMask(nomad::Entity const &entity,
                             nomad::ComponentMask oldMask) {
  ComponentMask newMask = entityMasks[entity];

  for (auto &system : systems) {
    ComponentMask systemSignature = system->getSignature();
    if (newMask.isNewMatch(oldMask, systemSignature)) {
      // We match but didn't match before
      system->registerEntity(entity);
    } else if (newMask.isNoLongerMatched(oldMask, systemSignature)) {
      system->unRegisterEntity(entity);
    }
  }
}
} // namespace nomad
