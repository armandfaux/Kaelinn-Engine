#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include <engine/math/Vector2.hpp>

TEST_CASE("Vector2", "[ctors]") {
  kln::Vector2 a;
  kln::Vector2 b(10, 5);

  REQUIRE((a.x == 0 && a.y == 0));
  REQUIRE((b.x == 10 && b.y == 5));
}

TEST_CASE("Vector2", "[op overloads]") {
  kln::Vector2 a(1, 3);
  kln::Vector2 b(-1, 2);
  kln::Vector2 c = a + b;
  kln::Vector2 d = a - b;

  REQUIRE((c.x == 0 && c.y == 5));
  REQUIRE((d.x == 2 && d.y == 1));
  REQUIRE(c == kln::Vector2(0, 5));
  REQUIRE(c != kln::Vector2(1, 5));
  REQUIRE(c != kln::Vector2());
}

TEST_CASE("Vector2", "[stream operator]") {
  kln::Vector2 v(10.5, 650);
  std::stringstream stream;
  stream << v;

  REQUIRE(stream.str() == "(10.5, 650)");
}
