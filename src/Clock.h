//
// Author: Finn O'Hare
//
//
#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/System/Clock.hpp>

namespace sk{
    class Clock{
        private:
            sf::Clock mClock;
            float mDeltaTime = 0.f;
            
        public:
            Clock();
            
            float restart();
            float getElapsedTime() const;
            
            void update();
            float getDeltaTime() const;
    };
}

#endif
