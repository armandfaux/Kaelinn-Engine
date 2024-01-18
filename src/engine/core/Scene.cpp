#include "Scene.hpp"

//////////// TO BE REMOVED //////////////////////
#include "../component/button/ButtonComp.hpp"
#include "../component/spatial/SpatialComp.hpp"
/////////////////////////////////////////////////

using namespace ge;

Scene::Scene(uint32_t id, std::string name) {
    _id = id;
    _name = name;
}

Scene::Scene(const Scene &other) {
    _active = other._active;
    _id = other._id;
    _name = other._name;
    _entityIds = other._entityIds;

    for (auto &entity : other._entities) {
        _entities.push_back(std::make_shared<Entity>(*entity));
    }
}

// getters
uint32_t Scene::getId() { return _id; }

std::string Scene::getName() { return _name; }

std::vector<std::shared_ptr<Entity>> &Scene::getEntities() { return _entities; }

std::shared_ptr<Entity> &Scene::getEntityById(uint32_t id) {
    for (auto &entity : _entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    throw std::runtime_error("No entity found by id");
}

bool Scene::isActive() { return _active; }

void Scene::setActive(bool status) { _active = status; }

// setters
void Scene::setId(uint32_t id) { _id = id; }

void Scene::setName(std::string name) { _name = name; }

// entity management
std::shared_ptr<Entity> Scene::createEntity(std::string name) {
    uint32_t id = getAvailableId(_entityIds, FIRST_ENTITY_ID, FIRST_ENTITY_ID + MAX_ENTITIES - 1);

    if (id) {
        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(id, name);
        _entityIds.insert(id);
        _entities.push_back(newEntity);
        // std::cout << "[SCENE " << _name << "] Entity " << name << "
        // successfully created with id " << id << "\n";
        return newEntity;
    } else {
        std::cout << "[SCENE] Maximum amount of entities reached in scene\n";
        throw std::runtime_error("Maximum amount of entities reached in scene\n");
    }
}

std::shared_ptr<Entity> Scene::instantiate(std::shared_ptr<Entity> &prefab) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(*prefab);
    uint32_t id = getAvailableId(_entityIds, FIRST_ENTITY_ID, FIRST_ENTITY_ID + MAX_ENTITIES - 1);

    if (id) {
        entity->setId(id);
        _entityIds.insert(id);
        _entities.push_back(entity);
        // std::cout << "[SCENE " << _name << "] Prefab " << entity->getName()
        // << " successfully instantiated with id " << id << "\n";
    } else {
        std::cout << "[SCENE] Maximum amount of entities reached in scene\n";
        throw std::runtime_error("Maximum amount of entities reached in scene\n");
    }
    return entity;
}

// create a copy of the given prefab in the scene
std::shared_ptr<Entity> Scene::instantiate(std::shared_ptr<Entity> &prefab, Event &event) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(*prefab);

    // Do not instanciate if an entity already has this ID
    for (auto &entity : _entities) {
        if (entity->getId() == event.entityId1) {
            return entity;
        }
    }

    entity->setId(event.entityId1);

    if (entity->hasComp("Spatial")) {
        SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
        if (event.pos != Vector2()) {
            spatialComp->setPos(event.pos);
        }
    }

    if (entity->hasComp("Input")) {
        InputComp *inputComp = dynamic_cast<InputComp *>(entity->getComp("Input").get());
        inputComp->setClientId(event.clientId);
    }

    _entityIds.insert(event.entityId1);
    _entities.push_back(entity);
    // std::cout << "[SCENE " << _name << "] Prefab " << entity->getName() << "
    // successfully instantiated with id " << event.entityId1 << "\n";
    return entity;
}

void Scene::rmEntityById(uint32_t id) {
    auto it =
        std::find_if(_entities.begin(), _entities.end(), [id](const auto &entity) { return entity->getId() == id; });

    // If the entity is found, erase it from the vector and remove its id from
    // the set
    if (it != _entities.end()) {
        _entityIds.erase(id);
        _entities.erase(it);
    }
}

Scene::~Scene() {}