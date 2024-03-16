#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include <cstddef>
#include <cstdint>

#include "../EngineApi.hpp"
#include "../interface/IComponent.hpp"

namespace kln {
    class ENGINE_API AComponent : public IComponent {
      public:
        AComponent();
        ~AComponent();

        // getters
        CompType getType() override;

      protected:
        uint32_t _id;
        CompType _type;
    };
} // namespace kln

#endif /* !ACOMPONENT_HPP_ */
