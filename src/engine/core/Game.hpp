#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "../EngineApi.hpp"
#include "../interface/ISystem.hpp"
#include "../math/Time.hpp"
#include "../system/network/NetworkSystem.hpp"
#include "Scene.hpp"

namespace kln {
#define UPDATE(systems)                                                                                                \
    for (auto &system : systems) {                                                                                     \
        system->update(scene);                                                                                         \
        system->clearEventQueue();                                                                                     \
    }

    class ENGINE_API Game {
      public:
        Game();
        Game(std::string name);
        Game(std::string name, SystemType type);
        ~Game();

        // getters
        std::string getName();
        std::vector<std::shared_ptr<Scene>> &getScenes();
        std::shared_ptr<Scene> &getSceneById(uint32_t id);
        std::shared_ptr<Scene> &getSceneByName(std::string name);
        std::vector<std::shared_ptr<Entity>> &getPrefabs();
        bool isRunning();
        bool sceneExists(uint32_t sceneId);
        bool sceneExists(std::string sceneName);

        // setters
        void setStatus(bool running);
        void setName(std::string name);
        void setActiveScene(uint32_t sceneId);
        void setActiveScene(std::string sceneName);

        uint32_t createScene();
        uint32_t createScene(std::string name);

        void duplicateScene(uint32_t sceneId);
        void rmSceneById(uint32_t sceneId);

        void addSystem(std::shared_ptr<ISystem> system);
        void addPrefab(std::shared_ptr<Entity> prefab);

        void run();

      private:
        SystemType _type = SystemType::client;
        std::string _name;
        std::vector<std::shared_ptr<Scene>> _scenes;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<std::shared_ptr<Entity>> _prefabs;

        bool _isRunning;
    };
} // namespace kln

#endif /* !GAME_HPP_ */
