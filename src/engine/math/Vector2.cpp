#include "Vector2.hpp"

using namespace kln;

// ctor
Vector2::Vector2() : x(0.0), y(0.0) {}
Vector2::Vector2(double x, double y) : x(x), y(y) {}

void Vector2::limit(double value) {
    x = std::max(x, -value);
    x = std::min(x, value);
    y = std::max(y, -value);
    y = std::min(y, value);
}

// operators
Vector2 Vector2::operator+(const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }

Vector2 Vector2::operator-(const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }

// TODO currently not tested
Vector2 Vector2::operator*(double scalar) const { return Vector2(x * scalar, y * scalar); }

// TODO currently not tested
Vector2 Vector2::operator/(double scalar) const {
    if (scalar != 0.0) { // division by zero check
        return Vector2(x / scalar, y / scalar);
    } else {
        // TODO Handle the error appropriately (throw an exception, set to a
        // default value, etc.)
        return Vector2();
    }
}

bool Vector2::operator==(const Vector2 &other) const { return (x == other.x) && (y == other.y); }

bool Vector2::operator!=(const Vector2 &other) const { return (x != other.x) || (y != other.y); }