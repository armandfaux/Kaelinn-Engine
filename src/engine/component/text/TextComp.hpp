/*
** EPITECH PROJECT, 2024
** B-CPP-500-MPL-5-2-rtype-hugo.eschlimann
** File description:
** TextComp
*/

#ifndef TEXTCOMP_HPP_
#define TEXTCOMP_HPP_

#include <filesystem>
#include <iostream>
#include <string>

#include "../../EngineApi.hpp"
#include "../../math/Vector2.hpp"
#include "../AComponent.hpp"

namespace kln {
    class ENGINE_API TextComp : public AComponent {
      public:
        TextComp(std::string fontPath, size_t size, std::string content, Vector2 offset);
        virtual ~TextComp() = default;

        // getters
        std::string getFontPath();
        size_t getSize();
        std::string getContent();
        Vector2 getOffset();

        // setters
        void setFontPath(std::string fontPath);
        void setSize(size_t size);
        void setContent(std::string content);
        void setOffset(Vector2 offset);

        std::shared_ptr<IComponent> clone() override;

      private:
        std::string _fontPath;
        size_t _size;
        std::string _content;
        Vector2 _offset;
    };

} // namespace kln

#endif /* !TEXTCOMP_HPP_ */
