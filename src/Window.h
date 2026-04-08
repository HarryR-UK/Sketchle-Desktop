#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cstdlib>

typedef sf::Vector2i veci;

namespace sk {
    class Window{

        private:
            sf::RenderWindow* mRenderWindow = nullptr;
            sf::ContextSettings mContextSettings;
            sf::VideoMode mVideoMode;

            int mWindowHeight;
            int mWindowWidth;

            veci mMousePosScreen;
            veci mMousePosWindow;

            bool mIsWindowOpen = false;

        private:

        public:

        public:
            Window(const int& windowH, const int& windowW, const int& antiAlias);
            ~Window();
            const bool& getIsWindowOpen();
            void clear();
            void display();

            void close();
            bool pollEvent(sf::Event& event);
            sf::RenderWindow* getRenderWindow();

    };

}

#endif //!WINDOW_H
