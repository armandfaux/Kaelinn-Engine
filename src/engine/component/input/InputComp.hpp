#ifndef INPUTCOMP_HPP_
#define INPUTCOMP_HPP_

#include "../../EngineApi.hpp"
#include "../../event/Event.hpp"
#include "../AComponent.hpp"

namespace kln {
    class ENGINE_API InputComp : public AComponent {
      public:
        InputComp();
        virtual ~InputComp() = default;

        void setClientId(uint32_t id);

        uint32_t getClientId();

        std::shared_ptr<IComponent> clone();

      private:
        uint32_t _clientId;
    };
} // namespace kln
#endif /* !INPUTCOMP_HPP_ */
