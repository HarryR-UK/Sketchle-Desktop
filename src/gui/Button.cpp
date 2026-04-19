//
// Author: Harry Rotheram
//
//
#include "Button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
using namespace sk;

Button::Button(){}

Button::Button(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize){
    this->init(txt, size, bgColor, txtColor, font, fontSize);
}

void Button::init(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize){
    mText.setString(txt);
    mText.setFillColor(txtColor);
    mText.setFont(font);
    mText.setCharacterSize(fontSize);

    mBtnColor = bgColor;
    mTextColor = txtColor;
    mBtnHoverColor = bgColor;
    mTextHoverColor = txtColor;

    mButtonShape.setSize(size);
    mButtonShape.setFillColor(bgColor);

    mButtonSize = size;
}

void Button::setPosition(const sf::Vector2f& pos){
    mButtonShape.setPosition(pos);
    mPosition = sf::Vector2f(pos);
    
    // based on SFML coordinate system (0,0) being top left
    // we can center text accurately with this knowledge (using half the width of the button shapes)
    float xPos = (pos.x + mButtonShape.getGlobalBounds().width * 0.5f) - (mText.getGlobalBounds().width * 0.5f);
    float yPos = (pos.y + mButtonShape.getGlobalBounds().height * 0.5f) - (mText.getGlobalBounds().height * 0.5f);

    mText.setPosition(sf::Vector2f(xPos, yPos));



}

void Button::setBtnHoverColor(const sf::Color& c){
    mBtnHoverColor = c;
}

void Button::setTxtHoverColor(const sf::Color& c){
    mTextHoverColor = c;
}

void Button::mouseHovered(){
    mButtonShape.setFillColor(mBtnHoverColor);
    mText.setFillColor(mTextHoverColor);
}

void Button::mouseNotHovered(){
    if(mButtonShape.getFillColor() == mBtnColor && mText.getFillColor() == mTextColor) return; 

    mButtonShape.setFillColor(mBtnColor);
    mText.setFillColor(mTextColor);
}

const sf::Vector2f& Button::getPosition(){ return mPosition; }

void Button::update(const Input& input){
    sf::Vector2f btnPos = mButtonShape.getPosition();

    float btnPosWidth = mButtonShape.getPosition().x + mButtonShape.getLocalBounds().width;
    float btnPosHeight = mButtonShape.getPosition().y + mButtonShape.getLocalBounds().height;

    const sf::Vector2i* mousePos = &input.mousePositionWindow;
    
    // checking mouse is in the bounds
    if(mousePos->x < btnPosWidth && mousePos->x > btnPos.x && mousePos->y < btnPosHeight && mousePos->y > btnPos.y){
        mouseHovered();
        if(input.mouseButton1Clicked){
            if(onClick) onClick();
        }
    }else{
        mouseNotHovered();
    }

}



void Button::setBtnFillColor(const sf::Color& c){
    mButtonShape.setFillColor(c);
    mBtnColor = c;
}
void Button::setTxtFillFolor(const sf::Color& c){
    mText.setFillColor(c);
    mTextColor = c;
}
void Button::setBtnOutlineColor(const sf::Color& c){
    mButtonShape.setOutlineColor(c);
}

void Button::setBtnOutlineThickness(const int& t){
    mButtonShape.setOutlineThickness(t);
}


void Button::draw(sk::Window& window){
    // render all button elements here
    window.getRenderWindow()->draw(mButtonShape);
    window.getRenderWindow()->draw(mText);
}

sf::Vector2f Button::getButtonSize(){
    return mButtonSize;
}
