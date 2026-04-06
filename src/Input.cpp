#include "Input.h"


using namespace sk;


void Input::update(sk::Window& window){
    this->mousePositionScreen = sf::Mouse::getPosition();
    this->mousePositionWindow = sf::Mouse::getPosition(*(window.getRenderWindow()));
}
