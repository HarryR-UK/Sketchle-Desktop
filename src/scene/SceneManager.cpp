#include "SceneManager.h"
#include <iterator>
#include <memory>

using namespace sk;


template<typename T, typename... Args>
void SceneManager::changeScene(Args&&... args){
    mCurrentScene = std::make_unique<T>(std::forward<Args>(args)...);
}

void SceneManager::update(){
    mCurrentScene->update();
}

void SceneManager::draw(sk::Window& window){
    mCurrentScene->draw(window);
}
