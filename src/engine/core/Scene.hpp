#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../EngineApi.hpp"
#include "../component/input/InputComp.hpp"
#include "../event/Event.hpp"
#include "../math/Utils.hpp"
#include "../math/Vector2.hpp"
#include "Entity.hpp"

namespace kln {
#define MAX_ENTITIES 10000
#define FIRST_ENTITY_ID 10000

    class ENGINE_API Scene {
      public:
        Scene(uint32_t id, std::string name);
        Scene(const Scene &other);
        ~Scene();

        // getters
        uint32_t getId();
        std::string getName();
        std::vector<std::shared_ptr<Entity>> &getEntities();
        std::shared_ptr<Entity> &getEntityById(uint32_t);
        bool isActive();

        void setActive(bool status);

        // setters
        void setId(uint32_t id);
        void setName(std::string name);

        // entity & prefab management
        std::shared_ptr<Entity> createEntity(std::string name);
        std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity);
        std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity, Event &event);
        void rmEntityById(uint32_t id);

      private:
        bool _active = false;

        uint32_t _id;
        std::string _name;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::unordered_set<uint32_t> _entityIds;
    };
} // namespace kln

#endif