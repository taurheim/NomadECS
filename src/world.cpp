#include "world.h"
#include "component.h"

namespace nomad {
  World::World(nomad::EntityManager * entityManager) : entityManager(entityManager){

  }

  void World::init() {
    for(auto & system : systems) {
      system->init();
    }
  }

  void World::update(int dt) {
    for(auto & system : systems) {
      system->update(dt);
    }
  }

  EntityHandle World::createEntity() {
    return { entityManager->createEntity(), this };
  }

  void World::destroyEntity(nomad::Entity entity) {
    for (auto & system : systems) {
      system->unRegisterEntity(entity);
    }

    entityManager->destroy(entity);
  }

  void World::addSystem(nomad::System *system) {
    system->registerWorld(this);
    systems.push_back(system);
  }

  template<typename ComponentType>
  void World::addComponent(nomad::Entity & entity, ComponentType && component) {
    ComponentManager<ComponentType> * manager = getComponentManager<ComponentType>();
    manager->addComponent(entity, component);

    ComponentMask oldMask = entityMasks[entity];
    entityMasks[entity].addComponent<ComponentType>();

    updateEntityMask(entity, oldMask);
  }

  template<typename ComponentType>
  void World::removeComponent(nomad::Entity & entity) {
    ComponentManager<ComponentType> * manager = getComponentManager<ComponentType>();
    ComponentHandle<ComponentType> component = manager->lookup(entity);
    component.destroy();

    ComponentMask oldMask = entityMasks[entity];
    entityMasks[entity].removeComponent<ComponentType>();

    updateEntityMask(entity, oldMask);
  }

  void World::updateEntityMask(nomad::Entity & entity, nomad::ComponentMask oldMask) {
    ComponentMask newMask = entityMasks[entity];

    for (auto & system : systems) {
      ComponentMask systemSignature = system->getSignature();
      if (newMask.isNewMatch(oldMask, systemSignature)) {
        // We match but didn't match before
        system->registerEntity(entity);
      } else if (newMask.isNoLongerMatched(oldMask, systemSignature)) {
        system->unRegisterEntity(entity);
      }
    }
  }

  template<typename ComponentType>
  ComponentManager<ComponentType> * World::getComponentManager() {
    return static_cast<ComponentManager<ComponentType> *>(GetComponentFamily<ComponentType>());
  }
}
