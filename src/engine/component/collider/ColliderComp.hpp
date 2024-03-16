#ifndef COLLIDERCOMP_HPP_
#define COLLIDERCOMP_HPP_

#include <memory>
#include <vector>

#include "../../core/Entity.hpp"
#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace kln {
    class ENGINE_API ColliderComp : public AComponent {
      public:
        ColliderComp(Vector2 bounds, Vector2 offset, bool solid);
        ~ColliderComp();

        // getters
        Vector2 getBounds();
        Vector2 getOffset();
        bool isSolid();
        bool isCollidingWith(Entity);

        void addCollidingEntity(Entity);
        void rmCollidingEntity(Entity);

        std::shared_ptr<IComponent> clone() override;

      private:
        bool _solid = false;
        Vector2 _bounds;
        Vector2 _offset;
        // TODO Change to a set
        std::vector<Entity> _collidingEntities;
    };
} // namespace kln

#endif /* !COLLIDERCOMP_HPP_ */
