#include "TextComp.hpp"

using namespace kln;

TextComp::TextComp(std::string fontPath, size_t size = 12, std::string content = "New Text", Vector2 offset = {0, 0}) : AComponent() {
    _type = CompType::TEXT;

    if (!std::filesystem::exists(fontPath)) {
        // TODO Exception
        std::cout << "[TEXT] " << fontPath << " - No such file or directory";
    }
    _fontPath = fontPath;
    _size = size;
    _content = content;
    _offset = offset;
}

// getters
std::string TextComp::getFontPath() { return _fontPath; }

size_t TextComp::getSize() { return _size; }

std::string TextComp::getContent() { return _content; }

Vector2 TextComp::getOffset() { return _offset; }

// setters

void TextComp::setFontPath(std::string fontPath) { _fontPath = fontPath; }

void TextComp::setSize(size_t size) { _size = size; }

void TextComp::setContent(std::string content) { _content = content; }

void TextComp::setOffset(Vector2 offset) { _offset = offset; }

std::shared_ptr<IComponent> TextComp::clone() { return std::make_shared<TextComp>(_fontPath, _size, _content); }
