#include <engine/core/Game.hpp>
#include <engine/system/render/RenderSystem.hpp>
#include <engine/system/input/InputSystem.hpp>
#include <engine/system/physic/PhysicSystem.hpp>
#include <engine/system/scene/SceneSystem.hpp>
#include <engine/component/spatial/SpatialComp.hpp>
#include <engine/component/sprite/SpriteComp.hpp>

int main(int argc, char** argv) {

    // Core initialisation
    kln::Game game;

    // Systems initialisation
    std::shared_ptr<kln::RenderSystem> renderS = std::make_shared<kln::RenderSystem>("Simulation", 1260, 720, 32, "Default");
    std::shared_ptr<kln::InputSystem> inputS = std::make_shared<kln::InputSystem>(renderS->getWindow());
    std::shared_ptr<kln::PhysicSystem> physicS = std::make_shared<kln::PhysicSystem>();
    std::shared_ptr<kln::SceneSystem> sceneS = std::make_shared<kln::SceneSystem>(game);

    game.addSystem(sceneS);
    game.addSystem(inputS);
    game.addSystem(physicS);
    game.addSystem(renderS);

    // Scene creation
    game.createScene("Main");
    game.setActiveScene("Main");
    std::shared_ptr<kln::Scene> mainScene = game.getSceneByName("Main");

    // Create a simple entity
    std::shared_ptr<kln::Entity> ball = mainScene->createEntity("Ball");
    ball->addComp(std::make_shared<kln::SpatialComp>(kln::Vector2(600, 320)));
    ball->addComp(std::make_shared<kln::SpriteComp>("assets/ball.png", kln::Vector2(80, 80)));

    // Starting game loop
    game.run();

    return 0;
}