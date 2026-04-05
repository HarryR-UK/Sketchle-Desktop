#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <memory>
namespace sk {
    class SceneManager{
        private:
            std::unique_ptr<Scene> mCurrentScene;
        private:


        public:

        public:
            template<typename T, typename... Args>
            void changeScene(Args&&... args);

            void update();
            void draw(sk::Window& window);


    };

}

#endif //!SCENEMANAGER_H
