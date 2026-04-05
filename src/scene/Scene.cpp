#include "Scene.h"

using namespace sk;

Scene::Scene(){}

Scene::~Scene(){

}

void Scene::update(){
    for(auto& e: mGUIElements) e->update();

}

void Scene::draw(sk::Window& window){
    for(auto& e: mGUIElements) e->draw(window);
}
