#include "UISystem.hpp"

using namespace ge;

UISystem::UISystem() { _name = "UISystem"; }

void UISystem::update(std::shared_ptr<Scene> &scene) {
    std::vector<std::shared_ptr<Entity>> &entities = scene->getEntities();

    for (auto &event : _eventQueue) {
        if (event.type == Type::input && event.keyPressed && event.key == Key::MouseLeft) {
            for (auto &entity : entities) {
                if (entity->hasComp("Button")) {
                    ButtonComp *button = dynamic_cast<ButtonComp *>(entity->getComp("Button").get());
                    SpatialComp *spatial = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
                    BodyComp *body = dynamic_cast<BodyComp *>(entity->getComp("Body").get());

                    if (event.pos.x >= spatial->getPos().x &&
                        event.pos.x <= spatial->getPos().x + body->getBounds().x &&
                        event.pos.y >= spatial->getPos().y &&
                        event.pos.y <= spatial->getPos().y + body->getBounds().y) {
                        for (auto &buttonEvent : button->getEvents()) {
                            _publisher.publish(buttonEvent);
                        }
                    }
                }
            }
        }
    }
}
