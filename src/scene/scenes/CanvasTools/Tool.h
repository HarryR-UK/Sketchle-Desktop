#ifndef TOOL_H
#define TOOL_H

#include "ToolType.h"
#include "../../../Input.h"
#include <SFML/Graphics.hpp>
#include "../../../global.h"

namespace sk {
    class Tool{
        private:
            ToolType mToolType = ToolType::BRUSH;
            sf::RectangleShape mToolOutline;
            sf::Vector2u mMouseGridPosition;
    
            sf::Color mColorSelected = sf::Color::Red;

            const float& mGridPixelSize;

            sf::Vector2f mGridOffset = {0,0};

            bool mOutOfBounds = false;

            const float& mPixelOutlineThickness;


        private:

        public:

        public:
            Tool(const float& gridPixelSize, const float& gridPixelOutlineSize);
            void update(const sk::Input& input);
            void draw(sk::Window& window);

            void setGridOffset(sf::Vector2f off);
            void setPixelOutlineThickness(const float& t);
            void setType(ToolType type);

            const sf::Color& getColorSelected();;
            const sf::Vector2u& getMouseGridPosition();
            const ToolType& getToolType();
            const bool& getOutOfBounds();

    };
}

#endif //!TOOL_H
