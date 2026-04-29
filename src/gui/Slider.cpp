#include "Slider.h"
#include "SFML/System/Vector2.hpp"
using namespace sk;


Slider::Slider(){

}
Slider::Slider(const int& length, const sf::Color& barColor, const sf::Color& dotColor, float min, float max){
    init(length, barColor, dotColor);
}

void Slider::init(const int& length, const sf::Color& barColor, const sf::Color& dotColor, float min, float max){
    mMinValue = min;
    mMaxValue = max;

    mBarHeight = length * 0.05f;
    mBarShape.setSize({(float)length, mBarHeight});
    mBarShape.setFillColor(barColor);

    mDotShape.setScale({0.5f, 0.5f});
    mDotShape.setFillColor(dotColor);

    mBarLength = length;

    mDotShape.setRadius(length * 0.15f);
    mDotShape.setPointCount(20);

    mDotColor = dotColor;
    mDotHoverColor = {static_cast<sf::Uint8>(dotColor.r * 0.8f),
        static_cast<sf::Uint8>(dotColor.g * 0.8f),
            static_cast<sf::Uint8>(dotColor.b * 0.8f)};


    mDotShape.setOrigin(mDotShape.getRadius(), mDotShape.getRadius());

    mCurrentValue = (min + max) * 0.5f;

    
}

void Slider::setHoverDotColor(const sf::Color& c){
    mDotHoverColor = c;
}

void Slider::update(const Input& input){

    // Check hover
    bool hovering =
        input.mousePositionWindow.x <= mDotShape.getPosition().x + mDotShape.getRadius() &&
        input.mousePositionWindow.x >= mDotShape.getPosition().x - mDotShape.getRadius() &&
        input.mousePositionWindow.y >= mDotShape.getPosition().y - mDotShape.getRadius() &&
        input.mousePositionWindow.y <= mDotShape.getPosition().y + mDotShape.getRadius();

    
    if (hovering && input.mouseButton1Pressed) {
        mDragging = true;
    }

    if (!input.mouseButton1Pressed) {
        mDragging = false;
    }

    if (mDragging) {
        mDotShape.setPosition({
                (float)input.mousePositionWindow.x,
                mDotShape.getPosition().y
        });

        // get percentage of position in relation to bar length
        // times that percentage with max value
        float minPos = mBarShape.getPosition().x;
        float maxPos = mBarShape.getPosition().x + mBarLength;

        float percentage = (mDotShape.getPosition().x - minPos) / (maxPos - minPos);
        percentage = std::clamp(percentage, 0.0f, 1.0f);
        
        mCurrentValue = mMinValue + percentage * (mMaxValue - mMinValue);
        
        
    }

    if (hovering) {
        mDotShape.setFillColor(mDotHoverColor);
    } else {
        mDotShape.setFillColor(mDotColor);
    }


    // constraint
    float left = mBarShape.getPosition().x;
    float right = mBarShape.getPosition().x + mBarLength;

    if (mDotShape.getPosition().x < left) {
        mDotShape.setPosition(left, mDotShape.getPosition().y);
    }
    else if (mDotShape.getPosition().x > right) {
        mDotShape.setPosition(right, mDotShape.getPosition().y);
    }


    std::cout << "VALUE: " << mCurrentValue << '\n';

}
void Slider::draw(sk::Window& window){
    window.getRenderWindow()->draw(mBarShape);
    window.getRenderWindow()->draw(mDotShape);
}


void Slider::setPosition(const sf::Vector2f& pos){
    mSliderPos = pos;
    mBarShape.setPosition(pos);
    mDotShape.setPosition({
        (mSliderPos.x + (mBarLength * 0.5f)),
        mSliderPos.y + (mBarHeight * 0.5f)
    });

}

