#pragma once

namespace nomad {
  struct ComponentMask {
    unsigned int mask = 0;

    template<typename ComponentType>
    void addComponent();

    template<typename ComponentType>
    void removeComponent();

    bool isNewMatch(ComponentMask oldMask, ComponentMask systemMask);

    bool isNoLongerMatched(ComponentMask oldMask, ComponentMask systemMask);

    bool matches(ComponentMask systemMask);
  };
}
