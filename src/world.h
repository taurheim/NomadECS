#pragma once
#include "entity.h"
#include "component.h"
#include "system.h"
#include "componentManager.h"
#include "componentMask.h"
#include "entityManager.h"
#include "componentHandle.h"
/*
 * The world is a way of linking all of the disparate parts of the ECS.
 * Users of the engine/ECS primarily interact with the world and handles.
 * Handles are exclusively built by the world.
 *
 * <LINK TO BLOG POST about the world>
 * TODO write a blog post about multiple worlds
 */

namespace nomad {
  class EntityHandle;
  class World {
    public:
      World(EntityManager * entityManager);

      /*
       * Should be called before the first update, but after instantiation
       */
      void init();

      /*
       * Update game logic. This is unrelated to a frame
       * TODO link to gafferongames timesstep article
       */
      void update(int dt);
      EntityHandle createEntity();
      void addSystem(System * system);
      void destroyEntity(Entity entity);

      /*
       * This is only necessary for bridge component managers. Please see the following blog post:
       * TODO blog post
       */
      template<typename ComponentType>
      void addCustomComponentManager(ComponentManager<ComponentType> * manager) {
        int family = GetComponentFamily<ComponentType>();
        if (family >= componentManagers.size()) {
          componentManagers.resize(family + 1);
        }
        componentManagers[family] = manager;
      }

      template<typename ComponentType>
      void addComponent(Entity & entity, ComponentType && component) {
        ComponentManager<ComponentType> * manager = getComponentManager<ComponentType>();
        manager->addComponent(entity, component);

        ComponentMask oldMask = entityMasks[entity];
        entityMasks[entity].addComponent<ComponentType>();

        updateEntityMask(entity, oldMask);
      }

      template<typename ComponentType>
      void removeComponent(Entity & entity) {
        ComponentManager<ComponentType> * manager = getComponentManager<ComponentType>();
        ComponentHandle<ComponentType> component = manager->lookup(entity);
        component.destroy();

        ComponentMask oldMask = entityMasks[entity];
        entityMasks[entity].removeComponent<ComponentType>();

        updateEntityMask(entity, oldMask);
      }

      template<typename ComponentType, typename ... Args>
      void unpack(Entity e, ComponentHandle<ComponentType> & handle, ComponentHandle<Args> & ... args) {
        typedef ComponentManager<ComponentType> ComponentManagerType;
        auto mgr = getComponentManager<ComponentType>();
        handle = ComponentHandle<ComponentType>(e, mgr->lookup(e), mgr);

        // Recurse
        unpack<Args...>(e, args ...);
      }

      // Base case
      template<typename ComponentType>
      void unpack(Entity e, ComponentHandle<ComponentType> & handle) {
        typedef ComponentManager<ComponentType> ComponentManagerType;
        auto mgr = getComponentManager<ComponentType>();
        handle = ComponentHandle<ComponentType>(e, mgr->lookup(e), mgr);
      }


    private:
      EntityManager * entityManager;
      std::vector<System *> systems;
      std::vector<void *> componentManagers;
      std::map<Entity, ComponentMask> entityMasks;

      void updateEntityMask(Entity & entity, ComponentMask oldMask);

      template<typename ComponentType>
      ComponentManager<ComponentType> * getComponentManager() {
        // Need to make sure we actually have a component manager.
        // TODO this is a performance hit every time we add and remove a component
        int family = GetComponentFamily<ComponentType>();

        if (family >= componentManagers.size()) {
          componentManagers.resize(family + 1);
        }

        if (!componentManagers[family]) {
          componentManagers[family] = new ComponentManager<ComponentType>();
        }

        return static_cast<ComponentManager<ComponentType> *>(componentManagers[family]);
      }
  };
}
