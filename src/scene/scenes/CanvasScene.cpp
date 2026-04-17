#include "CanvasScene.h"
#include <memory>

using namespace sk;

void CanvasScene::initButtons(sk::Window& window){
    mFont.loadFromFile("assets/arial/ARIAL.TTF");
    std::unique_ptr<sk::Button> testButton = std::make_unique<sk::Button>();
    testButton->init("Test", {100,100}, sf::Color::White, sf::Color::Black, mFont, 24);
    testButton->setPosition({200,200});

    testButton->setBtnHoverColor(sf::Color::Red);
    testButton->setTxtHoverColor(sf::Color::White);


    addGUIElement(std::move(testButton));
}

void CanvasScene::initCanvas(sk::Window& window){
    
}

CanvasScene::CanvasScene(sk::Window& window){
    initButtons(window);
    initCanvas(window);
}

void CanvasScene::update(const Input& input){
    // allow user to draw


    Scene::update(input);
}

void CanvasScene::draw(sk::Window& window){

    Scene::draw(window);
}

CanvasScene::~CanvasScene(){
}
