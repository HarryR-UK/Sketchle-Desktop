//
// Author: Harry Rotheram
//
//
#include "SceneManager.h"
using namespace sk;


void SceneManager::draw(sk::Window& window){
    if(mCurrentScene) mCurrentScene->draw(window);

}

void SceneManager::update(const Input& input){
    if(mCurrentScene) mCurrentScene->update(input);
}

void SceneManager::update(const Input&input, float dt, float elapsed){
    if(mCurrentScene) mCurrentScene->update(input, dt, elapsed);
}
