#ifndef BUTTON_H
#define BUTTON_H
#include "GUIElement.h"
#include "../Input.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

#define CHARACTER_SIZE 12

namespace sk {
    class Button : public GUIElement{

        private:
            sf::RectangleShape mButtonShape;
            sf::Text mText;
            sf::Vector2f mPosition;
        private:

        public:

        public:
            Button();
            Button(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font);

            void init(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font);;

            void draw(sk::Window& window) override;

            void setPosition(const sf::Vector2f& pos);
            const sf::Vector2f& getPosition();

            void update(const Input& input) override;

            std::function<void()> onClick;
        
    };

}

#endif // !BUTTON_H
