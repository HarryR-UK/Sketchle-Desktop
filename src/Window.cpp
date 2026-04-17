//
// Author: Harry Rotheram
//
//
#include "Window.h"
#include <SFML/Graphics/Sprite.hpp>
#include <cstddef>
#include <cstdlib>

using namespace sk;

Window::Window(const int& windowH, const int& windowW, const int& antiAlias){
    mVideoMode.height = windowH;
    mVideoMode.width = windowW;

    mWindowSize = {windowW, windowH};

    mContextSettings.antialiasingLevel = antiAlias;



    mRenderWindow = new sf::RenderWindow(mVideoMode, "Sketchle", sf::Style::Close, mContextSettings);

    if(mRenderWindow == nullptr){
        std::cout << "Window not instantiated: cannot allocate memory" << '\n';
        exit(EXIT_FAILURE);
    }

    mView.reset(sf::FloatRect(0,0, windowW, windowH));
    mRenderWindow->setView(mView);

    mIsWindowOpen = true;

}

const sf::Vector2i& Window::getWindowSize(){
    return mWindowSize;
}
Window::~Window(){
    mIsWindowOpen = false;
    delete mRenderWindow;
}

const bool& Window::getIsWindowOpen(){return this->mIsWindowOpen;}

void Window::clear(){ mRenderWindow->clear(); }
void Window::clear(const sf::Color& c){
    mRenderWindow->clear(c);
}
void Window::display(){ mRenderWindow->display(); }

void Window::close(){
    mIsWindowOpen = false;
    mRenderWindow->close();

}

bool Window::pollEvent(sf::Event& event){
    return mRenderWindow->pollEvent(event);
}



sf::RenderWindow* Window::getRenderWindow(){ return mRenderWindow; }


sf::Vector2u Window::getMonitorResolution(){
   return {(sf::VideoMode::getDesktopMode().width),(sf::VideoMode::getDesktopMode().height)};
}

void Window::setWindowSize(const sf::Vector2u& size){
    mRenderWindow->setSize(size);

    mView.reset(sf::FloatRect(0,0, size.x, size.y));
    mRenderWindow->setView(mView);

    mWindowSize = {(int) size.x, (int) size.y};

}
