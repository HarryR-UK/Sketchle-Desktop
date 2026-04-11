//
// Author: Harry Rotheram
//
//
#include "EventHandler.h"

using namespace sk;


EventHandler::EventHandler(){

}
EventHandler::~EventHandler(){}

void EventHandler::pollEvents(sk::Window& window){
    while(window.pollEvent(mEvent)){
        switch (mEvent.type) {
            case sf::Event::Closed:
                window.close();
            default:
                break;
        }

    }
}
