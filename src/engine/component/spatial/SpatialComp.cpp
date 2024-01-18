#include "SpatialComp.hpp"

using namespace ge;

SpatialComp::SpatialComp() {
    _name = "Spatial";
    _position = Vector2(0, 0);
}

SpatialComp::SpatialComp(Vector2 pos) {
    _name = "Spatial";
    _position = pos;
}

// getters
Vector2 SpatialComp::getPos() { return _position; }

void SpatialComp::setPos(Vector2 newPos) { _position = newPos; }

std::shared_ptr<IComponent> SpatialComp::clone() { return std::make_shared<SpatialComp>(_position); }
