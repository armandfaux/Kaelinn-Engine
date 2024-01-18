#include <catch2/catch_test_macros.hpp>

#include <engine/component/body/BodyComp.hpp>
#include <engine/component/input/InputComp.hpp>
#include <engine/component/spatial/SpatialComp.hpp>
#include <engine/core/Entity.hpp>

TEST_CASE("Entity", "[component operations]") {
  ge::Entity entity(1, "name");
  entity.addComp(std::make_shared<ge::SpatialComp>());
  entity.addComp(std::make_shared<ge::InputComp>());

  REQUIRE(entity.hasComp("Spatial"));
  REQUIRE(entity.hasComps(std::vector<std::string>{"Input", "Spatial"}));
}

TEST_CASE("Entity", "[getters]") {
  ge::Entity entity(143, "name");
  entity.addComp(std::make_shared<ge::SpatialComp>());
  entity.addComp(std::make_shared<ge::InputComp>());
  entity.addComp(std::make_shared<ge::BodyComp>(10, ge::Vector2(20, 30)));

  REQUIRE((entity.getComp("Spatial")->getName() == "Spatial"));
  REQUIRE((entity.getPtrComps().size() == 3));
  REQUIRE((entity.getId() == 143));
  REQUIRE((entity.getName() == "name"));
}