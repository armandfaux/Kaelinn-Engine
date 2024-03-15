#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <cstdint>
#include <memory>
#include <string>

namespace kln {
    // An entity's component
    class IComponent {
      public:
        virtual uint32_t getId() = 0; // Likely useless
        virtual std::string getName() = 0; // TODO Rename to something like "getType"

        // MUST be overrided to allow prefab duplication
        virtual std::shared_ptr<IComponent> clone() = 0;
    };
} // namespace kln

#endif