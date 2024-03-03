#include "Subscriber.hpp"

#include <iostream>

using namespace kln;

Subscriber::Subscriber(ISystem &parent) : _parent(parent) {}

void Subscriber::onEvent(Event &event) { _parent.addEvent(event); }

Subscriber::~Subscriber() {}
