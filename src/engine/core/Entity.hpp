#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <memory>
#include <vector>

#include "../EngineApi.hpp"
#include "../interface/IComponent.hpp"

namespace ge {
#define MAX_ENTITIES 10000
#define FIRST_ENTITY_ID 10000

    class ENGINE_API Entity {
      public:
        Entity() = default;
        Entity(std::string name);
        Entity(uint32_t id, std::string name);
        ~Entity() = default;
        Entity(const Entity &other);

        // getters
        std::string getName();
        uint32_t getId();
        std::vector<std::shared_ptr<IComponent>> &getPtrComps();
        std::shared_ptr<IComponent> &getComp(std::string name);

        bool hasComp(std::string name);
        bool hasComps(std::vector<std::string> names);

        void setId(uint32_t id);
        void addComp(std::shared_ptr<IComponent> newComp);

      private:
        std::string _name = "Default";
        uint32_t _id = 0;
        std::vector<std::shared_ptr<IComponent>> _comps;

#define ENTITY_TAG "[ENTITY " << _id << "] "
    };

    uint32_t getAvailableId(std::vector<std::shared_ptr<Entity>> &entities);
} // namespace ge

#endif