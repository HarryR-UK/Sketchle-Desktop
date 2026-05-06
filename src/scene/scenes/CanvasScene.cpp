//
// Author: Harry Rotheram and Finn O'Hare

#include "CanvasScene.h"
#include "CanvasTools/ToolType.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

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
    toolIndicator->init(brushImage, {90,90});
    toolIndicator->setPosition({(float)(windowSize.x*0.92f), (float)(windowSize.y * 0.2f)});
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
        
    //Submit button + message
    auto submitText = std::make_unique<sk::Button>();
    submitText->init(mSubmitMsg, {100,100}, sf::Color::Transparent, sf::Color(255,0,0), mFont, 30);
    submitText->setPosition({(float)(windowSize.x * 0.4f) - 100, (float)(windowSize.y * 0.4f)}); 
    submitText->setBtnOutlineColor(sf::Color::Transparent);
    submitText->setBtnOutlineThickness(0);    
    submitText->setTxtOutlineColor(sf::Color::Black);
    submitText->setTxtOutlineThickness(2);    
    sk::Button* submitTxtPtr = submitText.get();   
    addGUIElement(std::move(submitText));
    
    auto submitButton = std::make_unique<sk::Button>();    
    sf::Image submitImage;
    if(!submitImage.loadFromFile("assets/submit.png")){
        std::cout << "Could not load image" << '\n';
    }    
    submitButton->init(submitImage, {100,100});
    submitButton->setPosition({(float)(windowSize.x * 0.95f) - 60, (float)(windowSize.y * 0.85f)}); 
    submitButton->setBtnOutlineColor(sf::Color(104,98,108));
    submitButton->setBtnOutlineThickness(10);    
    submitButton->onClick = [this, &net, submitTxtPtr, windowSize](){
        if(submitArt(net)){
            clearCanvas();
            if(!mIsArtSubmitted){
                mIsArtSubmitted = true;
                submitTxtPtr->setPosition({(float)(windowSize.x * 0.4f) - 100, (float)(windowSize.y * 0.4f)}); 
                mSubmitMsg = "Sketch uploaded!"; 
            }else{
                submitTxtPtr->setPosition({(float)(windowSize.x * 0.3f) - 100, (float)(windowSize.y * 0.4f)}); 
                mSubmitMsg = "Sketch already uploaded!";
            }
        }
        submitTxtPtr->setTxt(net.getServerResponse());
    };
    addGUIElement(std::move(submitButton));    
    
    
    net.attemptGetDailyTheme();
    std::string theme = "Today's Theme: " + net.getServerResponse();

    auto dailyThemeText = std::make_unique<sk::Button>();
    dailyThemeText->init(theme, {100,100}, sf::Color::Transparent, sf::Color(180, 100, 255), mFont, 50);
    dailyThemeText->setPosition({(float)(windowSize.x * 0.5f) - 100, (float)(windowSize.y * 0.01f)}); 
    dailyThemeText->setBtnOutlineColor(sf::Color::Transparent);
    dailyThemeText->setBtnOutlineThickness(0);    
    dailyThemeText->setTxtOutlineColor(sf::Color::Black);
    dailyThemeText->setTxtOutlineThickness(2);    
    addGUIElement(std::move(dailyThemeText));


    /*
    auto brushSizeSlider = std::make_unique<sk::Slider>();
    brushSizeSlider->init(100, sf::Color::Black, sf::Color::White);
    brushSizeSlider->setPosition({(float)windowSize.x * 0.2f, (float)windowSize.y * 0.2f});

    addGUIElement(std::move(brushSizeSlider));
    */
    
    //Hue slider + text
    auto hueSlider = std::make_unique<sk::Slider>();
    hueSlider->init(150, sf::Color::Black, sf::Color::White, 0, 360);
    hueSlider->setPosition({(float)windowSize.x * 0.1f, (float)windowSize.y * 0.75f});
    hueSlider->setCurrentValue(360);
    mHueSlider = hueSlider.get();
    addGUIElement(std::move(hueSlider));
    
    auto hueText = std::make_unique<sk::Button>();
    hueText->init("Hue: ", {50,50}, sf::Color::Transparent, sf::Color::White, mFont, 30);
    hueText->setPosition({(float)(windowSize.x * 0.2f), (float)(windowSize.y * 0.72f)}); 
    hueText->setBtnOutlineColor(sf::Color::Transparent);
    hueText->setBtnOutlineThickness(0);    
    hueText->setTxtOutlineColor(sf::Color::Black);
    hueText->setTxtOutlineThickness(2);
    mHueText = hueText.get();
    addGUIElement(std::move(hueText));

    //Saturation slider + text
    auto satSlider = std::make_unique<sk::Slider>();
    satSlider->init(150, sf::Color::Black, sf::Color::White, 0.f, 1.f);
    satSlider->setPosition({(float)windowSize.x * 0.1f, (float)windowSize.y * 0.81f});
    satSlider->setCurrentValue(1.0f);
    mSatSlider = satSlider.get();
    addGUIElement(std::move(satSlider));
    
    auto satText = std::make_unique<sk::Button>();
    satText->init("Sat: ", {50,50}, sf::Color::Transparent, sf::Color::White, mFont, 30);
    satText->setPosition({(float)(windowSize.x * 0.2f), (float)(windowSize.y * 0.78f)}); 
    satText->setBtnOutlineColor(sf::Color::Transparent);
    satText->setBtnOutlineThickness(0);    
    satText->setTxtOutlineColor(sf::Color::Black);
    satText->setTxtOutlineThickness(2);
    mSatText = satText.get();
    addGUIElement(std::move(satText));
    
    //Value slider + text
    auto valSlider = std::make_unique<sk::Slider>();
    valSlider->init(150, sf::Color::Black, sf::Color::White, 0.f, 1.f);
    valSlider->setPosition({(float)windowSize.x * 0.1f, (float)windowSize.y * 0.87f});
    valSlider->setCurrentValue(1.0f);
    mValSlider = valSlider.get();
    addGUIElement(std::move(valSlider));
    
    auto valText = std::make_unique<sk::Button>();
    valText->init("Val: ", {50,50}, sf::Color::Transparent, sf::Color::White, mFont, 30);
    valText->setPosition({(float)(windowSize.x * 0.2f), (float)(windowSize.y * 0.84f)}); 
    valText->setBtnOutlineColor(sf::Color::Transparent);
    valText->setBtnOutlineThickness(0);    
    valText->setTxtOutlineColor(sf::Color::Black);
    valText->setTxtOutlineThickness(2);
    mValText = valText.get();
    addGUIElement(std::move(valText));
       
}

