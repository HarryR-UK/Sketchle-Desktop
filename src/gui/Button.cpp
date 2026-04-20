//
// Author: Harry Rotheram and Finn O'Hare
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

// button constructor using image instead of text
void Button::init(const sf::Image& image, const sf::Vector2f& size){
    if(!mTexture.loadFromImage(image)){
        std::cout << "Could not load image (Button.cpp)" << '\n';
        return;
    }
    
    mSprite.setTexture(mTexture);
    
    sf::Vector2u imgSize = image.getSize();
    
    mSprite.setScale(size.x / imgSize.x, size.y / imgSize.y);
    
    mButtonShape.setSize(size);
    mButtonShape.setFillColor(sf::Color::Transparent);
    mButtonSize = size;
    mUseImage = true;
}

void Button::setPosition(const sf::Vector2f& pos){   
    mPosition = sf::Vector2f(pos);
    mButtonShape.setPosition(pos);
    
    if(mUseImage){
        mSprite.setPosition(pos);
    } else{
        mButtonShape.setPosition(pos);
        
        // based on SFML coordinate system (0,0) being top left
        // we can center text accurately with this knowledge (using half the width of the button shapes)
        float xPos = (pos.x + mButtonShape.getGlobalBounds().width * 0.5f) - (mText.getGlobalBounds().width * 0.5f);
        float yPos = (pos.y + mButtonShape.getGlobalBounds().height * 0.5f) - (mText.getGlobalBounds().height * 0.5f);

        mText.setPosition(sf::Vector2f(xPos, yPos));
    }
}

void Button::setBtnHoverColor(const sf::Color& c){
    mBtnHoverColor = c;
}

void Button::setTxtHoverColor(const sf::Color& c){
    mTextHoverColor = c;
}

void Button::setHoverEnabled(bool hoverEnabled){
    mHoverEnabled = hoverEnabled;
}

void Button::mouseHovered(){
    if(!mHoverEnabled) return;
    if(mUseImage){
        mSprite.setColor(sf::Color(200,200,200));
    }else{
        mButtonShape.setFillColor(mBtnHoverColor);
        mText.setFillColor(mTextHoverColor);
    }
    
}

void Button::mouseNotHovered(){
    if(!mHoverEnabled) return;
    if(mButtonShape.getFillColor() == mBtnColor && mText.getFillColor() == mTextColor) return;     
    if(mUseImage){
        mSprite.setColor(sf::Color::White);
    }else{
        mButtonShape.setFillColor(mBtnColor);
        mText.setFillColor(mTextColor);
    }
}

const sf::Vector2f& Button::getPosition(){ return mPosition; }

void Button::update(const Input& input){
    sf::Vector2f btnPos = mPosition;

    float btnPosWidth = mPosition.x + mButtonSize.x;
    float btnPosHeight = mPosition.y + mButtonSize.y;
    
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
void Button::setTxtFillColor(const sf::Color& c){
    mText.setFillColor(c);
    mTextColor = c;
}
void Button::setTxt(const std::string& txt){
    mText.setString(txt);
}

void Button::setBtnOutlineColor(const sf::Color& c){
    mButtonShape.setOutlineColor(c);
}

void Button::setBtnOutlineThickness(const int& t){
    mButtonShape.setOutlineThickness(t);
}

void Button::setImage(const sf::Image& image){
    if(!mTexture.loadFromImage(image)){
        std::cout << "Could not load image" << '\n';
        return;
    }
    mSprite.setTexture(mTexture);
}

void Button::draw(sk::Window& window){
    // render all button elements here
    if(mUseImage){
        window.getRenderWindow()->draw(mButtonShape);
        window.getRenderWindow()->draw(mSprite);
    }else{
        window.getRenderWindow()->draw(mButtonShape);
        window.getRenderWindow()->draw(mText);
    }    
}
void Button::setTxtOutlineColor(const sf::Color& c){
    mText.setOutlineColor(c);
}
void Button::setTxtOutlineThickness(const int& t){
    mText.setOutlineThickness(t);
}

sf::Vector2f Button::getButtonSize(){
    return mButtonSize;
}
