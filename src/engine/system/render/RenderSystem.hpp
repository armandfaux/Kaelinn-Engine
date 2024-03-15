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
    enum WindowStyle {
        NONE = 0,
        TITLE,
        RESIZE,
        CLOSE,
        FULLSCREEN,
        DEFAULT,
    };

    class ENGINE_API RenderSystem : public ASystem
    {
        public:
            RenderSystem(std::string title, uint16_t width, uint16_t height, uint16_t bitsPerPixel, WindowStyle style);
            virtual ~RenderSystem() = default;

            class ENGINE_API SfObject
            {
                public:
                    // TODO Can be changed with default values instead
                    SfObject(uint32_t id, std::string filePath, Vector2 pos);
                    SfObject(uint32_t id, std::string filePath, Vector2 pos, Vector2 rect, Vector2 offset);
                    ~SfObject();

                    // getters
                    Entity getEntity();
                    sf::Sprite getSprite();
                    std::shared_ptr<sf::Texture> getTextr();
                    bool isText();

                    // setters
                    void setPosition(Vector2 pos);
                    void setOffset(Vector2 offset);

                private:
                    Entity _entity;
                    sf::Sprite _sprite;
                    std::shared_ptr<sf::Texture> _textr;
                    Vector2 _rect;

            };

            // getters
            SfObject getObjectById(uint32_t id);
            std::shared_ptr<sf::RenderWindow> getWindow();

            void update(std::shared_ptr<Scene> &scene) override;
            void handleEvents();

            bool isEntityCreated(uint32_t id);
            void initObject(std::shared_ptr<Entity> entity);

        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::vector<SfObject> _objects;
    };
} // namespace kln

#endif /* !RENDERSYSTEM_HPP_ */
