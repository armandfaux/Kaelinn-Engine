#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include <iostream>
#include <vector>

#include "../EngineApi.hpp"
#include "../event/Event.hpp"
#include "../event/Publisher.hpp"
#include "../event/Subscriber.hpp"
#include "../interface/ISystem.hpp"

namespace kln {
    class ENGINE_API ASystem : public ISystem {
      public:
        ASystem();
        ~ASystem();

        // getters
        std::string getName() override;
        SystemType getType() override;
        std::shared_ptr<Subscriber> getSubscriber() override;
        Publisher getPublisher() override;
        uint32_t getEventCount() override;

        void addEvent(Event &event) override;
        void subscribe(std::shared_ptr<Subscriber>) override;
        void clearEventQueue() override;

      protected:
        std::string _name;
        SystemType _systemType;

        // Event bus
        std::vector<Event> _eventQueue;
        std::shared_ptr<Subscriber> _subscriber;
        Publisher _publisher;
    };
} // namespace kln

#endif /* !ASYSTEM_HPP_ */
