//
// Author: Harry Rotheram
//
//
#include "Input.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>


using namespace sk;


void Input::update(sk::Window& window){
    if(window.hasFocus()){
        this->mousePositionScreen = sf::Mouse::getPosition();
        this->mousePositionWindow = sf::Mouse::getPosition(*(window.getRenderWindow()));
        this->mousePositionView = window.mapPixeltoCoords(mousePositionWindow);

        // Left button
        mouseButton1Clicked = !mouseButton1Held && sf::Mouse::isButtonPressed(sf::Mouse::Left);
        mouseButton1Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        mouseButton1Held = mouseButton1Pressed;

        // Right button
        mouseButton2Clicked = !mouseButton2Held && sf::Mouse::isButtonPressed(sf::Mouse::Right);
        mouseButton2Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        mouseButton2Held = mouseButton2Pressed;
    }

    

    
}

