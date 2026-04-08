#include "Application.h"
using namespace sk;

Application::Application()
    : mWindow(500, 500, 3)
{

}

Application::~Application(){

}

void Application::render(){
    mWindow.clear();


    mWindow.display();
}

void Application::run(){
    while(mWindow.getIsWindowOpen()){
        // poll events
        mEventHandler.pollEvents(mWindow, mInput);

        // update
        mInput.update(mWindow);
        //mSceneManager.update();

        
        // rendering
        render();
        

    }
}

