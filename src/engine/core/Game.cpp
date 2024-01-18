#include "Game.hpp"

using namespace ge;

// ctors
Game::Game() {
    _name = "New Game";
    _isRunning = false;
    std::cout << "[ENGINE] New Game created\n";
}

Game::Game(std::string name) {
    _name = name;
    _isRunning = false;
    std::cout << "[ENGINE] " << name << " created\n";
    std::cout << "...\n";
}

Game::Game(std::string name, SystemType type) {
    _name = name;
    _isRunning = false;
    _type = type;
    std::cout << "[ENGINE] " << name << " created\n";
    std::cout << "...\n";
}

// getters
std::string Game::getName() { return _name; }

std::vector<std::shared_ptr<Scene>> &Game::getScenes() { return _scenes; }

std::shared_ptr<Scene> &Game::getSceneById(uint32_t id) {
    for (auto &scene : _scenes) {
        if (scene->getId() == id) {
            return scene;
        }
    }
    throw std::runtime_error("No scene found by id");
}

std::shared_ptr<Scene> &Game::getSceneByName(std::string name) {
    for (auto &scene : _scenes) {
        if (scene->getName() == name) {
            return scene;
        }
    }
    throw std::runtime_error("No scene found by name");
}

std::vector<std::shared_ptr<Entity>> &Game::getPrefabs() { return _prefabs; }

bool Game::isRunning() { return _isRunning; }

bool ge::Game::sceneExists(uint32_t sceneId) {
    auto it =
        std::find_if(_scenes.begin(), _scenes.end(), [&](const auto &scene) { return scene->getId() == sceneId; });

    return it != _scenes.end();
}

bool ge::Game::sceneExists(std::string sceneName) {
    auto it =
        std::find_if(_scenes.begin(), _scenes.end(), [&](const auto &scene) { return scene->getName() == sceneName; });

    return it != _scenes.end();
}

// Setters
void Game::setStatus(bool running) { _isRunning = running; }

void Game::setName(std::string name) { _name = name; }

void Game::setActiveScene(uint32_t sceneId) {
    // Clients can run only 1 scene at once
    if (sceneExists(sceneId)) {
        if (_type == SystemType::client) {
            for (auto &scene : _scenes) {
                scene->setActive(false);
            }
        }

        getSceneById(sceneId)->setActive(true);
        std::cout << "[GAME] Switching to scene " << sceneId << "\n";
    } else {
        std::cout << "[GAME] SetActiveScene(" << sceneId << ") - No such scene found\n";
    }
}

void Game::setActiveScene(std::string sceneName) {
    // Clients can run only 1 scene at once
    if (_type == SystemType::client) {
        for (auto &scene : _scenes) {
            scene->setActive(false);
        }
    }

    if (sceneExists(sceneName)) {
        getSceneByName(sceneName)->setActive(true);
        std::cout << "[GAME] Switching to scene " << sceneName << "\n";
    } else {
        std::cout << "[GAME] SetActiveScene(" << sceneName << ") - No such scene found\n";
    }
}

void Game::run() {
    _isRunning = true;

    // Game loop
    while (_isRunning) {
        // Start the deltatime clock
        auto frameStartTime = std::chrono::high_resolution_clock::now();

        // Run the game systems on every active scene
        for (auto &system : _systems) {
            for (auto &scene : _scenes) {
                if (scene->isActive()) {
                    system->update(scene);
                }
            }
            system->clearEventQueue();
        }

        // Measure & set the deltatime
        auto frameEndTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(frameEndTime - frameStartTime).count();
    }
}

// scene management
uint32_t Game::createScene() {
    // create a scene with the closest available default name ("New Scene", "New
    // Scene (1)", "New Scene (2)", etc...)
    std::string defaultName = "New Scene";
    uint32_t id = 1;
    uint32_t copyIndex = 0;

    for (auto &scene : _scenes) {
        if (scene->getId() == id) {
            if (++id > 99) { // Id max reached
                std::cout << "[GAME] Failed to create the scene \"" << defaultName
                          << "\": maximum amount of scenes reached\n";
                return 0;
            }
        }
        if (scene->getName() == defaultName) {
            defaultName = "New Scene (" + std::to_string(++copyIndex) + ")";
        }
    }
    _scenes.push_back(std::make_shared<Scene>(id, defaultName));

    std::cout << "[" << _name << "] Scene \"" << defaultName << "\" succesfully created with id " << id << "\n";
    return id;
}

uint32_t Game::createScene(std::string name) {
    std::string newName = name;
    uint32_t id = 1;
    uint32_t copyIndex = 0;

    // check if such scene already exists
    for (auto &scene : _scenes) {
        if (scene->getId() == id) {
            if (++id > 99) { // Id max reached
                std::cout << "[" << _name << "] Failed to create the scene \"" << newName
                          << "\": maximum amount of scenes reached\n";
                return 0;
            }
        }
        if (scene->getName() == newName) {
            newName = name + " (" + std::to_string(++copyIndex) + ")";
        }
    }
    _scenes.push_back(std::make_shared<Scene>(id, newName));

    std::cout << "[GAME] Scene \"" << newName << "\" succesfully created with id " << id << "\n";
    return id;
}

void Game::duplicateScene(uint32_t sceneId) {
    // Find the scene to duplicate
    auto it = std::find_if(_scenes.begin(), _scenes.end(),
                           [sceneId](const auto &scene) { return scene->getId() == sceneId; });

    if (it != _scenes.end()) {
        std::cout << "[GAME] Duplicating scene: " << (*it)->getName() << "\n";
        std::shared_ptr<Scene> originalScene = *it;

        // Create a new scene by copying the original using the copy constructor
        std::shared_ptr<Scene> newScene = std::make_shared<Scene>(*originalScene);

        // Generate a unique name for the duplicated scene
        std::string newName = newScene->getName();
        uint32_t id = 1;
        uint32_t copyIndex = 0;

        auto isDuplicate = [&](const auto &scene) { return scene->getId() == id || scene->getName() == newName; };

        // Check if the generated id or name already exists
        while (std::any_of(_scenes.begin(), _scenes.end(), isDuplicate)) {
            if (++id > 99) { // Id max reached
                std::cout << "[" << _name << "] Failed to create the scene \"" << newName
                          << "\": maximum amount of scenes reached\n";
                return;
            }

            newName = newScene->getName() + " (" + std::to_string(++copyIndex) + ")";
        }

        // Set the new name and id for the duplicated scene
        newScene->setName(newName);
        newScene->setId(id);

        std::cout << "[GAME] Scene \"" << newName << "\" successfully created with id " << id << "\n";

        // Add the duplicated scene to the scenes vector
        _scenes.push_back(newScene);
    } else {
        std::cout << "[GAME] Scene with id " << sceneId << " not found for duplication\n";
    }
}

void Game::rmSceneById(uint32_t sceneId) {
    auto it =
        std::remove_if(_scenes.begin(), _scenes.end(), [&](const auto &scene) { return scene->getId() == sceneId; });

    if (it != _scenes.end()) {
        _scenes.erase(it, _scenes.end());
        std::cout << "[GAME] Scene with ID " << sceneId << " removed successfully\n";
    } else {
        std::cout << "[GAME] Scene with ID " << sceneId << " not found\n";
    }
}

void Game::addSystem(std::shared_ptr<ISystem> system) { _systems.push_back(system); }

void Game::addPrefab(std::shared_ptr<Entity> prefab) { _prefabs.push_back(prefab); }

// dtor
Game::~Game() {}
