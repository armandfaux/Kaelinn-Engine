#ifndef PHYSICSYSTEM_HPP_
#define PHYSICSYSTEM_HPP_

#include <memory>
#include <vector>

#include "../../EngineApi.hpp"
#include "../../component/body/BodyComp.hpp"
#include "../../component/collider/ColliderComp.hpp"
#include "../../component/spatial/SpatialComp.hpp"
#include "../../core/Entity.hpp"
#include "../../event/Event.hpp"
#include "../../math/Time.hpp"
#include "../ASystem.hpp"

namespace ge {
    class ENGINE_API PhysicSystem : public ASystem {
      public:
        struct Rect {
            float left, top, width, height;
        };

        PhysicSystem();
        virtual ~PhysicSystem() = default;

        void update(std::shared_ptr<Scene> &scene) override;
        void checkCollisions(std::shared_ptr<Scene> &scene);
        void resolvePhysics(std::vector<std::shared_ptr<Entity>> &entities);
    };
} // namespace ge

#endif /* !PHYSICSYSTEM_HPP_ */
