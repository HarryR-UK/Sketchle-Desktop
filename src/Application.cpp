//
// Author: Harry Rotheram
//
//
#include "Application.h"
#include "Clock.h"
#include "scene/scenes/CanvasScene.h"
#include "scene/scenes/MainMenuScene.h"
#include <cmath>
using namespace sk;

Application::Application()
    : mWindow(0, 0, 8)
{
    sf::Vector2u monitorRes = mWindow.getMonitorResolution();
    mWindow.setWindowSize({static_cast<unsigned int>(monitorRes.x * 0.7f), static_cast<unsigned int>(monitorRes.y * 0.7f)});
}

Application::~Application(){

}

void Application::render(){
    mWindow.clear();

    mSceneManager.draw(mWindow);


    mWindow.display();
}

void Application::run(){
    mSceneManager.changeScene<MainMenuScene>(mWindow);
    
    sk::Clock clock;

    while(mWindow.getIsWindowOpen()){
        // start clock
        clock.update();
        float dt = clock.getDeltaTime();
        float elapsed = clock.getElapsedTime();
        
        // poll events
        mEventHandler.pollEvents(mWindow, mInput);
                               
        // update
        mInput.update(mWindow);

        mSceneManager.update(mInput, dt, elapsed);


        
        // rendering
        render();
        

    }
}

