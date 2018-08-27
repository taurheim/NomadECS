#include "componentMask.h"
#include "nomad.h"

namespace nomad {
  template<typename ComponentType>
  void ComponentMask::addComponent() {
    mask |= (1 << GetComponentFamily<ComponentType>());
  }

  template<typename ComponentType>
  void ComponentMask::removeComponent() {
    mask ^= (1 << GetComponentFamily<ComponentType>());
  }

  bool ComponentMask::isNewMatch(nomad::ComponentMask oldMask, nomad::ComponentMask systemMask) {
    return matches(systemMask) && !oldMask.matches(systemMask);
  }

  bool ComponentMask::isNoLongerMatched(nomad::ComponentMask oldMask, nomad::ComponentMask systemMask) {
    return oldMask.matches(systemMask) && !matches(systemMask);
  }

  bool ComponentMask::matches(nomad::ComponentMask systemMask) {
    return ((mask & systemMask.mask) == systemMask.mask);
  }
}
