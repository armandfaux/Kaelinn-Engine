#include <engine/core/Game.hpp>
#include <engine/system/render/RenderSystem.hpp>
#include <engine/system/input/InputSystem.hpp>
#include <engine/system/physic/PhysicSystem.hpp>
#include <engine/system/scene/SceneSystem.hpp>

int main(int argc, char** argv) {

    kln::Game game;

    std::shared_ptr<kln::RenderSystem> renderS = std::make_shared<kln::RenderSystem>("Simulation", 1000, 800, 32, "Fullscreen");
    std::shared_ptr<kln::PhysicSystem> physicS = std::make_shared<kln::PhysicSystem>();

    game.createScene("Main Scene");

    return 0;
}