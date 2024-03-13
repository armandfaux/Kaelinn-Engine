#ifndef SCENESYSTEM_HPP_
#define SCENESYSTEM_HPP_

#include "../../EngineApi.hpp"
#include "../../core/Game.hpp"
#include "../../event/Event.hpp"
#include "../ASystem.hpp"

namespace kln {
    class ENGINE_API SceneSystem : public ASystem {
      public:
        SceneSystem(Game &parent);
        virtual ~SceneSystem() = default;

        void update(std::shared_ptr<Scene> &scene) override;

      private:
        Game &_parent;
        bool debug = false;
    };
} // namespace kln

#endif /* !SCENESYSTEM_HPP_ */
