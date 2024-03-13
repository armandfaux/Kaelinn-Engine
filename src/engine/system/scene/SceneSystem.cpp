#include "SceneSystem.hpp"

using namespace kln;

SceneSystem::SceneSystem(Game& parent) : _parent(parent)
{
}

void SceneSystem::update(std::shared_ptr<Scene> &scene) {
    for (auto &event : _eventQueue) {
        switch (event.type) {
        case Type::switchScene:
            _parent.setActiveScene(event.sceneId);
            break;

        case Type::newEntity:
            for (auto &prefab : _parent.getPrefabs()) {
                if (prefab->getName() == event.prefabName) {
                    if (event.entityId1 == 0) {
                        event.entityId1 = getAvailableId(scene->getEntities());
                    }

                    _parent.getSceneById(event.sceneId)->instantiate(prefab, event);
                }
            }
            break;

        case Type::delEntity:
            _parent.getSceneById(event.sceneId)->rmEntityById(event.entityId1);
            break;

        case Type::newScene:
            _parent.duplicateScene(event.sceneId);
            break;

        case Type::delScene:
            _parent.rmSceneById(event.sceneId);
            break;

        case Type::exit:
            std::cout << "[ENGINE] Exit event received\n";
            _parent.setStatus(false);
            break;

        default:
            break;
        }
    }
    _eventQueue.clear();
}
