//
// Author: Finn O'Hare
//
//
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "GUIElement.h"
#include "../Input.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

namespace sk {
    class Textbox : public GUIElement {
        private:
            sf::RectangleShape mTboxShape;
            sf::Text mText;
            sf::Vector2f mPosition;
            sf::Color mTboxColor = sf::Color::White;
            sf::Color mTextColor = sf::Color::Black;

            sf::Color mTboxHoverColor = sf::Color::White;
            sf::Color mTextHoverColor = sf::Color::Black;
            
            bool mIsSelected = false;
            bool mKeyHeld = false;
            
            std::string mUserInput = "";
            std::string mPlaceholder = "";
            
        
        public:
            Textbox();
            Textbox(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize);
            void init(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize);
            
            void setTboxHoverColor(const sf::Color& c);
            void setTxtHoverColor(const sf::Color& c);

            void draw(sk::Window& window) override;

            void setPosition(const sf::Vector2f& pos);
            const sf::Vector2f& getPosition();

            void update(const Input& input) override;

            void mouseHovered();
            void mouseNotHovered();
            
            sf::Vector2f getTboxSize();
            
            void setSelected(bool selected);
            std::string getText();
                                    
            void setPlaceholder(const std::string& placeholder);
            
            std::function<void()> onEnter;
            
            
            
        private:
            void inputLogic(int charTyped);

    };   
}
#endif