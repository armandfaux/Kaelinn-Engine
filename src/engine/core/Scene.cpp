#include "Scene.hpp"

//////////// TO BE REMOVED //////////////////////
#include "../component/button/ButtonComp.hpp"
#include "../component/spatial/SpatialComp.hpp"
/////////////////////////////////////////////////

using namespace kln;

Scene::Scene(uint32_t id, std::string name) {
    _id = id;
    _name = name;
}

// Scene::Scene(const Scene &other) {
//     _active = other._active;
//     _id = other._id;
//     _name = other._name;
//     _entityIds = other._entityIds;

//     for (auto &entity : other._entities) {
//         _entities.push_back(std::make_shared<Entity>(*entity));
//     }
// }

// getters
uint32_t Scene::getId()
{
    return _id;
}

std::string Scene::getName()
{
    return _name;
}

std::unordered_set<Entity> Scene::getEntities()
{
    return _entities;
}

std::unordered_map<std::string, ComponentMap>& Scene::getAllComps()
{
    return _allComps;
}

ComponentMap& Scene::getComps(std::string type)
{
    return _allComps[type];
}

// NO LONGER REQUIRED
// std::shared_ptr<Entity> &Scene::getEntityById(uint32_t id) {
//     for (auto &entity : _entities) {
//         if (entity->getId() == id) {
//             return entity;
//         }
//     }
//     throw std::runtime_error("No entity found by id");
// }

bool Scene::isActive() { return _active; }


// setters
void Scene::setId(uint32_t id)
{
    _id = id;
}

void Scene::setName(std::string name)
{
    _name = name;
}

void Scene::setActive(bool status)
{
    _active = status;
}

// Entity management
Entity Scene::availableId(Entity id = 0)
{
    return (_entities.find(id) == _entities.end()) ? id : availableId(++id);
}

Entity Scene::newEntity() {
    Entity id = availableId();
    _entities.insert(id);
    return id;
}

void Scene::rmEntity(Entity entity)
{
    _entities.erase(entity);
}

void Scene::addComp(Entity entity, std::shared_ptr<IComponent> comp)
{
    // TODO check if entity doesn't have such comp
    _allComps[comp->getName()][entity] = comp;
    // TODO + edit signature
}

void Scene::rmComp(Entity entity, std::string type)
{
    _allComps[type].erase(entity);
}

// std::shared_ptr<Entity> Scene::instantiate(std::shared_ptr<Entity> &prefab) {
//     std::shared_ptr<Entity> entity = std::make_shared<Entity>(*prefab);
//     uint32_t id = getAvailableId(_entityIds, FIRST_ENTITY_ID, FIRST_ENTITY_ID + MAX_ENTITIES - 1);

//     if (id) {
//         entity->setId(id);
//         _entityIds.insert(id);
//         _entities.push_back(entity);
//         // std::cout << "[SCENE " << _name << "] Prefab " << entity->getName()
//         // << " successfully instantiated with id " << id << "\n";
//     } else {
//         std::cout << "[SCENE] Maximum amount of entities reached in scene\n";
//         throw std::runtime_error("Maximum amount of entities reached in scene\n");
//     }
//     return entity;
// }

// // create a copy of the given prefab in the scene
// std::shared_ptr<Entity> Scene::instantiate(std::shared_ptr<Entity> &prefab, Event &event) {
//     std::shared_ptr<Entity> entity = std::make_shared<Entity>(*prefab);

//     // Do not instanciate if an entity already has this ID
//     for (auto &entity : _entities) {
//         if (entity->getId() == event.entityId1) {
//             return entity;
//         }
//     }

//     entity->setId(event.entityId1);

//     if (entity->hasComp("Spatial")) {
//         SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
//         if (event.pos != Vector2()) {
//             spatialComp->setPos(event.pos);
//         }
//     }

//     if (entity->hasComp("Input")) {
//         InputComp *inputComp = dynamic_cast<InputComp *>(entity->getComp("Input").get());
//         inputComp->setClientId(event.clientId);
//     }

//     _entityIds.insert(event.entityId1);
//     _entities.push_back(entity);
//     // std::cout << "[SCENE " << _name << "] Prefab " << entity->getName() << "
//     // successfully instantiated with id " << event.entityId1 << "\n";
//     return entity;
// }

Scene::~Scene() {}