//
// Author: Harry Rotheram and Finn O'Hare

#include "CanvasScene.h"
#include "CanvasTools/ToolType.h"
#include "SFML/System/Vector2.hpp"
#include <memory>

using namespace sk;

void CanvasScene::initButtons(sk::Window& window, NetworkClient& net){
    mFont.loadFromFile("assets/arial/ARIAL.TTF");
    sf::Vector2i windowSize = window.getWindowSize();
    sf::Image brushImage;
    sf::Image eraserImage;
    sf::Image bucketImage;
    brushImage.loadFromFile("assets/brush.png");
    eraserImage.loadFromFile("assets/eraser.png");
    bucketImage.loadFromFile("assets/bucket.png");
    
    //Tool indicator
    auto toolIndicator = std::make_unique<sk::Button>();
    toolIndicator->init(brushImage, {45,45});
    toolIndicator->setPosition({(float)(windowSize.x*0.95f), (float)(windowSize.y * 0.12f)});
    toolIndicator->setBtnOutlineColor(sf::Color::White);
    toolIndicator->setBtnOutlineThickness(3);
    toolIndicator->setHoverEnabled(false);
    auto* toolIndicatorPtr = toolIndicator.get(); 
    addGUIElement(std::move(toolIndicator));
    
    //Clear button
    auto clearButton = std::make_unique<sk::Button>();    
    sf::Image clearImage;
    if(!clearImage.loadFromFile("assets/clear.png")){
        std::cout << "Could not load image" << '\n';
    }    
    clearButton->init(clearImage, {95,95});
    clearButton->setPosition({10, (float)(windowSize.y * 0.1f)});    
    clearButton->onClick = [this](){ clearCanvas(); };
    addGUIElement(std::move(clearButton));

    //Brush button
    auto brushButton = std::make_unique<sk::Button>();    
    brushButton->init(brushImage, {75,75});
    brushButton->setPosition({10, (float)(windowSize.y * 0.3f)});    
    brushButton->onClick = [this, toolIndicatorPtr, brushImage](){ 
        mTool.setType(ToolType::BRUSH); 
        toolIndicatorPtr->setImage(brushImage);
     };
    addGUIElement(std::move(brushButton));
    
    //Eraser button
    auto eraserButton = std::make_unique<sk::Button>();     
    eraserButton->init(eraserImage, {75,75});
    eraserButton->setPosition({10, (float)(windowSize.y * 0.3f) + 75});    
    eraserButton->onClick = [this, toolIndicatorPtr, eraserImage](){ 
        mTool.setType(ToolType::ERASE); 
        toolIndicatorPtr->setImage(eraserImage);
     };
    addGUIElement(std::move(eraserButton));
    
    //Bucket button
    auto bucketButton = std::make_unique<sk::Button>();     
    bucketButton->init(bucketImage, {75,75});
    bucketButton->setPosition({10, (float)(windowSize.y * 0.3f) + 150});    
    bucketButton->onClick = [this, toolIndicatorPtr, bucketImage](){ 
        mTool.setType(ToolType::BUCKET); 
        toolIndicatorPtr->setImage(bucketImage);
     };
    addGUIElement(std::move(bucketButton));
    
    //Grid button
    auto gridButton = std::make_unique<sk::Button>();    
    sf::Image gridImage;
    if(!gridImage.loadFromFile("assets/grid.png")){
        std::cout << "Could not load image" << '\n';
    }    
    gridButton->init(gridImage, {75,75});
    gridButton->setPosition({10, (float)(windowSize.y * 0.3f) + 225});    
    gridButton->onClick = [this](){
        togglePixelOutlines();
    };
    addGUIElement(std::move(gridButton));
        
    //Submit button
    auto submitButton = std::make_unique<sk::Button>();    
    sf::Image submitImage;
    if(!submitImage.loadFromFile("assets/submit.png")){
        std::cout << "Could not load image" << '\n';
    }    
    submitButton->init(submitImage, {100,100});
    submitButton->setPosition({(float)(windowSize.x * 0.95f) - 60, (float)(windowSize.y * 0.85f)}); 
    submitButton->setBtnOutlineColor(sf::Color(104,98,108));
    submitButton->setBtnOutlineThickness(10);    
    submitButton->onClick = [this, &net](){
        submitArt(net);
    };
    addGUIElement(std::move(submitButton));    
       
}

void CanvasScene::submitArt(NetworkClient& net){
    // convert canvas into sf::Image
    // send to network
    sf::Image image;
    image.create(CANVAS_SIZE, CANVAS_SIZE);

    for(int y = 0; y < CANVAS_SIZE; ++y){
        for(int x = 0; x < CANVAS_SIZE; ++x){
            image.setPixel(x, y, mCanvas[x][y]);
        }
    }
    
    if(!net.attemptImageSubmit(image)){
        std::cout << "Canvas Error: Could not submit art work" << '\n';
    }

    std::cout << "IMAGE UPLOADED SUCCESSFULLY" << '\n';
    
    
}

