#include <catch2/catch_test_macros.hpp>
#include <set>
#include <vector>

#include <engine/core/Game.hpp>
#include <engine/core/Scene.hpp>

TEST_CASE("Game", "[ctors]") {
  ge::Game A;
  ge::Game B("R-Test");

  REQUIRE((A.getName() == "New Game"));
  REQUIRE((B.getName() == "R-Test"));
}

TEST_CASE("Game", "[scene management]") {
  ge::Game game("R-Test");

  REQUIRE(!game.isRunning());
  REQUIRE(game.getName() == "R-Test");

  std::vector<uint32_t> idSet;
  std::shared_ptr<ge::Scene> sceneA = game.getSceneById(game.createScene());
  std::shared_ptr<ge::Scene> sceneB = game.getSceneById(game.createScene());
  std::shared_ptr<ge::Scene> sceneC = game.getSceneById(game.createScene());
  std::shared_ptr<ge::Scene> sceneD =
      game.getSceneById(game.createScene("Menu Scene"));
  std::shared_ptr<ge::Scene> sceneE =
      game.getSceneById(game.createScene("Menu Scene"));
  std::shared_ptr<ge::Scene> sceneF =
      game.getSceneById(game.createScene("Menu Scene"));

  for (auto scene : game.getScenes()) {
    idSet.push_back(scene->getId());
  }
  std::set idSetUnique(idSet.begin(), idSet.end());

  REQUIRE((idSetUnique.size() == idSet.size()));
  REQUIRE((sceneB->getName() == "New Scene (1)"));
  REQUIRE((sceneC->getName() == "New Scene (2)"));
  REQUIRE((sceneE->getName() == "Menu Scene (1)"));
  REQUIRE((sceneF->getName() == "Menu Scene (2)"));

  REQUIRE((game.getSceneByName("Menu Scene")->getId() == sceneD->getId()));

  game.setName("another_name");
  game.setActiveScene(sceneE->getId());

  REQUIRE(game.getName() == "another_name");
  REQUIRE(game.isRunning());
}