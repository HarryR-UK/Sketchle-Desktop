//
// Author: Harry Rotheram
//
//

#ifndef SLIDER_H
#define SLIDER_H

#include "GUIElement.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
namespace sk {
    class Slider : public GUIElement{
        private:
            sf::RectangleShape mBarShape;
            sf::CircleShape mDotShape;
            sf::Color mDotColor;
            sf::Color mDotHoverColor;

            sf::Vector2f mSliderPos;

            sf::Vector2f mDotPos;

            float mBarLength;
            float mBarHeight;

            bool mDragging = false;

            float mMaxValue;
            float mMinValue;
            float mCurrentValue;
        private:

        public:

        public:
            void update(const Input& input) override;
            void draw(sk::Window& window) override;
            
            Slider();
            Slider(const int& length, const sf::Color& barColor, const sf::Color& dotColor, float min = 0.0f, float max = 1.0f);

            void init(const int& length, const sf::Color& barColor, const sf::Color& dotColor, float min = 0.0f, float max = 1.0f);

            void setPosition(const sf::Vector2f& pos);
            void setHoverDotColor(const sf::Color& c);
            void setCurrentValue(const float& val);

            const float& getCurrentValue() const;


    };
}


#endif // !SLIDER_H
