#include <catch2/catch_test_macros.hpp>

#include <engine/component/body/BodyComp.hpp>
#include <engine/component/input/InputComp.hpp>
#include <engine/component/spatial/SpatialComp.hpp>
#include <engine/core/Entity.hpp>

TEST_CASE("Entity", "[component operations]") {
  kln::Entity entity(1, "name");
  entity.addComp(std::make_shared<kln::SpatialComp>());
  entity.addComp(std::make_shared<kln::InputComp>());

  REQUIRE(entity.hasComp("Spatial"));
  REQUIRE(entity.hasComps(std::vector<std::string>{"Input", "Spatial"}));
}

TEST_CASE("Entity", "[getters]") {
  kln::Entity entity(143, "name");
  entity.addComp(std::make_shared<kln::SpatialComp>());
  entity.addComp(std::make_shared<kln::InputComp>());
  entity.addComp(std::make_shared<kln::BodyComp>(10, kln::Vector2(20, 30)));

  REQUIRE((entity.getComp("Spatial")->getName() == "Spatial"));
  REQUIRE((entity.getPtrComps().size() == 3));
  REQUIRE((entity.getId() == 143));
  REQUIRE((entity.getName() == "name"));
}