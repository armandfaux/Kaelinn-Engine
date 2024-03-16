#include "ColliderComp.hpp"

using namespace kln;

ColliderComp::ColliderComp(Vector2 bounds = {0, 0}, Vector2 offset = {0, 0}, bool solid = false) {
    _type = CompType::COLLIDER;

    _bounds = bounds;
    _offset = offset;
    _solid = solid;
}

// ColliderComp::ColliderComp(Vector2 bounds) {
//     _bounds = bounds;
//     _type = "Collider";
// }

// ColliderComp::ColliderComp(Vector2 bounds, Vector2 offset) {
//     _bounds = bounds;
//     _offset = offset;
//     _type = "Collider";
// }

// ColliderComp::ColliderComp(Vector2 bounds, bool solid) {
//     _bounds = bounds;
//     _solid = solid;
//     _type = "Collider";
// }

Vector2 ColliderComp::getBounds() { return _bounds; }

Vector2 ColliderComp::getOffset() { return _offset; }

bool ColliderComp::isSolid() { return _solid; }

bool ColliderComp::isCollidingWith(Entity entity) {
    auto it = std::find(_collidingEntities.begin(), _collidingEntities.end(), entity);

    return it != _collidingEntities.end();
}

void ColliderComp::addCollidingEntity(Entity entity) {
    if (!isCollidingWith(entity)) {
        _collidingEntities.push_back(entity);
    }
}

void ColliderComp::rmCollidingEntity(Entity entity) {
    auto it = std::find(_collidingEntities.begin(), _collidingEntities.end(), entity);

    if (it != _collidingEntities.end()) {
        _collidingEntities.erase(it);
    }
}

std::shared_ptr<IComponent> ColliderComp::clone() { return std::make_shared<ColliderComp>(_bounds, _offset, _solid); }

ColliderComp::~ColliderComp() {}