bool CanvasScene::submitArt(NetworkClient& net){
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
        return false;
    }

    std::cout << "IMAGE UPLOADED SUCCESSFULLY" << '\n';
    return true;
    
    
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
        {size * 3.0f, size * 3.0f},
        mTool.getColorSelected(),
        sf::Color::White,
        mFont,
        0
    );

    selectedColorIcon->setPosition({
        window.getWindowSize().x * 0.92f,
        window.getWindowSize().y * 0.08f
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
        
        // update the value of h/s/v sliders instead of directly changing colour (will be automatically updated)
        colorBtn->onClick =[this, color](){
            sf::Vector3f hsv = mColorUtil.rgbToHsv(color);
            float h = hsv.x;
            float s = hsv.y;
            float v = hsv.z;

            if(mHueSlider){
                mHueSlider->setCurrentValue(h);
            }
            if(mSatSlider){
                mSatSlider->setCurrentValue(s);
            }
            if(mValSlider){
                mValSlider->setCurrentValue(v);
            }
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
    
    // always set colour to slider value
    if(mHueSlider && mSatSlider && mValSlider){
        float h = mHueSlider->getCurrentValue();
        float s = mSatSlider->getCurrentValue();
        float v = mValSlider->getCurrentValue();
        sf::Color c = mColorUtil.hsvToRgb(h, s, v);
        mTool.setPixelColor(c);
        if(mSelectedColorIcon){
            mSelectedColorIcon->setBtnFillColor(c);
            mSelectedColorIcon->setBtnHoverColor(c);
        }
        // round values for cleaner output
        auto cutFloat = [](float val, int precision = 2){
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(precision) << val;
            return ss.str();
        };
        // set slider text to current hsv values
        mHueText->setTxt("Hue: " + cutFloat(h, 0));
        mSatText->setTxt("Sat: " + cutFloat(s, 2));          
        mValText->setTxt("Val: " + cutFloat(v, 2));
    }
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

    if(!mIsArtSubmitted){
        window.getRenderWindow()->draw(mCanvasBuffer);
    }

    mTool.draw(window);

    window.changeToGUIView();
    Scene::draw(window);
}

CanvasScene::~CanvasScene(){
}
