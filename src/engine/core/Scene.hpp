#ifndef SCENE_HPP
#define SCENE_HPP

#include <bitset>
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
    using Signature = std::bitset<CompType::COUNT>;

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
            std::unordered_set<Entity> getEntitiesWithSignature(Signature);
            Signature getSignature(Entity);
            std::unordered_map<CompType, ComponentMap>& getAllComps();
            ComponentMap& getComps(CompType);
            std::shared_ptr<IComponent>& getComp(Entity, CompType);
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
            void rmComp(Entity, CompType);

            // PREFAB SYSTEM DISABLED FOR NOW
            // std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity);
            // std::shared_ptr<Entity> instantiate(std::shared_ptr<Entity> &entity, Event &event);

        private:
            uint32_t _id;
            std::string _name;
            bool _active = false;

            std::unordered_set<Entity> _entities;
            std::unordered_map<Entity, Signature> _signatures;
            std::unordered_map<CompType, ComponentMap> _allComps;
    };
} // namespace kln

#endif