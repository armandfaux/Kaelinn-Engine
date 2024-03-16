#include "InputComp.hpp"

using namespace kln;

// STOCK ID CLIENT
//  CHeck mov id comp id event

InputComp::InputComp() {
    _type = CompType::INPUT;
    _clientId = 0;
}

void InputComp::setClientId(uint32_t id) { _clientId = id; }

uint32_t InputComp::getClientId() { return _clientId; }

std::shared_ptr<IComponent> InputComp::clone() { return std::make_shared<InputComp>(); }
