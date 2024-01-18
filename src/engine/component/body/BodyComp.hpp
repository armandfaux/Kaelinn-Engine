#ifndef BODYCOMP_HPP_
#define BODYCOMP_HPP_

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace ge {
    class ENGINE_API BodyComp : public AComponent {
      public:
        // TODO more ctors
        // BodyComp(); // auto mass / bounds
        // BodyComp(double _mass); // auto bounds
        BodyComp(Vector2 bounds);
        BodyComp(double mass, Vector2 bounds);
        BodyComp(double mass, Vector2 bounds, double speed);
        BodyComp(double mass, Vector2 bounds, double speed, Vector2 velocity);
        virtual ~BodyComp() = default;

        // getters
        double getMass();
        double getSpeed();
        Vector2 getBounds();
        Vector2 getVelocity();

        // setters
        void setMass(double mass);
        void setSpeed(double speed);
        void setBounds(Vector2 bounds);
        void setVelocity(Vector2 velocity);

        std::shared_ptr<IComponent> clone() override;

      private:
        double _mass;
        double _speed;
        Vector2 _bounds;
        Vector2 _velocity;
    };
} // namespace ge

#endif /* !BODYCOMP_HPP_ */
