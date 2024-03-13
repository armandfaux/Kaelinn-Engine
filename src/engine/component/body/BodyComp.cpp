#include "BodyComp.hpp"

using namespace kln;

BodyComp::BodyComp(Vector2 bounds) {
    _name = "Body";
    _bounds = bounds;
}

BodyComp::BodyComp(double mass, Vector2 bounds) {
    _name = "Body";
    _mass = mass;
    _bounds = bounds;
    _speed = 0;
}

BodyComp::BodyComp(double mass, Vector2 bounds, double speed) {
    _name = "Body";
    _mass = mass;
    _bounds = bounds;
    _speed = speed;
}

BodyComp::BodyComp(double mass, Vector2 bounds, double speed, Vector2 velocity) {
    _name = "Body";
    _mass = mass;
    _bounds = bounds;
    _speed = speed;
    _velocity = velocity;
}

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