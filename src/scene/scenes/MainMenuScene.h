//
// Author: Harry Rotheram
//
//
#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../Scene.h"
#include "../../Window.h"
#include "../../gui/Button.h"
#include "../../gui/Textbox.h"
#include <SFML/Graphics/Font.hpp>

namespace sk {
    class MainMenuScene : public Scene{
        private:
            sf::Font mFont;
        private:
        public:
        public:
            MainMenuScene(sk::Window& window);
          
    };

}

#endif // !MAINMENUSCENE_H
