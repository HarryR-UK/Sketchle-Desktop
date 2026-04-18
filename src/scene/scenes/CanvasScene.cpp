#include "CanvasScene.h"
#include <memory>

using namespace sk;

void CanvasScene::initButtons(sk::Window& window){
    mFont.loadFromFile("assets/arial/ARIAL.TTF");
    sf::Vector2i windowSize = window.getWindowSize();

    //Brush button
    auto brushButton = std::make_unique<sk::Button>();
    brushButton->init("Brush", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    brushButton->setPosition({10, (float)(windowSize.y * 0.3f)});
    brushButton->setBtnHoverColor(sf::Color(150, 70, 225));
    brushButton->onClick = [](){ std::cout << "Brush Selected" << '\n'; };
    addGUIElement(std::move(brushButton));

    //Eraser button
    auto eraserButton = std::make_unique<sk::Button>();
    eraserButton->init("Eraser", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    eraserButton->setPosition({10, (float)(windowSize.y * 0.3f) + 60});
    eraserButton->setBtnHoverColor(sf::Color(150, 70, 225));
    eraserButton->onClick = [](){ std::cout << "Eraser Selected" << '\n'; };
    addGUIElement(std::move(eraserButton));

    //Bucket button
    auto bucketButton = std::make_unique<sk::Button>();
    bucketButton->init("Fill", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    bucketButton->setPosition({10, (float)(windowSize.y * 0.3f) + 120});
    bucketButton->setBtnHoverColor(sf::Color(150, 70, 225));
    bucketButton->onClick = [](){ std::cout << "Fill Selected" << '\n'; };
    addGUIElement(std::move(bucketButton));
    
    //Share button
    auto shareButton = std::make_unique<sk::Button>();
    shareButton->init("Share", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    shareButton->setPosition({10, (float)(windowSize.y * 0.3f) + 180});
    shareButton->setBtnHoverColor(sf::Color(150, 70, 225));
    shareButton->onClick = [](){ std::cout << "Share Selected" << '\n'; };
    addGUIElement(std::move(shareButton));
    
    //Submit button
    auto submitButton = std::make_unique<sk::Button>();
    submitButton->init("Submit", {120, 50}, sf::Color(100, 200, 100), sf::Color::White, mFont, 20);
    submitButton->setPosition({(float)(windowSize.x * 0.5f) - 60, (float)(windowSize.y - 70)});
    submitButton->setBtnHoverColor(sf::Color(70, 170, 70));
    submitButton->onClick = [](){ std::cout << "Drawing Submitted" << '\n'; };
    addGUIElement(std::move(submitButton));
}

void CanvasScene::initCanvas(sk::Window& window){
    
}

CanvasScene::CanvasScene(sk::Window& window)
: mTool(mGridPixelSize, mGridPixelOutlineSize){
    initButtons(window);
    initCanvas(window);
}

void CanvasScene::update(const Input& input){
    
    mTool.update(input);

    Scene::update(input);
}

void CanvasScene::draw(sk::Window& window){
    mTool.draw(window);

    Scene::draw(window);
}

CanvasScene::~CanvasScene(){
}