void CanvasScene::initColorPalette(sk::Window& window){
    const int size = 30.f;
    const float startX = 15.f;
    const float startY = window.getWindowSize().y * 0.7f;
    const float spacing = 3.f;

    // Currently selected colour
    auto selectedColorIcon = std::make_unique<sk::Button>();

    selectedColorIcon->init(
        "",
        {size * 1.5f, size * 1.5f},
        mTool.getColorSelected(),
        sf::Color::White,
        mFont,
        0
    );

    selectedColorIcon->setPosition({
        window.getWindowSize().x * 0.95f,
        window.getWindowSize().y * 0.05f
    });

    selectedColorIcon->setBtnOutlineColor(sf::Color::White);
    selectedColorIcon->setBtnOutlineThickness(3);

    mSelectedColorIcon = selectedColorIcon.get();

    addGUIElement(std::move(selectedColorIcon));
       

    for(int i = 0; i < mColorPalette.size(); ++i){
        auto colorBtn = std::make_unique<sk::Button>();


        sf::Color color = mColorPalette[i];

        colorBtn->init("", {size,size}, color, sf::Color::Transparent, mFont, 0);
        colorBtn->setBtnHoverColor({
                static_cast<sf::Uint8>(color.r * 0.6f),
                static_cast<sf::Uint8>(color.g * 0.6f),
                static_cast<sf::Uint8>(color.b * 0.6f)
        });

        int row = i / 4;
        int col = i % 4;

        colorBtn->setPosition({
            startX + col * (size + spacing),
            startY + row * (size + spacing)
        });

        colorBtn->onClick =[this, color](){
            mTool.setPixelColor(color); 

            if(mSelectedColorIcon) mSelectedColorIcon->setBtnFillColor(color);
            if(mSelectedColorIcon) mSelectedColorIcon->setBtnHoverColor(color);
            
        };

        addGUIElement(std::move(colorBtn));



    }



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

CanvasScene::CanvasScene(sk::Window& window, sk::NetworkClient& net)
: mTool(mGridPixelSize, mGridPixelOutlineSize), mNetClient{net}{
    initButtons(window, net);
    initColorPalette(window);
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

void CanvasScene::bucketStroke(const Input& input){
    if(input.mouseButton1Clicked){
        int startX = mTool.getMouseGridPosition().x;
        int startY = mTool.getMouseGridPosition().y;

        sf::Color currColor = getPixelColor(startX, startY);
        sf::Color newColor = mTool.getColorSelected();

        if(newColor == currColor) return;

        std::queue<sf::Vector2i> q;

        q.push({startX, startY});

        while(!q.empty()){
            sf::Vector2i p = q.front();
            q.pop();

            int x = p.x;
            int y = p.y;

            // check boundarys of canvas first
            if(x < 0 || y < 0 || x >= CANVAS_SIZE || y >= CANVAS_SIZE)
                continue;

            if(getPixelColor(x, y) != currColor)
                continue;

            setPixelColor(x, y, newColor);

            // all neighbours
            q.push({x + 1, y});
            q.push({x - 1, y});
            q.push({x, y + 1});
            q.push({x, y - 1});


        }
    }

}

void CanvasScene::update(const Input& input, sk::Window& window, float dt, float elapsed){ 
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
            case BUCKET:
                bucketStroke(input);
                break;
            default:
                break;
        }

    }


    cameraPan(input, window);
    cameraZoom(input, window);

    Scene::update(input, window, dt, elapsed);
}

void CanvasScene::cameraZoom(const Input& input, sk::Window& window){
    if(input.scrollWheelChange != 0.f){
        float zFactor = std::pow(1.1f, -input.scrollWheelChange);
        if(zFactor)
        window.zoomCamera(zFactor);
    }
}

void CanvasScene::cameraPan(const Input& input, sk::Window& window){
    if(input.mouseButton2Clicked){
        mIsPanning = true;
        mLastMousePos = input.mousePositionWindow;
    }

    if(!input.mouseButton2Pressed){
        mIsPanning = false;
        return;
    }

    
    if(mIsPanning){
        sf::Vector2i currMousePos = input.mousePositionWindow;
        // delta (difference between the last and curr mouse pos)
        sf::Vector2f d = window.mapPixeltoCoords(mLastMousePos) - window.mapPixeltoCoords(currMousePos);
    
        window.moveCamera(d);

        mLastMousePos = currMousePos;
    
    }
}




void CanvasScene::draw(sk::Window& window){
    window.changeToWorldView();
    window.getRenderWindow()->draw(mCanvasBuffer);

    mTool.draw(window);

    window.changeToGUIView();
    Scene::draw(window);
}

CanvasScene::~CanvasScene(){
}
