#ifndef TOOL_H
#define TOOL_H

#include "ToolType.h"
#include "../../../Input.h"
#include <SFML/Graphics.hpp>

namespace sk {
    class Tool{
        private:
            ToolType mToolType;
            sf::RectangleShape mToolOutline;
            sf::Vector2u mMouseGridPosition;
    
            sf::Color mColorSelected = sf::Color::White;

            float mGridPixelSize;
        private:

        public:

        public:
            Tool(float gridPixelSize, float pixelOutlineSize);
            void update(const sk::Input& input);
            void draw(sk::Window& window);


    };
}

#endif //!TOOL_H
