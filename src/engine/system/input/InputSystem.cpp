#include "InputSystem.hpp"

using namespace kln;

InputSystem::InputSystem(std::shared_ptr<sf::RenderWindow> window) {
    _window = window;
    std::cout << "[SYSTEM] Input System successfully created\n";
}

Key toGeKey(sf::Mouse::Button mouseButton) {
    switch (mouseButton) {
    case sf::Mouse::Left:
        return Key::MouseLeft;
    case sf::Mouse::Right:
        return Key::MouseRight;
    case sf::Mouse::Middle:
        return Key::MouseMiddle;
    case sf::Mouse::XButton1:
        return Key::MouseXButton1;
    case sf::Mouse::XButton2:
        return Key::MouseXButton2;
    default:
        return Key::Unknown;
    }
}

Key toGeKey(sf::Keyboard::Key key) {
    return (key == sf::Keyboard::A       ? Key::A
            : key == sf::Keyboard::B     ? Key::B
            : key == sf::Keyboard::C     ? Key::C
            : key == sf::Keyboard::D     ? Key::D
            : key == sf::Keyboard::E     ? Key::E
            : key == sf::Keyboard::F     ? Key::F
            : key == sf::Keyboard::G     ? Key::G
            : key == sf::Keyboard::H     ? Key::H
            : key == sf::Keyboard::I     ? Key::I
            : key == sf::Keyboard::J     ? Key::J
            : key == sf::Keyboard::K     ? Key::K
            : key == sf::Keyboard::L     ? Key::L
            : key == sf::Keyboard::M     ? Key::M
            : key == sf::Keyboard::N     ? Key::N
            : key == sf::Keyboard::O     ? Key::O
            : key == sf::Keyboard::P     ? Key::P
            : key == sf::Keyboard::Q     ? Key::Q
            : key == sf::Keyboard::R     ? Key::R
            : key == sf::Keyboard::S     ? Key::S
            : key == sf::Keyboard::T     ? Key::T
            : key == sf::Keyboard::U     ? Key::U
            : key == sf::Keyboard::V     ? Key::V
            : key == sf::Keyboard::W     ? Key::W
            : key == sf::Keyboard::X     ? Key::X
            : key == sf::Keyboard::Y     ? Key::Y
            : key == sf::Keyboard::Z     ? Key::Z
            : key == sf::Keyboard::Space ? Key::Space
            : key == sf::Keyboard::Enter ? Key::Enter
            : key == sf::Keyboard::Num0  ? Key::Num0
            : key == sf::Keyboard::Num1  ? Key::Num1
            : key == sf::Keyboard::Num2  ? Key::Num2
            : key == sf::Keyboard::Num3  ? Key::Num3
            : key == sf::Keyboard::Num4  ? Key::Num4
            : key == sf::Keyboard::Num5  ? Key::Num5
            : key == sf::Keyboard::Num6  ? Key::Num6
            : key == sf::Keyboard::Num7  ? Key::Num7
            : key == sf::Keyboard::Num8  ? Key::Num8
            : key == sf::Keyboard::Num9  ? Key::Num9
            : key == sf::Keyboard::Left  ? Key::Left
            : key == sf::Keyboard::Right ? Key::Right
            : key == sf::Keyboard::Up    ? Key::Up
            : key == sf::Keyboard::Down  ? Key::Down
                                         : Key::Unknown);
}

void InputSystem::update(std::shared_ptr<Scene> &scene) {
    sf::Event sfEvent;

    while (_window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed || sfEvent.key.code == sf::Keyboard::Escape) {
            _window->close();
        }

        Event geEvent = {
            .type = Type::input,
            .keyPressed = sfEvent.type == sf::Event::KeyPressed || sfEvent.type == sf::Event::MouseButtonPressed,
            .keyReleased = sfEvent.type == sf::Event::KeyReleased || sfEvent.type == sf::Event::MouseButtonReleased,
        };
        if (sfEvent.type == sf::Event::KeyPressed || sfEvent.type == sf::Event::KeyReleased) {
            geEvent.key = toGeKey(sfEvent.key.code);
        } else if (sfEvent.type == sf::Event::MouseButtonPressed || sfEvent.type == sf::Event::MouseButtonReleased) {
            geEvent.key = toGeKey(sfEvent.mouseButton.button);
            geEvent.pos = {static_cast<double>(sfEvent.mouseButton.x), static_cast<double>(sfEvent.mouseButton.y)};
        }

        bool keyFound = false;

        // Check if the key is already pressed
        if (geEvent.keyPressed) {
            for (Key &key : _pressedKeys) {
                if (key == geEvent.key) {
                    keyFound = true;
                }
            }

            // If not, add it to the pressed keys and publish the event
            if (!keyFound) {
                _pressedKeys.push_back(geEvent.key);
                _publisher.publish(geEvent);
            }

            // When the key is released, remove it from the pressed keys
        } else if (geEvent.keyReleased) {
            for (auto it = _pressedKeys.begin(); it != _pressedKeys.end(); it++) {
                if (*it == geEvent.key) {
                    _pressedKeys.erase(it);
                    break;
                }
            }

            _publisher.publish(geEvent);

            // Re-publish the pressed keys to avoid getting stuck when opposite
            // direction keys are pressed
            for (auto &key : _pressedKeys) {
                geEvent.key = key;
                geEvent.keyPressed = true;
                geEvent.keyReleased = false;
                _publisher.publish(geEvent);
            }
        }
    }
}

void InputSystem::subscribe(std::shared_ptr<Subscriber> subscriber) { _publisher.subscribe(subscriber); }
