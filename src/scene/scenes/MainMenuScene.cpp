//
// Author: Harry Rotheram
//
//
#include "MainMenuScene.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <random>

using namespace sk;


MainMenuScene::MainMenuScene(sk::Window& window){
    mFont.loadFromFile("assets/arial/ARIAl.TTF");
    auto mTestButton = std::make_unique<sk::Button>();
    sf::Vector2i windowSize = window.getWindowSize();

    std::cout << "Window Size: " << windowSize.x << ", " << windowSize.y << '\n';

    mTestButton->init("TEST", {100,100}, sf::Color::White, {0,0,0}, mFont, 24);
    mTestButton->setPosition({(float)(windowSize.x * 0.5f),(float)(windowSize.y * 0.5f)});

    mTestButton->setBtnHoverColor(sf::Color::Red);
    mTestButton->setTxtHoverColor(sf::Color::Yellow);





    mTestButton->onClick = [](){
        std::cout << "Button Clicked" << '\n';
    };


    addGUIElement(std::move(mTestButton));
}

