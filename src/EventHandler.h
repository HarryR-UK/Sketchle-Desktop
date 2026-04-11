//
// Author: Harry Rotheram
//
//
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Window.h"
#include "Input.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace sk {
    class EventHandler{

        private:
            sf::Event mEvent;
        private:

        public:

        public:
            EventHandler();
            ~EventHandler();
            const sf::Event& getEvent();
            void pollEvents(sk::Window& window);


    };

}



#endif // !EVENTHANDLER_H



