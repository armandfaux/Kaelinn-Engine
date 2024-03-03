/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComp
*/

#include "SpriteComp.hpp"

using namespace kln;

SpriteComp::SpriteComp(std::string imagePath) : AComponent() {
    if (!std::filesystem::exists(imagePath)) {
        // TODO Exception
        std::cout << "[SPRITE] " << imagePath << " - No such file or directory";
    }
    _name = "Sprite";
    _imagePath = imagePath;
    _rect = Vector2(-1, -1);
    _offset = Vector2(0, 0); // TODO remove unused lines
}

SpriteComp::SpriteComp(std::string imagePath, Vector2 rect) : AComponent() {
    if (!std::filesystem::exists(imagePath)) {
        // TODO Exception
        std::cout << "[SPRITE] " << imagePath << " - No such file or directory";
    }
    _name = "Sprite";
    _imagePath = imagePath;
    _rect = rect;
    _offset = Vector2(0, 0); // TODO remove unused lines
}

SpriteComp::SpriteComp(std::string imagePath, Vector2 rect, Vector2 offset) : AComponent() {
    if (!std::filesystem::exists(imagePath)) {
        // TODO Exception
        std::cout << "[SPRITE] " << imagePath << " - No such file or directory";
    }
    _name = "Sprite";
    _imagePath = imagePath;
    _rect = rect;
    _offset = offset;
}

// getters
std::string SpriteComp::getImagePath() { return _imagePath; }

Vector2 SpriteComp::getRect() { return _rect; }

Vector2 SpriteComp::getOffset() { return _offset; }

// setters
void SpriteComp::setImagePath(std::string imagePath) { _imagePath = imagePath; }

void SpriteComp::setRect(Vector2 rect) { _rect = rect; }

void SpriteComp::setOffset(Vector2 offset) { _offset = offset; }

std::shared_ptr<IComponent> SpriteComp::clone() { return std::make_shared<SpriteComp>(_imagePath, _rect, _offset); }
