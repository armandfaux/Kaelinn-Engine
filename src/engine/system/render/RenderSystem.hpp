#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include "../../EngineApi.hpp"
#include "../../component/spatial/SpatialComp.hpp"
#include "../../component/sprite/SpriteComp.hpp"
#include "../../component/text/TextComp.hpp"
#include "../../core/Entity.hpp"
#include "../ASystem.hpp"

namespace kln {
    // render the sprite components with SFML
    class ENGINE_API RenderSystem : public ASystem {
      public:
        RenderSystem(std::string title, unsigned int width, unsigned int height, unsigned int bitsPerPixel,
                     std::string style);
        virtual ~RenderSystem() = default;

        class ENGINE_API SfObject {
          public:
            SfObject(uint32_t id, std::string filePath, Vector2 pos);
            SfObject(uint32_t id, std::string filePath, Vector2 pos, Vector2 rect, Vector2 offset);
            SfObject(uint32_t id, std::string filePath, Vector2 pos, std::string content, size_t size);
            ~SfObject();

            // getters
            uint32_t getEntityId();
            sf::Sprite getSprite();
            sf::Text getText();
            std::shared_ptr<sf::Texture> getTextr();
            bool isText();

            // setters
            void setPosition(Vector2 pos);
            void setOffset(Vector2 offset);

          private: // private or public ?
            bool _isText = false;
            uint32_t _entityId;
            sf::Sprite _sprite;
            std::shared_ptr<sf::Texture> _textr;
            Vector2 _rect;
            size_t _size;
            sf::Text _text;
            std::shared_ptr<sf::Font> _font;
        };

        // getters
        SfObject getObjectById(uint32_t id);
        std::shared_ptr<sf::RenderWindow> getWindow();

        void update(std::shared_ptr<Scene> &scene) override;

        bool isEntityCreated(uint32_t id);
        void initObject(std::shared_ptr<Entity> entity);

      private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::vector<SfObject> _objects;
    };
} // namespace kln

#endif /* !RENDERSYSTEM_HPP_ */
