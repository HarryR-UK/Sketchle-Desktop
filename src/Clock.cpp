//
// Author: Finn O'Hare
//
//
#include "Clock.h"

using namespace sk;

Clock::Clock(){}

float Clock::restart(){
    return mClock.restart().asSeconds();
}

float Clock::getElapsedTime() const{
    return mClock.getElapsedTime().asSeconds();
}

void Clock::update(){
    mDeltaTime = mClock.restart().asSeconds();
}

float Clock::getDeltaTime() const{
    return mDeltaTime;
}