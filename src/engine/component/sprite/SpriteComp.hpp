#ifndef SPRITECOMP_HPP_
#define SPRITECOMP_HPP_

#include <filesystem>
#include <iostream>
#include <string>

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace kln {
    class ENGINE_API SpriteComp : public AComponent {
      public:
        SpriteComp(std::string imagePath);
        SpriteComp(std::string imagePath, Vector2 rect);
        SpriteComp(std::string imagePath, Vector2 rect, Vector2 offset);
        virtual ~SpriteComp() = default;

        // getters
        std::string getImagePath();
        Vector2 getRect();
        Vector2 getOffset();

        // setters
        void setImagePath(std::string imagePath);
        void setRect(Vector2 rect);
        void setOffset(Vector2 offset);

        std::shared_ptr<IComponent> clone() override;

      private:
        std::string _imagePath;
        Vector2 _rect;
        Vector2 _offset;
    };
} // namespace kln

#endif /* !SPRITECOMP_HPP_ */
