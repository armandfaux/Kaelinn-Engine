#include "RenderSystem.hpp"

using namespace ge;

RenderSystem::RenderSystem(std::string title, unsigned int width, unsigned int height, unsigned int bitsPerPixel,
                           std::string style) {
    sf::VideoMode mode(width, height, bitsPerPixel);
    _window = std::make_shared<sf::RenderWindow>(mode, title,
                                                 ((style == "None")         ? sf::Style::None
                                                  : (style == "Titlebar")   ? sf::Style::Titlebar
                                                  : (style == "Resize")     ? sf::Style::Resize
                                                  : (style == "Close")      ? sf::Style::Close
                                                  : (style == "Fullscreen") ? sf::Style::Fullscreen
                                                                            : sf::Style::Default));

    _systemType = SystemType::client;
    std::cout << "[SYSTEM] Render System successfully created\n";
}

// getters
RenderSystem::SfObject RenderSystem::getObjectById(uint32_t id) {
    for (auto &object : _objects) {
        if (object.getEntityId() == id) {
            return object;
        }
    }
    // TODO throw an exception
    return SfObject(0, "", Vector2(), Vector2(), Vector2());
}

std::shared_ptr<sf::RenderWindow> RenderSystem::getWindow() { return _window; }

void RenderSystem::update(std::shared_ptr<Scene> &scene) {
    std::vector<std::shared_ptr<Entity>> &entities = scene->getEntities();

    _window->clear(sf::Color::Black);
    // TODO cut this code in several function ? might be better engineering to
    // do here required from the entity : (SpatialComp, SpriteComp)
    for (auto &entity : entities) {
        if (entity->hasComps(std::vector<std::string>{"Spatial", "Sprite"})) {
            // Checks if the entity exists in current sprite list
            SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
            SpriteComp *spriteComp = dynamic_cast<SpriteComp *>(entity->getComp("Sprite").get());

            for (auto &event : _eventQueue) {
                switch (event.type) {
                case Type::pos:
                    if (event.entityId1 == entity->getId()) {
                        spatialComp->setPos(event.pos);
                    }
                    break;
                case Type::switchScene:
                    _objects.clear();
                    break;
                case Type::exit:
                    std::cout << "[RENDERSYSTEM] Exit event received\n";
                    _window->close();
                    break;
                }
            }

            if (!isEntityCreated(entity->getId())) {
                initObject(entity);
            } else {
                for (auto &object : _objects) {
                    if (object.getEntityId() == entity->getId()) {
                        // Update the sprite position
                        object.setOffset(spriteComp->getOffset());
                        object.setPosition(spatialComp->getPos());
                        if (!object.isText()) {
                            _window->draw(object.getSprite());
                        } else {
                            _window->draw(object.getText());
                        }
                    }
                }
            }
        }
    }
    _window->display();
}

bool RenderSystem::isEntityCreated(uint32_t id) {
    for (auto &sprite : _objects) {
        if (sprite.getEntityId() == id) {
            return true;
        }
    }
    return false;
}

void RenderSystem::initObject(std::shared_ptr<Entity> entity) {
    // TODO hascomp/getcomp merge optimisation
    if (entity->hasComps(std::vector<std::string>{"Sprite", "Spatial"})) {
        SpriteComp *spriteComp = dynamic_cast<SpriteComp *>(entity->getComp("Sprite").get());
        SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());

        std::string filePath = spriteComp->getImagePath();
        if (std::filesystem::exists(filePath)) {
            if (spriteComp->getRect().x < 0) {
                SfObject newSprite(entity->getId(), filePath, spatialComp->getPos());
                _objects.push_back(newSprite);
            } else {
                SfObject newSprite(entity->getId(), filePath, spatialComp->getPos(), spriteComp->getRect(),
                                   spriteComp->getOffset());
                _objects.push_back(newSprite);
            }
        } else {
            std::cout << "[RENDER] " << filePath << " - no such file or directory\n";
        }
    }
    // to create a text object, the entity must have a TextComp and a
    // SpatialComp
    if (entity->hasComps(std::vector<std::string>{"Text", "Spatial"})) {
        TextComp *textComp = dynamic_cast<TextComp *>(entity->getComp("Text").get());
        SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());

        std::string fontPath = textComp->getFontPath();
        if (std::filesystem::exists(fontPath)) {
            SfObject newText(entity->getId(), fontPath, (spatialComp->getPos() + textComp->getOffset() / 8),
                             textComp->getContent(), textComp->getSize());
            _objects.push_back(newText);
        } else {
            std::cout << "font not found" << std::endl;
            // TODO Throw an exception
        }
    }
}

RenderSystem::SfObject::SfObject(uint32_t id, std::string filePath, Vector2 pos) {
    _textr = std::make_shared<sf::Texture>();
    if (!_textr->loadFromFile(filePath)) {
        // TODO Exception warning
        return;
    }
    _sprite = sf::Sprite(*_textr.get());
    _sprite.setPosition(pos.x, pos.y);
    _entityId = id;
}

RenderSystem::SfObject::SfObject(uint32_t id, std::string filePath, Vector2 pos, Vector2 rect, Vector2 offset) {
    _textr = std::make_shared<sf::Texture>();
    if (!_textr->loadFromFile(filePath)) {
        // TODO Exception warning
        return;
    }
    _rect = rect;
    _sprite = sf::Sprite(*_textr.get());
    sf::Rect<int> textrRect(offset.x, offset.y, rect.x, rect.y);
    _sprite.setTextureRect(textrRect);
    _entityId = id;
}

RenderSystem::SfObject::SfObject(uint32_t id, std::string filePath, Vector2 pos, std::string content, size_t size) {
    _entityId = id;

    _font = std::make_shared<sf::Font>();
    if (!_font->loadFromFile(filePath)) {
        // TODO Exception warning
        return;
    }

    _text.setFont(*_font.get());
    _text.setString(content);
    _text.setCharacterSize(size);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(pos.x, pos.y);

    _isText = true;
}

uint32_t RenderSystem::SfObject::getEntityId() { return _entityId; }

sf::Sprite RenderSystem::SfObject::getSprite() { return _sprite; }

sf::Text RenderSystem::SfObject::getText() { return _text; }

std::shared_ptr<sf::Texture> RenderSystem::SfObject::getTextr() { return _textr; }

bool RenderSystem::SfObject::isText() { return _isText; }

sf::Vector2f round(const sf::Vector2f vector) { return sf::Vector2f{std::round(vector.x), std::round(vector.y)}; }

void RenderSystem::SfObject::setPosition(Vector2 pos) { _sprite.setPosition(round(pos.x), round(pos.y)); }

void RenderSystem::SfObject::setOffset(Vector2 offset) {
    sf::Rect<int> textrRect(offset.x, offset.y, _rect.x, _rect.y);
    _sprite.setTextureRect(textrRect);
}

RenderSystem::SfObject::~SfObject() {}
