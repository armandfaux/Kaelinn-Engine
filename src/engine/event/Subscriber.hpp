#ifndef SUBSCRIBER_HPP_
#define SUBSCRIBER_HPP_

#include "../EngineApi.hpp"
#include "../interface/ISystem.hpp"
#include "Event.hpp"

namespace ge {
    class ISystem;

    class ENGINE_API Subscriber {
      public:
        Subscriber(ISystem &parent);
        ~Subscriber();

        void onEvent(Event &event);

      private:
        ISystem &_parent;
    };
} // namespace ge

#endif /* !SUBSCRIBER_HPP_ */
