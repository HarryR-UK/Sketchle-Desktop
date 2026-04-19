//
// Author: Harry Rotheram
//
//
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
            void changeScene(Args&&... args){
                mCurrentScene = std::make_unique<T>(std::forward<Args>(args)...);
            }

            void update(const Input& input, sk::Window& window);

            void draw(sk::Window& window);


    };

}

#endif //!SCENEMANAGER_H
