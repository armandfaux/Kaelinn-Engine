#include "ButtonComp.hpp"

using namespace kln;

ButtonComp::ButtonComp(std::vector<Event> events) {
    _type = CompType::BUTTON;
    _events = events;
}

// getter
std::vector<Event> &ButtonComp::getEvents() { return _events; }

// setter
void ButtonComp::setEvents(std::vector<Event> events) { _events = events; }

std::shared_ptr<IComponent> ButtonComp::clone() { return std::make_shared<ButtonComp>(_events); }