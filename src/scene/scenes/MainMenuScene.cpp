//
// Author: Harry Rotheram and Finn O'Hare
//
//
#include "MainMenuScene.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <random>

using namespace sk;


MainMenuScene::MainMenuScene(sk::Window& window){
    // text button
    mFont.loadFromFile("assets/arial/ARIAl.TTF");
    auto mTestButton = std::make_unique<sk::Button>();
    sf::Vector2i windowSize = window.getWindowSize();

    mTestButton->init("TESTES", {100,100}, sf::Color::Red, {0,0,0}, mFont, 26);
    mTestButton->setPosition({(float)(windowSize.x * 0.5f),(float)(windowSize.y * 0.5f)});

    mTestButton->setBtnHoverColor(sf::Color::Red);
    mTestButton->setTxtHoverColor(sf::Color::Yellow);

    mTestButton->onClick = [](){
        std::cout << "Button Clicked" << '\n';
    };

    addGUIElement(std::move(mTestButton));
    
    // image button
    auto mImageButton = std::make_unique<sk::Button>();
    
    sf::Image testImage;
    if(!testImage.loadFromFile("assets/Trollface.png")){
        std::cout << "Could not load image (MainMenuScene.cpp)" << '\n';
    }
    
    mImageButton->init(testImage, {100,100});
    mImageButton->setPosition({(float)(windowSize.x * 0.3f),(float)(windowSize.y * 0.5f)});
    
    mImageButton->onClick = [](){
        std::cout << "trololololololololololololololo" << '\n';
    };
    
    addGUIElement(std::move(mImageButton));
    
    
    // username textbox
    auto mUnameTextbox = std::make_unique<sk::Textbox>();
    auto textboxPtr = mUnameTextbox.get();
    
    mUnameTextbox->init("USERNAME", {300, 50}, sf::Color::White, sf::Color::Black, mFont, 24);
    mUnameTextbox->setPlaceholder("USERNAME");

    mUnameTextbox->setPosition({
        (float)(windowSize.x * 0.4f),
        (float)(windowSize.y * 0.7f)
    });

    mUnameTextbox->setTboxHoverColor(sf::Color(200, 200, 200));
    mUnameTextbox->setTxtHoverColor(sf::Color::Black);
        
    mUnameTextbox->onEnter = [textboxPtr](){
        std::cout << textboxPtr->getText() << '\n'; // print text on enter
    };
    
    addGUIElement(std::move(mUnameTextbox));   
    
    // password textbox
    auto mPwordTextbox = std::make_unique<sk::Textbox>();
    /*auto*/ textboxPtr = mPwordTextbox.get();

    mPwordTextbox->init("PASSWORD", {300, 50}, sf::Color::White, sf::Color::Black, mFont, 24);
    mPwordTextbox->setPlaceholder("PASSWORD");

    mPwordTextbox->setPosition({
        (float)(windowSize.x * 0.4f),
        (float)(windowSize.y * 0.8f)
    });

    mPwordTextbox->setTboxHoverColor(sf::Color(200, 200, 200));
    mPwordTextbox->setTxtHoverColor(sf::Color::Black);
    
    mPwordTextbox->onEnter = [textboxPtr](){
        std::cout << textboxPtr->getText() << '\n'; // print text on enter
    };
    
    addGUIElement(std::move(mPwordTextbox));   
}

