#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../../EngineApi.hpp"
#include "../../event/Event.hpp"
#include "../../event/Publisher.hpp"
#include "../../event/Subscriber.hpp"
#include "../ASystem.hpp"

namespace kln {
    class ENGINE_API InputSystem : public ASystem {
      public:
        InputSystem(std::shared_ptr<sf::RenderWindow> window);
        virtual ~InputSystem() = default;

        void update(std::shared_ptr<Scene> &scene) override;
        void subscribe(std::shared_ptr<Subscriber> subscriber);

      private:
        Publisher _publisher;
        std::shared_ptr<sf::RenderWindow> _window;
        std::vector<Key> _pressedKeys;
    };
} // namespace kln

#endif /* !INPUTSYSTEM_HPP_ */
