#include "Publisher.hpp"

#include <iostream> // TODO remove

using namespace ge;

Publisher::Publisher() {}

void Publisher::publish(Event event) {
    for (auto &sub : _subscribers) {
        sub->onEvent(event);
    }
}

void Publisher::subscribe(std::shared_ptr<Subscriber> newSub) { _subscribers.push_back(newSub); }

Publisher::~Publisher() {}
