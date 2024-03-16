#ifndef TRASNFORMCOMP_HPP
#define TRASNFORMCOMP_HPP

#include <cstddef>

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace kln {
    class ENGINE_API SpatialComp : public AComponent {
      public:
        SpatialComp(Vector2 pos);
        virtual ~SpatialComp() = default;

        // getters
        Vector2 getPos();

        // setters
        void setPos(Vector2 newPos);

        std::shared_ptr<IComponent> clone() override;

      private:
        Vector2 _position;
        // TODO rotation
    };
} // namespace kln

#endif