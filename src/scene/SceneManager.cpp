#include "SceneManager.h"
using namespace sk;


void SceneManager::draw(sk::Window& window){
    if(mCurrentScene) mCurrentScene->draw(window);
}

void SceneManager::update(const Input& input){
    if(mCurrentScene) mCurrentScene->update(input);
}
