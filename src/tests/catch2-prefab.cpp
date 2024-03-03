#include <catch2/catch_test_macros.hpp>

#include <engine/component/spatial/SpatialComp.hpp>
#include <engine/core/Game.hpp>

TEST_CASE("Prefab", "[Add & Instantiate prefabs]") {
  kln::Game game;
  game.createScene();

  REQUIRE((game.getPrefabs().size() == 0));

  std::shared_ptr<kln::Entity> prefab = std::make_shared<kln::Entity>("MyPrefab");
  prefab->addComp(std::make_shared<kln::SpatialComp>());
  game.addPrefab(prefab);

  REQUIRE((game.getPrefabs().size() == 1));

  // TODO REWORK THE TEST TO MATCH THE NEW INSTANTIATE METHOD
  // std::shared_ptr<ge::Entity> clone = game.getSceneByName("New
  // Scene")->instantiate(prefab);

  // ge::SpatialComp* cloneSpatial =
  // dynamic_cast<ge::SpatialComp*>(clone->getComp("Spatial").get());
  // cloneSpatial->setPos(ge::Vector2(5, 0));

  // ge::SpatialComp* prefabSpatial =
  // dynamic_cast<ge::SpatialComp*>(prefab->getComp("Spatial").get());

  // REQUIRE((prefabSpatial->getPos() != cloneSpatial->getPos()));
}