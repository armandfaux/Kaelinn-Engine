#ifndef PUBLISHER_HPP_
#define PUBLISHER_HPP_

#include <memory>
#include <vector>

#include "../EngineApi.hpp"
#include "Event.hpp"
#include "Subscriber.hpp"

namespace kln {
    class Subscriber;

    class ENGINE_API Publisher {
      public:
        Publisher();
        ~Publisher();

        void publish(Event event);
        void subscribe(std::shared_ptr<Subscriber> subscriber);

      private:
        std::vector<std::shared_ptr<Subscriber>> _subscribers;
    };
} // namespace kln

#endif /* !PUBLISHER_HPP_ */
