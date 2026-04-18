#include "Tool.h"

using namespace sk;

Tool::Tool(float gridPixelSize, float pixelOutlineSize){
    mToolOutline.setOutlineThickness(pixelOutlineSize);
    mToolOutline.setOutlineColor(sf::Color::Transparent);
    mToolOutline.setSize({gridPixelSize, gridPixelSize});
    mToolOutline.setOutlineColor(sf::Color::Red);
    
    mGridPixelSize = gridPixelSize;
    
}

void Tool::update(const Input& input){
    const sf::Vector2f& mouseViewPos = input.mousePositionView;


    // keeps the selctor over a pixel
    if(mouseViewPos.x >= 0.f){
        mMouseGridPosition.x = mouseViewPos.x / static_cast<unsigned>(mGridPixelSize);
    }
    
    if(mouseViewPos.y >= 0.f){
        mMouseGridPosition.y = mouseViewPos.y / static_cast<unsigned>(mGridPixelSize);
    }

    mToolOutline.setPosition(mMouseGridPosition.x * mGridPixelSize, mMouseGridPosition.y * mGridPixelSize);

}

void Tool::draw(sk::Window& window){
    window.getRenderWindow()->draw(mToolOutline);
}
