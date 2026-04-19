//
//
// Author: Harry Rotheram

#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include "../Scene.h"
#include "../../Window.h"
#include "../../gui/Button.h"
#include "CanvasTools/Tool.h"
#include <array>
#include <vector>
#include"../../global.h"
#include <queue>

#define QUAD_POINT_COUNT 4

namespace sk {
    class CanvasScene : public Scene{
        private:
            sf::Font mFont;
            
            const sf::Vector2u mCanvasSize = {CANVAS_SIZE, CANVAS_SIZE};
            const float  mDefaultPixelSize = 9.f;
            const float mDefaultOutlineSize = 1.f;

            float mGridPixelSize = mDefaultPixelSize;
            float mGridPixelOutlineSize = mDefaultOutlineSize;

            std::array<std::array<sf::Color, CANVAS_SIZE>, CANVAS_SIZE> mCanvas;
            sf::VertexArray mCanvasBuffer;
            sf::Vector2f mCanvasPos;

            sf::RectangleShape mColorPixel;
            sf::RectangleShape mCursorPixelSelect;

            sk::Tool mTool;

            bool mShowPixelOutlines = true;

            std::vector<sf::Color> mColorPalette = {
                sf::Color::Black,
                sf::Color::White,
                sf::Color::Red,
                sf::Color::Green,
                sf::Color::Blue,
                sf::Color::Yellow,
                sf::Color(255, 165, 0), // orange
                sf::Color(128, 0, 128),  // purple
                sf::Color(139,69,19) // brown
            };


            sk::Button* mSelectedColorIcon;

        private:
            void initButtons(sk::Window& window);
            void initCanvas(sk::Window& window);
            void initColorPalette(sk::Window& window);
            void setPixelColor(int x, int y, sf::Color color);
            void togglePixelOutlines();
            void rebuildCanvas();
            const sf::Color& getPixelColor(int x, int y);
            void brushStroke(const Input& input);
            void eraseStroke(const Input& input);
            void bucketStroke(const Input& input);

            void clearCanvas();


        public:
            CanvasScene(sk::Window& window);
            ~CanvasScene();
            void update(const Input& input) override;
            void draw(sk::Window& window) override;
    };

}



#endif //!CANVASSCENE_H
