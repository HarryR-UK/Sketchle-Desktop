#include "Window.h"
#include <SFML/Graphics/Sprite.hpp>
#include <cstdlib>

using namespace sk;

Window::Window(const int& windowH, const int& windowW, const int& antiAlias){
    mVideoMode.height = windowH;
    mVideoMode.width = windowW;

    mContextSettings.antialiasingLevel = antiAlias;


    mRenderWindow = new sf::RenderWindow(mVideoMode, "Sketchle", sf::Style::Close, mContextSettings);

    if(mRenderWindow == nullptr){
        std::cout << "Window not instantiated: cannot allocate memory" << '\n';
        exit(EXIT_FAILURE);
    }

    mIsWindowOpen = true;

}

Window::~Window(){
    mIsWindowOpen = false;
    delete mRenderWindow;
}

const bool& Window::getIsWindowOpen(){return this->mIsWindowOpen;}

void Window::clear(){ mRenderWindow->clear(); }
void Window::display(){ mRenderWindow->display(); }

void Window::close(){
    mIsWindowOpen = false;
    mRenderWindow->close();

}

bool Window::pollEvent(sf::Event& event){
    return mRenderWindow->pollEvent(event);
}



sf::RenderWindow* Window::getRenderWindow(){ return mRenderWindow; }
