#include "PhysicSystem.hpp"

using namespace kln;

PhysicSystem::PhysicSystem() {
    _name = "Physic";
    _systemType = SystemType::server;
    std::cout << "[SYSTEM] Physic System successfully created\n";
}

void PhysicSystem::update(std::shared_ptr<Scene> &scene) {
    std::vector<std::shared_ptr<Entity>> &entities = scene->getEntities();
    checkCollisions(scene);
    resolvePhysics(entities);
}

void PhysicSystem::checkCollisions(std::shared_ptr<Scene> &scene) {
    std::vector<std::shared_ptr<Entity>> &entities = scene->getEntities();

    // Iterate over each entity
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        auto &entity = *it;
        if (!entity->hasComps(std::vector<std::string>{"Spatial", "Body", "Collider"})) {
            continue;
        }

        // Get the first entity components
        SpatialComp *entitySpatial = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
        ColliderComp *entityCollider = dynamic_cast<ColliderComp *>(entity->getComp("Collider").get());

        Vector2 pos1 = entitySpatial->getPos();
        Vector2 bounds1 = entityCollider->getBounds();

        // Iterate over entities that haven't been processed yet
        for (auto otherIt = std::next(it); otherIt != entities.end(); ++otherIt) {
            auto &other = *otherIt;
            if (!other->hasComps(std::vector<std::string>{"Spatial", "Body", "Collider"})) {
                continue;
            }
            if (entity->getId() == other->getId()) {
                continue;
            }

            // Get the second entity components
            SpatialComp *otherSpatial = dynamic_cast<SpatialComp *>(other->getComp("Spatial").get());
            ColliderComp *otherCollider = dynamic_cast<ColliderComp *>(other->getComp("Collider").get());

            Vector2 pos2 = otherSpatial->getPos();
            Vector2 bounds2 = otherCollider->getBounds();

            // Collision detection
            if (pos1.x < pos2.x + bounds2.x && pos1.x + bounds1.x > pos2.x && pos1.y < pos2.y + bounds2.y &&
                pos1.y + bounds1.y > pos2.y) {
                // Entity doesn't collide yet
                if (!entityCollider->isCollidingWith(other->getId())) {
                    entityCollider->addCollidingEntity(other->getId());
                    otherCollider->addCollidingEntity(entity->getId());

                    Event newEvent{
                        .type = Type::collisionEnter,
                        .entityId1 = entity->getId(),
                        .entityId2 = other->getId(),
                        .sceneId = scene->getId(),
                    };
                    _publisher.publish(newEvent);
                }
            } else {
                if (entityCollider->isCollidingWith(other->getId())) {
                    entityCollider->rmCollidingEntity(other->getId());
                    otherCollider->rmCollidingEntity(entity->getId());

                    Event newEvent{
                        .type = Type::collisionExit,
                        .entityId1 = entity->getId(),
                        .entityId2 = other->getId(),
                        .sceneId = scene->getId(),
                    };
                    _publisher.publish(newEvent);
                }
            }
        }
    }
}

void PhysicSystem::resolvePhysics(std::vector<std::shared_ptr<Entity>> &entities) {
    for (auto &entity : entities) {
        if (entity->hasComps(
                std::vector<std::string>{"Body", "Spatial"})) { // TODO component getter optimisation ? Merge
            // hasComp & getComp together
            SpatialComp *spatial = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
            BodyComp *body = dynamic_cast<BodyComp *>(entity->getComp("Body").get());

            Vector2 currentPos = spatial->getPos();
            Vector2 vel = body->getVelocity();

            // Velocity normalisation
            if (vel.x != 0 || vel.y != 0) {
                double magn = std::sqrt(vel.x * vel.x + vel.y * vel.y);
                if (magn != 0 && magn != INFINITY) {
                    vel.x /= magn / std::abs(vel.x);
                    vel.y /= magn / std::abs(vel.y);
                }
            }

            vel.x *= deltaTime;
            vel.y *= deltaTime;

            // Set the new position depending on the velocity IF NO COLLISION
            // FOUND
            Vector2 newPos = currentPos + vel;
            spatial->setPos(newPos);
        }
    }
}
