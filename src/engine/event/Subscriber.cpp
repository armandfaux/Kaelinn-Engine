#include "Subscriber.hpp"

#include <iostream>

using namespace ge;

Subscriber::Subscriber(ISystem &parent) : _parent(parent) {}

void Subscriber::onEvent(Event &event) { _parent.addEvent(event); }

Subscriber::~Subscriber() {}
