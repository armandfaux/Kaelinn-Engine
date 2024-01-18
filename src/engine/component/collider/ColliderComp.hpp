#ifndef COLLIDERCOMP_HPP_
#define COLLIDERCOMP_HPP_

#include <memory>

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace ge {
    class ENGINE_API ColliderComp : public AComponent {
      public:
        ColliderComp(Vector2 bounds);
        ColliderComp(Vector2 bounds, Vector2 offset);
        ColliderComp(Vector2 bounds, bool solid);
        ColliderComp(Vector2 bounds, Vector2 offset, bool solid);
        ~ColliderComp();

        // getters
        Vector2 getBounds();
        Vector2 getOffset();
        bool isSolid();
        bool isCollidingWith(uint32_t id);

        void addCollidingEntity(uint32_t id);
        void rmCollidingEntity(uint32_t id);

        std::shared_ptr<IComponent> clone() override;

      private:
        bool _solid = false;
        Vector2 _bounds;
        Vector2 _offset;
        std::vector<uint32_t> _collidingEntities;
    };
} // namespace ge

#endif /* !COLLIDERCOMP_HPP_ */
