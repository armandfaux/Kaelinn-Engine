#include "SpatialComp.hpp"

using namespace kln;

SpatialComp::SpatialComp(Vector2 pos = {0, 0}) {
    _type = CompType::SPATIAL;
    _position = pos;
}

// getters
Vector2 SpatialComp::getPos()
{
    return _position;
}

void SpatialComp::setPos(Vector2 newPos)
{
    _position = newPos;
}

std::shared_ptr<IComponent> SpatialComp::clone()
{
    return std::make_shared<SpatialComp>(_position);
}
