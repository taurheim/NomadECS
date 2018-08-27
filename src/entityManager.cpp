#include "entityManager.h"

namespace nomad {
  Entity EntityManager::createEntity() {
    lastEntity++;
    return { lastEntity };
  }

  void EntityManager::destroy(nomad::Entity entity) {
    // Do nothing for now. This will be covered in a future blog post.
  }
}
