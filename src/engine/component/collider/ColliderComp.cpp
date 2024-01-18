#include "ColliderComp.hpp"

using namespace ge;

ColliderComp::ColliderComp(Vector2 bounds) {
    _bounds = bounds;
    _name = "Collider";
}

ColliderComp::ColliderComp(Vector2 bounds, Vector2 offset) {
    _bounds = bounds;
    _offset = offset;
    _name = "Collider";
}

ColliderComp::ColliderComp(Vector2 bounds, bool solid) {
    _bounds = bounds;
    _solid = solid;
    _name = "Collider";
}

ColliderComp::ColliderComp(Vector2 bounds, Vector2 offset, bool solid) {
    _bounds = bounds;
    _offset = offset;
    _solid = solid;
    _name = "Collider";
}

Vector2 ColliderComp::getBounds() { return _bounds; }

Vector2 ColliderComp::getOffset() { return _offset; }

bool ColliderComp::isSolid() { return _solid; }

bool ColliderComp::isCollidingWith(uint32_t id) {
    auto it = std::find(_collidingEntities.begin(), _collidingEntities.end(), id);

    return it != _collidingEntities.end();
}

void ColliderComp::addCollidingEntity(uint32_t id) {
    if (!isCollidingWith(id)) {
        _collidingEntities.push_back(id);
    }
}

void ColliderComp::rmCollidingEntity(uint32_t id) {
    auto it = std::find(_collidingEntities.begin(), _collidingEntities.end(), id);

    if (it != _collidingEntities.end()) {
        _collidingEntities.erase(it);
    }
}

std::shared_ptr<IComponent> ColliderComp::clone() { return std::make_shared<ColliderComp>(_bounds, _offset, _solid); }

ColliderComp::~ColliderComp() {}
