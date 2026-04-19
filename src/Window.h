//
// Author: Harry Rotheram
//
//


#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cstdlib>

typedef sf::Vector2i veci;

namespace sk {
    class Window{

        private:
            sf::RenderWindow mRenderWindow;
            sf::ContextSettings mContextSettings;
            sf::VideoMode mVideoMode;

            sf::View mWorldView;
            sf::View mGUIView;
            
            veci mWindowSize;

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
            void clear(const sf::Color& c);
            void display();

            void close();
            bool pollEvent(sf::Event& event);
            sf::RenderWindow* getRenderWindow();

            const veci& getWindowSize();
            sf::Vector2u getMonitorResolution();
            void setWindowSize(const sf::Vector2u& size);

            sf::Vector2f mapPixeltoCoords(sf::Vector2i mouseWindowPos);

            bool hasFocus();

            void changeToWorldView();
            void changeToGUIView();
            sf::View& getWorldView();
            sf::View& getGUIView();

            void moveCamera(sf::Vector2f pos);
        

    };

}

#endif //!WINDOW_H
