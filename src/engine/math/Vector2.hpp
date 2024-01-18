#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cmath>
#include <ostream>

#include "../EngineApi.hpp"

namespace ge {
    class ENGINE_API Vector2 {
      public:
        Vector2();
        Vector2(double x, double y);
        ~Vector2() = default;

        void limit(double value);

        // operators
        Vector2 operator+(const Vector2 &other) const;
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator*(double scalar) const;
        Vector2 operator/(double scalar) const;
        bool operator==(const Vector2 &other) const;
        bool operator!=(const Vector2 &other) const;

        template <class Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(x), CEREAL_NVP(y)); }

        double x;
        double y;
    };

    inline std::ostream &operator<<(std::ostream &os, const Vector2 &vector) {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }
} // namespace ge

#endif /* !VECTOR2_HPP_ */