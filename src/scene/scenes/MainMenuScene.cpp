#include "MainMenuScene.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <random>

using namespace sk;


MainMenuScene::MainMenuScene(){
    mFont.loadFromFile("assets/arial/ARIAl.TTF");
    auto mTestButton = std::make_unique<sk::Button>();
    mTestButton->init("TEST", {100,100}, sf::Color::White, {0,0,0}, mFont);
    mTestButton->setPosition({0,0}); 

    mTestButton->onClick = [](){
        std::cout << "Button Clicked" << '\n';
    };


    addGUIElement(std::move(mTestButton));
}

