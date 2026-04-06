#ifndef INPUT_H
#define INPUT_H

#include "Window.h"
#include <SFML/Window.hpp>

namespace sk {
    struct Input{
        sf::Vector2i mousePositionScreen;
        sf::Vector2i mousePositionWindow;
        bool mouseButton1Pressed;
        bool mouseButton2Pressed;

        void update(sk::Window& window);
    };
}

#endif //!INPUT_H
