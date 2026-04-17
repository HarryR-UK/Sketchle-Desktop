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
    sf::Vector2i windowSize = window.getWindowSize();

    // Title
    auto titleText = std::make_unique<sk::Button>();
    titleText->init("SKETCHLE", {400, 80}, sf::Color(0,0,0,0), sf::Color(180, 100, 255), mFont, 48);
    titleText->setPosition({(float)(windowSize.x * 0.5f) - 200, (float)(windowSize.y * 0.2f)});
    addGUIElement(std::move(titleText));

    // Login button
    auto loginButton = std::make_unique<sk::Button>();
    loginButton->init("Login", {200, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 24);
    loginButton->setPosition({(float)(windowSize.x * 0.5f) - 100, (float)(windowSize.y * 0.5f)});
    loginButton->setBtnHoverColor(sf::Color(150, 70, 225));
    loginButton->onClick = [](){ std::cout << "Login Clicked" << '\n'; };
    addGUIElement(std::move(loginButton));

    // Sign up button
    auto signupButton = std::make_unique<sk::Button>();
    signupButton->init("Sign Up", {200, 50}, sf::Color(220, 180, 255), sf::Color::White, mFont, 24);
    signupButton->setPosition({(float)(windowSize.x * 0.5f) - 100, (float)(windowSize.y * 0.5f) + 70});
    signupButton->setBtnHoverColor(sf::Color(200, 150, 255));
    signupButton->onClick = [](){ std::cout << "Sign Up Clicked" << '\n'; };
    addGUIElement(std::move(signupButton));
}