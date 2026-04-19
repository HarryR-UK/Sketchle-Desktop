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
        sf::Vector2f mousePositionView;
        bool mouseButton1Pressed = false;
        bool mouseButton2Pressed = false;
        bool mouseButton1Clicked = false;
        bool mouseButton2Clicked = false;
        
        sf::Uint32 lastCharTyped = 0;

        float scrollWheelChange = 0.0f;

        void update(sk::Window& window);
        void resetFrame();

        private:
            bool mouseButton1Held = false;
            bool mouseButton2Held = false;
    };
}

#endif //!INPUT_H
