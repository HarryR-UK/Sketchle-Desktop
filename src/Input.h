//
// Author: Harry Rotheram
//
//
#ifndef INPUT_H
#define INPUT_H

#include "Window.h"
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

namespace sk {
    struct Input{
        sf::Vector2i mousePositionScreen;
        sf::Vector2i mousePositionWindow;
        bool mouseButton1Pressed = false;
        bool mouseButton2Pressed = false;
        bool mouseButton1Clicked = false;
        bool mouseButton2Clicked = false;

        void update(sk::Window& window);

        private:
            bool mouseButton1Held = false;
            bool mouseButton2Held = false;
    };
}

#endif //!INPUT_H
