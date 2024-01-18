#ifndef TRASNFORMCOMP_HPP
#define TRASNFORMCOMP_HPP

#include <cstddef>

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace ge {
    class ENGINE_API SpatialComp : public AComponent {
      public:
        SpatialComp();
        SpatialComp(Vector2 pos);
        virtual ~SpatialComp() = default;

        // getters
        Vector2 getPos();

        // setters
        void setPos(Vector2 newPos);

        std::shared_ptr<IComponent> clone() override;

      private:
        Vector2 _position;
        std::string _names;
        // TODO rotation
    };
} // namespace ge

#endif