#ifndef UIYSTEM_HPP_
#define UIYSTEM_HPP_

#include <optional>

#include "../../EngineApi.hpp"
#include "../../component/body/BodyComp.hpp"
#include "../../component/button/ButtonComp.hpp"
#include "../../component/spatial/SpatialComp.hpp"
#include "../../event/Event.hpp"
#include "../ASystem.hpp"

namespace kln {
    class ENGINE_API UISystem : public ASystem {
      public:
        UISystem();
        virtual ~UISystem() = default;

        void update(std::shared_ptr<Scene> &scene) override;
    };
} // namespace kln

#endif /* !UISYSTEM_HPP_ */
