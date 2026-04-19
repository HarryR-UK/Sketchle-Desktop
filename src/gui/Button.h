//
// Author: Harry Rotheram
//
//
#ifndef BUTTON_H
#define BUTTON_H
#include "GUIElement.h"
#include "../Input.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>


namespace sk {
    class Button : public GUIElement{

        private:
            sf::RectangleShape mButtonShape;
            sf::Text mText;
            sf::Vector2f mPosition;
            sf::Color mBtnColor = sf::Color::White;
            sf::Color mTextColor = sf::Color::Black;

            sf::Color mBtnHoverColor = sf::Color::White;
            sf::Color mTextHoverColor = sf::Color::Black;

            sf::Vector2f mButtonSize;
            
            sf::Texture mTexture;
            sf::Sprite mSprite;
            bool mUseImage = false;
           

        private:

        public:

        public:
            Button();
            Button(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize);

            void init(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize);;
            
            void init(const sf::Image& image, const sf::Vector2f& size);

            void setBtnHoverColor(const sf::Color& c);
            void setTxtHoverColor(const sf::Color& c);

            void draw(sk::Window& window) override;

            void setPosition(const sf::Vector2f& pos);
            const sf::Vector2f& getPosition();

            void update(const Input& input) override;

            void mouseHovered();
            void mouseNotHovered();
            
            sf::Vector2f getButtonSize();
            
            std::function<void()> onClick;

        
    };

}

#endif // !BUTTON_H
