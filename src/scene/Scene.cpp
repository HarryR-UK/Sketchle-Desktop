//
// Author: Harry Rotheram
//
//
#include "Scene.h"
#include <memory>

using namespace sk;

Scene::Scene(){}

Scene::~Scene(){
}

void Scene::update(const Input& input){
    for(auto& e : mGUIElements){
        e->update(input);
    }
}

void Scene::update(const Input& input, float dt, float elapsed){
    for(auto& e : mGUIElements){
        e->update(input, dt, elapsed);
    }
}

void Scene::draw(sk::Window& window){
    for(auto& e : mGUIElements){
        e->draw(window);
    }
}

void Scene::addGUIElement(std::unique_ptr<GUIElement> e){
    mGUIElements.push_back(std::move(e));
}

