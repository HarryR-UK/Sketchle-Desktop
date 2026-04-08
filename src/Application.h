#ifndef APPLICATION_H
#define APPLICATION_H

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include "EventHandler.h"
#include "Input.h"
#include "Window.h"
#include "scene/SceneManager.h"

#include "scene/scenes/MainMenuScene.h"

namespace sk{
    class Application{
        private:
            sk::Window mWindow;
            sk::EventHandler mEventHandler;
            sk::Input mInput;
            sk::SceneManager mSceneManager;

            

        private:
            void render();


        public:
            void run();

        public:
            Application();
            ~Application();

    };

}



#endif
