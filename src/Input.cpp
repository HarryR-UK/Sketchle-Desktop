//
// Author: Harry Rotheram
//
//
#include "Input.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>


using namespace sk;


void Input::update(sk::Window& window){
    //lastCharTyped = 0;
    this->mousePositionScreen = sf::Mouse::getPosition();
    this->mousePositionWindow = sf::Mouse::getPosition(*(window.getRenderWindow()));

    // Left button
    mouseButton1Clicked = !mouseButton1Held && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    mouseButton1Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    mouseButton1Held = mouseButton1Pressed;

    // Right button
    mouseButton2Clicked = !mouseButton2Held && sf::Mouse::isButtonPressed(sf::Mouse::Right);
    mouseButton2Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    mouseButton2Held = mouseButton2Pressed;
    
    // Key pressed


    // Text entry
    //lastCharTyped = sf::Event::TextEntered;
    //std::cout << "Char: " << lastCharTyped << '\n';
    //std::cout << lastCharTyped << '\n';
    //std::cout << keyHeld << '\n';
    

    
}

