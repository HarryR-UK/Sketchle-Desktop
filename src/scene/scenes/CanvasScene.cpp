#include "CanvasScene.h"
#include "CanvasTools/ToolType.h"
#include <memory>

using namespace sk;

void CanvasScene::initButtons(sk::Window& window){
    mFont.loadFromFile("assets/arial/ARIAL.TTF");
    sf::Vector2i windowSize = window.getWindowSize();

    //Clear button
    auto clearButton = std::make_unique<sk::Button>();
    clearButton->init("Clear", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    clearButton->setPosition({10, (float)(windowSize.y * 0.1f)});
    clearButton->setBtnHoverColor(sf::Color(150, 70, 225));
    clearButton->onClick = [this](){ clearCanvas(); };
    addGUIElement(std::move(clearButton));

    //Brush button
    auto brushButton = std::make_unique<sk::Button>();
    brushButton->init("Brush", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    brushButton->setPosition({10, (float)(windowSize.y * 0.3f)});
    brushButton->setBtnHoverColor(sf::Color(150, 70, 225));
    brushButton->onClick = [this](){ 
        mTool.setType(ToolType::BRUSH); 
     };
    addGUIElement(std::move(brushButton));

    //Eraser button
    auto eraserButton = std::make_unique<sk::Button>();
    eraserButton->init("Eraser", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    eraserButton->setPosition({10, (float)(windowSize.y * 0.3f) + 60});
    eraserButton->setBtnHoverColor(sf::Color(150, 70, 225));
    eraserButton->onClick = [this](){
        mTool.setType(ToolType::ERASE);
        std::cout << "ERASE" << '\n';
    };
    addGUIElement(std::move(eraserButton));

    //Bucket button
    auto bucketButton = std::make_unique<sk::Button>();
    bucketButton->init("Fill", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    bucketButton->setPosition({10, (float)(windowSize.y * 0.3f) + 120});
    bucketButton->setBtnHoverColor(sf::Color(150, 70, 225));
    bucketButton->onClick = [](){ std::cout << "Fill Selected" << '\n'; };
    addGUIElement(std::move(bucketButton));
    
    //Share button
    auto toggleOutlineButton = std::make_unique<sk::Button>();
    toggleOutlineButton->init("Outline", {80, 50}, sf::Color(180, 100, 255), sf::Color::White, mFont, 16);
    toggleOutlineButton->setPosition({10, (float)(windowSize.y * 0.3f) + 180});
    toggleOutlineButton->setBtnHoverColor(sf::Color(150, 70, 225));
    toggleOutlineButton->onClick = [this](){
        togglePixelOutlines();
    };
    addGUIElement(std::move(toggleOutlineButton));
    
    //Submit button
    auto submitButton = std::make_unique<sk::Button>();
    submitButton->init("Submit", {120, 50}, sf::Color(100, 200, 100), sf::Color::White, mFont, 20);
    submitButton->setPosition({(float)(windowSize.x * 0.5f) - 60, (float)(windowSize.y - 70)});
    submitButton->setBtnHoverColor(sf::Color(70, 170, 70));
    submitButton->onClick = [](){ std::cout << "Drawing Submitted" << '\n'; };
    addGUIElement(std::move(submitButton));
}

void CanvasScene::togglePixelOutlines(){
    mShowPixelOutlines = !mShowPixelOutlines;
    if(mShowPixelOutlines)
        mGridPixelOutlineSize = mDefaultOutlineSize;
    else
        mGridPixelOutlineSize = 0.f;


    rebuildCanvas();


}

void CanvasScene::rebuildCanvas(){
    float startX = mCanvasPos.x;
    float startY = mCanvasPos.y;

    mCanvasBuffer.setPrimitiveType(sf::Quads);
    mCanvasBuffer.resize(CANVAS_SIZE * CANVAS_SIZE * QUAD_POINT_COUNT);

    for(int y = 0; y < CANVAS_SIZE; ++y){
        for(int x = 0; x < CANVAS_SIZE; ++x){
            int index = (x + y * CANVAS_SIZE) * QUAD_POINT_COUNT;

            float posX = startX + x * (mGridPixelSize + mGridPixelOutlineSize);
            float posY = startY + y * (mGridPixelSize + mGridPixelOutlineSize);

            mCanvasBuffer[index + 0].position = {posX, posY};
            mCanvasBuffer[index + 1].position = {posX + mGridPixelSize, posY};
            mCanvasBuffer[index + 2].position = {posX + mGridPixelSize, posY + mGridPixelSize};
            mCanvasBuffer[index + 3].position = {posX, posY + mGridPixelSize};


            for(int i = 0; i < 4; ++i){
                mCanvasBuffer[index +i].color = mCanvas[x][y];
            }
        }
    }

}

void CanvasScene::clearCanvas(){
    for(int y = 0; y < CANVAS_SIZE; ++y){
        for(int x = 0; x < CANVAS_SIZE; ++x){
            mCanvas[x][y] = sf::Color::White;
        }
    }

    rebuildCanvas();
}

void CanvasScene::initCanvas(sk::Window& window){
    
    float totalSize = CANVAS_SIZE * (mGridPixelSize + mGridPixelOutlineSize);

    sf::Vector2i winSize = window.getWindowSize();

    float startX = (winSize.x - totalSize) / 2.f;
    float startY = (winSize.y - totalSize) / 2.f;

    mCanvasPos = {startX, startY};

    clearCanvas();

}

void CanvasScene::setPixelColor(int x, int y, sf::Color color){
    mCanvas[x][y] = color;

    int index = (x + y * CANVAS_SIZE) * QUAD_POINT_COUNT;
    for(int i = 0; i < QUAD_POINT_COUNT; ++i){
        mCanvasBuffer[index + i].color = color;
    }
}


const sf::Color& CanvasScene::getPixelColor(int x, int y){
    return mCanvas[x][y];
}

CanvasScene::CanvasScene(sk::Window& window)
: mTool(mGridPixelSize, mGridPixelOutlineSize){
    initButtons(window);
    initCanvas(window);

    mTool.setGridOffset(mCanvasPos);
}

void CanvasScene::brushStroke(const Input& input){

    if(input.mouseButton1Pressed || input.mouseButton1Clicked){
        int x = mTool.getMouseGridPosition().x;
        int y = mTool.getMouseGridPosition().y;

        if(getPixelColor(x, y) != mTool.getColorSelected()){
            setPixelColor(x, y, mTool.getColorSelected());
        }

    }
}

void CanvasScene::eraseStroke(const Input& input){
    if(input.mouseButton1Pressed || input.mouseButton1Clicked){
        int x = mTool.getMouseGridPosition().x;
        int y = mTool.getMouseGridPosition().y;

        setPixelColor(x, y, sf::Color::White);

    }
    
}

void CanvasScene::update(const Input& input){ 
    mTool.update(input);
    
    // check for mouse clicks, then paint canvas
    if(!mTool.getOutOfBounds()){
        switch (mTool.getToolType()) {
            case BRUSH:
                brushStroke(input);
                break;
            case ERASE:
                eraseStroke(input);
                break;
            default:
                break;
        }

    }


    Scene::update(input);
}

void CanvasScene::draw(sk::Window& window){
    window.getRenderWindow()->draw(mCanvasBuffer);

    mTool.draw(window);
    Scene::draw(window);
}

CanvasScene::~CanvasScene(){
}
