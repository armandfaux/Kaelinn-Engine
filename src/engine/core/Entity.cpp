#include "Entity.hpp"

namespace kln {
    uint32_t getAvailableId(std::vector<std::shared_ptr<Entity>> &entities) {
        uint32_t id = FIRST_ENTITY_ID * 2;

        for (auto &entity : entities) {
            if (id == entity->getId()) {
                id++;
            }
        }

        return id;
    }

    Entity::Entity(std::string name) { _name = name; }

    Entity::Entity(uint32_t id, std::string name) {
        _id = id;
        _name = name;
    }

    Entity::Entity(const Entity &other) : _name(other._name), _id(other._id) {
        // Copy components
        for (const auto &comp : other._comps) {
            _comps.push_back(comp->clone());
        }
    }

    // getters
    uint32_t Entity::getId() { return _id; }

    std::string Entity::getName() { return _name; }

    std::vector<std::shared_ptr<IComponent>> &Entity::getPtrComps() { return _comps; }

    std::shared_ptr<IComponent> &Entity::getComp(std::string name) {
        for (auto &comp : _comps) {
            if (comp->getName() == name) {
                return comp;
            }
        }

        // TODO throw an exception
        // std::string exceptionName = ENTITY_TAG << "The component " <<
        // name.c_str()
        // << " doesn't exist in this entity\n";
        throw std::runtime_error("Component " + name + " doesn't exist in this entity\n");
    }

    // returns true if the Entity owns a component with the given name, false
    // otherwise
    bool Entity::hasComp(std::string name) {
        for (auto &comp : _comps) {
            if (comp->getName() == name) {
                return true;
            }
        }
        return false;
    }

    bool Entity::hasComps(std::vector<std::string> names) {
        uint32_t count = 0;

        for (auto &comp : _comps) {
            for (auto &name : names) {
                if (comp->getName() == name) {
                    count++;
                }
            }
        }
        return (count == names.size());
    }

    void Entity::setId(uint32_t id) { _id = id; }

    void Entity::addComp(std::shared_ptr<IComponent> newComp) { _comps.push_back(newComp); }
} // namespace kln
