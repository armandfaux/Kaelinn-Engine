#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <cstdint>
#include <memory>
#include <string>

namespace kln {
    enum CompType
    {
        SPATIAL = 0,
        SPRITE,
        BODY,
        COLLIDER,
        INPUT,
        BUTTON,
        TEXT,
        COUNT // Keeping track of the amount of components
    };

    // An entity's component
    class IComponent
    {
        public:
            virtual CompType getType() = 0;

            // MUST be overrided to allow prefab duplication
            virtual std::shared_ptr<IComponent> clone() = 0;
    };
} // namespace kln

#endif