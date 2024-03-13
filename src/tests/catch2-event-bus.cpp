// #include <catch2/catch_test_macros.hpp>

// #include <engine/event/Event.hpp>
// #include <engine/event/Subscriber.hpp>
// #include <engine/system/physic/PhysicSystem.hpp>

// TEST_CASE("Event Bus", "[init]") {
//   std::shared_ptr<kln::PhysicSystem> system1 =
//       std::make_shared<kln::PhysicSystem>();
//   std::shared_ptr<kln::ControlSystem> system2 =
//       std::make_shared<kln::ControlSystem>();

//   REQUIRE(system1->getSubscriber());
//   REQUIRE(system2->getSubscriber());
// }

// TEST_CASE("Event Bus", "[event transmission]") {
//   std::shared_ptr<kln::PhysicSystem> system1 =
//       std::make_shared<kln::PhysicSystem>();
//   std::shared_ptr<kln::ControlSystem> system2 =
//       std::make_shared<kln::ControlSystem>();

//   system1->subscribe(system2->getSubscriber());
//   system2->subscribe(system1->getSubscriber());

//   REQUIRE((system1->getEventCount() == 0));
//   REQUIRE((system2->getEventCount() == 0));

//   kln::Event event;

//   system2->getPublisher().publish(event);
//   system1->getPublisher().publish(event);
//   system1->getPublisher().publish(event);

//   REQUIRE((system1->getEventCount() == 1));
//   REQUIRE((system2->getEventCount() == 2));
// }