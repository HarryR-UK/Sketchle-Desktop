#include "EventHandler.h"

using namespace sk;


EventHandler::EventHandler(){

}
EventHandler::~EventHandler(){}

void EventHandler::pollEvents(sk::Window& window, sk::Input& input){
    while(window.pollEvent(mEvent)){
        switch (mEvent.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::MouseButtonPressed:
                if(mEvent.mouseButton.button == sf::Mouse::Left)
                    input.mouseButton1Pressed = true;
                if(mEvent.mouseButton.button == sf::Mouse::Right)
                    input.mouseButton2Pressed = true;

                std::cout << "Mouse Button Pressed!" << '\n';
                break;
            case sf::Event::MouseButtonReleased:
                if(mEvent.mouseButton.button == sf::Mouse::Left)
                    input.mouseButton1Pressed = false;
                if(mEvent.mouseButton.button == sf::Mouse::Right)
                    input.mouseButton2Pressed = false;
                break;


            default:
                break;
        }
    }
}
