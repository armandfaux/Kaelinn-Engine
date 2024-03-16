#include "BodyComp.hpp"

using namespace kln;

BodyComp::BodyComp(double mass = 1, Vector2 bounds = {0, 0}, double speed = 0, Vector2 velocity = {0, 0}) {
    _type = CompType::BODY;
    _mass = mass;
    _bounds = bounds;
    _speed = speed;
    _velocity = velocity;
}

// BodyComp::BodyComp(Vector2 bounds) {
//     _type = "Body";
//     _bounds = bounds;
// }

// BodyComp::BodyComp(double mass, Vector2 bounds) {
//     _type = "Body";
//     _mass = mass;
//     _bounds = bounds;
//     _speed = 0;
// }

// BodyComp::BodyComp(double mass, Vector2 bounds, double speed) {
//     _type = "Body";
//     _mass = mass;
//     _bounds = bounds;
//     _speed = speed;
// }

// getters

double BodyComp::getMass() { return _mass; }

double BodyComp::getSpeed() { return _speed; }

Vector2 BodyComp::getBounds() { return _bounds; }

Vector2 BodyComp::getVelocity() { return _velocity; }

// setters

void BodyComp::setMass(double mass) { _mass = mass; }

void BodyComp::setSpeed(double speed) { _speed = speed; }

void BodyComp::setBounds(Vector2 bounds) { _bounds = bounds; }

void BodyComp::setVelocity(Vector2 velocity) { _velocity = velocity; }

std::shared_ptr<IComponent> BodyComp::clone() { return std::make_shared<BodyComp>(_mass, _bounds, _speed, _velocity); }