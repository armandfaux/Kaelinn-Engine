#include "AComponent.hpp"

using namespace kln;

AComponent::AComponent() {}

CompType AComponent::getType()
{
    return _type;
}

AComponent::~AComponent() {}
