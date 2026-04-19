//
// Author: Harry Rotheram
//
//
#include "SceneManager.h"
using namespace sk;


void SceneManager::draw(sk::Window& window){
    if(mCurrentScene) mCurrentScene->draw(window);

}

void SceneManager::update(const Input& input, sk::Window& window){
    if(mCurrentScene) mCurrentScene->update(input, window);
}

void SceneManager::update(const Input&input, sk::Window& window, float dt, float elapsed){
    if(mCurrentScene) mCurrentScene->update(input, window, dt, elapsed);
}
