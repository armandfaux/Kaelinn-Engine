#include "AComponent.hpp"

using namespace kln;

AComponent::AComponent() {}

uint32_t AComponent::getId() { return _id; }

std::string AComponent::getName() { return _name; }

AComponent::~AComponent() {}
