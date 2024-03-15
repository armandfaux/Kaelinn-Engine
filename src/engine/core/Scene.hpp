#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "../EngineApi.hpp"
#include "../component/input/InputComp.hpp"
#include "../event/Event.hpp"
#include "../math/Utils.hpp"
#include "../math/Vector2.hpp"
#include "Entity.hpp"

namespace kln
{
    using ComponentMap = std::unordered_map<Entity, std::shared_ptr<IComponent>>;

    class ENGINE_API Scene
    {
        public:
            Scene(uint32_t id, std::string name);
            ~Scene();

            // SCENE COPY DISABLED FOR NOW
            // Scene(const Scene &other);

            // getters
            uint32_t getId();
            std::string getName();
            std::unordered_set<Entity> getEntities();
            // std::unordered_set<Entity> getEntitiesWithSignature({Signature});
            std::unordered_map<std::string, ComponentMap>& getAllComps();
            ComponentMap& getComps(std::string);
            bool isActive();

            // setters
            void setId(uint32_t id);
            void setName(std::string name);
            void setActive(bool status);

            // entity & prefab management
            Entity availableId(Entity);
            Entity newEntity();
            void rmEntity(Entity);

            void addComp(Entity, std::shared_ptr<IComponent>);
            void rmComp(Entity, std::string);

            // PREFAB SYSTEM DISABLED FOR NOW
            // std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity);
            // std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity, Event &event);

        private:
            uint32_t _id;
            std::string _name;
            bool _active = false;

            std::unordered_set<Entity> _entities;
            std::unordered_map<std::string, ComponentMap> _allComps;
    };
} // namespace kln

#endif