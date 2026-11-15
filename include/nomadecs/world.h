#pragma once
#include <memory>
#include "component.h"
#include "componentHandle.h"
#include "componentManager.h"
#include "componentMask.h"
#include "entity.h"
#include "entityManager.h"
#include "system.h"
/*
 * The world is a way of linking all of the disparate parts of the ECS.
 * Users of the engine/ECS primarily interact with the world and handles.
 * Handles are exclusively built by the world.
 *
 * https://medium.com/@savas/nomad-game-engine-part-3-the-big-picture-743cec145685
 * https://medium.com/@savas/nomad-game-engine-part-6-the-world-303d305f55cb
 *
 * TODO write blog post about multiple worlds
 */

namespace nomad {
struct EntityHandle;
class World {
 public:
  explicit World(std::unique_ptr<EntityManager> entityManager);

  /*
   * Should be called before the first update, but after instantiation
   */
  void init();

  /*
   * Update game logic. This is unrelated to a frame
   * https://gafferongames.com/post/fix_your_timestep/
   */
  void update(int dt);
  /*
   * Render a frame.
   */
  void render();
  EntityHandle createEntity();
  void addSystem(std::unique_ptr<System> system);
  void destroyEntity(Entity entity);

  /*
   * This is only necessary for bridge component managers.
   * TODO write blog post on bridge component managers
   */
  template <typename ComponentType>
  void addCustomComponentManager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
    int family = GetComponentFamily<ComponentType>();
    if (family >= componentManagers.size()) {
      componentManagers.resize(family + 1);
    }
    componentManagers[family] = manager;
  }

  template <typename ComponentType>
  void addComponent(Entity const &entity, ComponentType &&component) {
    ComponentManager<ComponentType> *manager = getComponentManager<ComponentType>();
    manager->addComponent(entity, component);

    ComponentMask oldMask = entityMasks[entity];
    entityMasks[entity].addComponent<ComponentType>();

    updateEntityMask(entity, oldMask);
  }

  template <typename ComponentType>
  void removeComponent(Entity const &entity) {
    ComponentManager<ComponentType> *manager = getComponentManager<ComponentType>();
    ComponentHandle<ComponentType> component = manager->lookup(entity);
    component.destroy();

    ComponentMask oldMask = entityMasks[entity];
    entityMasks[entity].removeComponent<ComponentType>();

    updateEntityMask(entity, oldMask);
  }

  template <typename ComponentType, typename... Args>
  void unpack(Entity e, ComponentHandle<ComponentType> &handle, ComponentHandle<Args> &... args) {
    typedef ComponentManager<ComponentType> ComponentManagerType;
    auto mgr = getComponentManager<ComponentType>();
    handle = ComponentHandle<ComponentType>(e, mgr->lookup(e), mgr);

    // Recurse
    unpack<Args...>(e, args...);
  }

  // Base case
  template <typename ComponentType>
  void unpack(Entity e, ComponentHandle<ComponentType> &handle) {
    typedef ComponentManager<ComponentType> ComponentManagerType;
    auto mgr = getComponentManager<ComponentType>();
    handle = ComponentHandle<ComponentType>(e, mgr->lookup(e), mgr);
  }

 private:
  std::unique_ptr<EntityManager> entityManager;
  std::vector<std::unique_ptr<System>> systems;
  std::vector<std::unique_ptr<BaseComponentManager>> componentManagers;
  std::map<Entity, ComponentMask> entityMasks;

  void updateEntityMask(Entity const &entity, ComponentMask oldMask);

  template <typename ComponentType>
  ComponentManager<ComponentType> *getComponentManager() {
    // Need to make sure we actually have a component manager.
    // TODO(taurheim) this is a performance hit every time we add and remove a component
    int family = GetComponentFamily<ComponentType>();

    if (family >= componentManagers.size()) {
      componentManagers.resize(family + 1);
    }

    if (!componentManagers[family]) {
      componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
    }

    return static_cast<ComponentManager<ComponentType> *>(componentManagers[family].get());
  }
};
}  // namespace nomad
