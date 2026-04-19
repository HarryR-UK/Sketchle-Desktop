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
            bool mIsKeyHeld = false;
        private:
            
        public:

        public:
            EventHandler();
            ~EventHandler();            
            void pollEvents(sk::Window& window, Input& input);
            


    };

}



#endif // !EVENTHANDLER_H



