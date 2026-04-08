#include "Application.h"
#include "scene/scenes/MainMenuScene.h"
using namespace sk;

Application::Application()
    : mWindow(500, 500, 3)
{

}

Application::~Application(){

}

void Application::render(){
    mWindow.clear();

    mSceneManager.draw(mWindow);


    mWindow.display();
}

void Application::run(){
    sk::MainMenuScene mainMenuScene;
    mSceneManager.changeScene<MainMenuScene>();

    while(mWindow.getIsWindowOpen()){
        // poll events
        mEventHandler.pollEvents(mWindow);

        // update
        mInput.update(mWindow);

        mSceneManager.update(mInput);


        
        // rendering
        render();
        

    }
}

