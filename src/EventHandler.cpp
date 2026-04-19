//
// Author: Harry Rotheram
//
//
#include "EventHandler.h"

using namespace sk;


EventHandler::EventHandler(){

}
EventHandler::~EventHandler(){}

void EventHandler::pollEvents(sk::Window& window, Input& input){
    input.lastCharTyped = 0; // reset previous keystroke
    while(window.pollEvent(mEvent)){
        switch (mEvent.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                input.lastCharTyped = mEvent.text.unicode; 
                break;
            default:
                break;
        }

    }
}


