#pragma once
#include "componentManager.h"
#include "entity.h"

/*
 * This is the implementation for a component handle. With this implementation,
 * a component handle is only valid for the update that it is fetched on.
 * Holding on to a handle will cause bugs.
 *
 * What is a handle?
 * https://medium.com/@savas/nomad-game-engine-part-4-2-adding-handles-8d299d80c7d0
 *
 * How do I use a component handle?
 *
 * There are two ways to access a component using the handle. Access members of
 * the component using the arrow operator:
 *
 * PositionHandle handle;
 * handle->x++;
 *
 */
namespace nomad {
template <typename ComponentType> struct ComponentHandle {
  using ExposedComponentType =
      typename ComponentManager<ComponentType>::LookupType;

  Entity owner;
  ExposedComponentType *component;
  ComponentManager<ComponentType> *manager;

  // Empty constructor used for World::unpack()
  ComponentHandle(){};
  ComponentHandle(Entity owner, ExposedComponentType *component,
                  ComponentManager<ComponentType> *manager) {
    this->owner = owner;
    this->component = component;
    this->manager = manager;
  }

  // handle->member is the same as handle.component->member
  ExposedComponentType *operator->() const { return component; }

  void destroy() { manager->destroyComponent(owner); }
};
} // namespace nomad