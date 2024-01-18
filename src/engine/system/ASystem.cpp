#include "ASystem.hpp"

using namespace ge;

ASystem::ASystem() { _subscriber = std::make_shared<Subscriber>(*this); }

// getters
std::string ASystem::getName() { return _name; }

SystemType ASystem::getType() { return _systemType; }

std::shared_ptr<Subscriber> ASystem::getSubscriber() { return _subscriber; }

Publisher ASystem::getPublisher() { return _publisher; }

uint32_t ASystem::getEventCount() { return _eventQueue.size(); }

void ASystem::addEvent(Event &event) { _eventQueue.push_back(event); }

void ASystem::subscribe(std::shared_ptr<Subscriber> subscriber) { _publisher.subscribe(subscriber); }

void ASystem::clearEventQueue() { _eventQueue.clear(); }

ASystem::~ASystem() {}
