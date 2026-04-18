// Author: Finn O'Hare
#include "Textbox.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>

using namespace sk;

Textbox::Textbox(){}

Textbox::Textbox(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize){
    this->init(txt, size, bgColor, txtColor, font, fontSize);
}

void Textbox::init(const std::string& txt, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Color& txtColor, const sf::Font& font, const int& fontSize){
    mText.setString(txt);
    mText.setFillColor(txtColor);
    mText.setFont(font);
    mText.setCharacterSize(fontSize);

    mTboxColor = bgColor;
    mTextColor = txtColor;
    mTboxHoverColor = bgColor;
    mTextHoverColor = txtColor;

    mTboxShape.setSize(size);
    mTboxShape.setFillColor(bgColor);
}

void Textbox::setPosition(const sf::Vector2f& pos){
    mTboxShape.setPosition(pos);
    mPosition = sf::Vector2f(pos);

    float xPos = pos.x + 8.f;
    float yPos = (pos.y + mTboxShape.getGlobalBounds().height * 0.5f) - (mText.getGlobalBounds().height * 0.5f);

    mText.setPosition(sf::Vector2f(xPos, yPos));
}

void Textbox::setTboxHoverColor(const sf::Color& c){
    mTboxHoverColor = c;
}

void Textbox::setTxtHoverColor(const sf::Color& c){
    mTextHoverColor = c;
}

void Textbox::mouseHovered(){
    mTboxShape.setFillColor(mTboxHoverColor);
    mText.setFillColor(mTextHoverColor);
}

void Textbox::mouseNotHovered(){
    if(mTboxShape.getFillColor() == mTboxColor && mText.getFillColor() == mTextColor) return;

    mTboxShape.setFillColor(mTboxColor);
    mText.setFillColor(mTextColor);
}

const sf::Vector2f& Textbox::getPosition(){ 
    return mPosition; 
}

void Textbox::setSelected(bool selected){
    mIsSelected = selected;
}

std::string Textbox::getText(){
    return mUserInput;
}

void Textbox::setPlaceholder(const std::string& placeholder){
    mPlaceholder = placeholder;
    mText.setString(placeholder);
}

void Textbox::update(const Input& input){
    sf::Vector2f boxPos = mTboxShape.getPosition();

    float boxWidth = boxPos.x + mTboxShape.getLocalBounds().width;
    float boxHeight = boxPos.y + mTboxShape.getLocalBounds().height;

    const sf::Vector2i* mousePos = &input.mousePositionWindow;

    // hover & selection
    if(mousePos->x < boxWidth && mousePos->x > boxPos.x && mousePos->y < boxHeight && mousePos->y > boxPos.y){
        mouseHovered();

        if(input.mouseButton1Clicked){
            mIsSelected = true;
            if(mUserInput.empty()){
                mText.setString("_"); // clear input if showing placeholder text
            } else {
                mText.setString(mUserInput + "_"); // restore cursor
            }
            //std::cout << "Textbox selected" << '\n';
        }
    }else{
        mouseNotHovered();

        if(input.mouseButton1Clicked){
            mIsSelected = false;
            if(mUserInput.empty()){
                mText.setString(mPlaceholder); // replace placeholder if user typed nothing
            } else {
                mText.setString(mUserInput); // clear cursor when not selected
            }
        }
    }

    if(mIsSelected){
        int charTyped = input.lastCharTyped;
        if(charTyped > 0 && charTyped < 128){
            if(charTyped == 8){ // backspace
                if(!mUserInput.empty()){
                    mUserInput.pop_back();
                    mText.setString(mUserInput + "_");
                }
            }
            else if(charTyped != 13){
                inputLogic(charTyped); // normal typing
            }
            else {
                // do something if enter pressed
                //std::cout << mUserInput << '\n';
                if (onEnter) onEnter();
                return;
            }
        }
    }    
}

void Textbox::inputLogic(int charTyped){
    if(mUserInput.size() <= 12) { // 12 character limit
        mUserInput += static_cast<char>(charTyped);
        mText.setString(mUserInput + "_");
    } else {
        return;
    }  
}

void Textbox::draw(sk::Window& window){
    window.getRenderWindow()->draw(mTboxShape);
    window.getRenderWindow()->draw(mText);
}
