#ifndef BUTTONCOMP_HPP_
#define BUTTONCOMP_HPP_

#include "../../EngineApi.hpp"
#include "../../event/Event.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace ge {
    class ENGINE_API ButtonComp : public AComponent {
      public:
        ButtonComp(std::vector<Event> events);
        ButtonComp(const ButtonComp &buttonComp) = default;

        ~ButtonComp() = default;

        std::vector<Event> &getEvents();

        // setter
        void setEvents(std::vector<Event> events);
        void setEvent(Event event);
        std::shared_ptr<IComponent> clone() override;

      private:
        std::vector<Event> _events;
    };
} // namespace ge

#endif /* !BUTTONCOMP_HPP_ */
