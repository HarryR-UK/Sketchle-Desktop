// Author: Harry Rotheram
#include "Tool.h"

using namespace sk;

Tool::Tool(const float& gridPixelSize,const float& gridPixelOutlineSize)
    : mPixelOutlineThickness(gridPixelOutlineSize),
    mGridPixelSize(gridPixelSize)
{
    mToolOutline.setOutlineThickness(gridPixelOutlineSize);
    mToolOutline.setFillColor(sf::Color::Transparent);
    mToolOutline.setSize({gridPixelSize, gridPixelSize});
    mToolOutline.setOutlineColor(mColorSelected);
     
}

void Tool::setGridOffset(sf::Vector2f off){
    mGridOffset = off;
}

void Tool::setType(ToolType type){
    mToolType = type;
}
const ToolType& Tool::getToolType() {
    return mToolType;
}


void Tool::update(const Input& input){
    const sf::Vector2f& mouseViewPos = input.mousePositionView;


    // keeps the selctor over a pixel
    int x = (mouseViewPos.x - mGridOffset.x) / (mGridPixelSize + mPixelOutlineThickness);
    int y = (mouseViewPos.y - mGridOffset.y) / (mGridPixelSize + mPixelOutlineThickness);

    if(x < 0 || y < 0 || x >= CANVAS_SIZE || y >= CANVAS_SIZE)
    {
        mOutOfBounds = true;
        return;
    }else{
        mOutOfBounds = false;
    }

    mMouseGridPosition = {(unsigned)x, (unsigned)y};

    float px = mGridOffset.x + x * (mGridPixelSize + mPixelOutlineThickness);
    float py = mGridOffset.y + y * (mGridPixelSize + mPixelOutlineThickness);

    mToolOutline.setPosition(px, py);


}
const sf::Vector2u& Tool::getMouseGridPosition()
{
    return mMouseGridPosition;
}

const sf::Color& Tool::getColorSelected()
{
    return mColorSelected;
}


void Tool::setPixelColor(const sf::Color& color){
    mColorSelected = color;
}

const bool& Tool::getOutOfBounds(){
    return mOutOfBounds;
}
void Tool::draw(sk::Window& window){
    if(!mOutOfBounds) window.getRenderWindow()->draw(mToolOutline);
}
