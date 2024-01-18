#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

#include <memory>

#include "../core/Scene.hpp"
#include "../event/Event.hpp"
#include "../event/Publisher.hpp"
#include "../event/Subscriber.hpp"

namespace ge {
    class Publisher;
    class Subscriber;

    enum SystemType {
        client,
        server,
    };

    class ISystem {
      public:
        // getters
        virtual SystemType getType() = 0;
        virtual std::string getName() = 0;
        virtual std::shared_ptr<Subscriber> getSubscriber() = 0;
        virtual uint32_t getEventCount() = 0;
        virtual Publisher getPublisher() = 0;

        virtual void update(std::shared_ptr<Scene> &scene) = 0;
        virtual void subscribe(std::shared_ptr<Subscriber>) = 0;
        virtual void addEvent(Event &) = 0;
        virtual void clearEventQueue() = 0;
    };
} // namespace ge

#endif