#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <cstdint>
#include <memory>
#include <string>

namespace ge {
    // An entity's component
    class IComponent {
      public:
        virtual uint32_t getId() = 0;
        virtual std::string getName() = 0;

        // MUST be overrided to allow prefab duplication
        virtual std::shared_ptr<IComponent> clone() = 0;
    };
} // namespace ge

#endif