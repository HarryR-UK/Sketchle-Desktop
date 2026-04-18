#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include "../Scene.h"
#include "../../Window.h"
#include "../../gui/Button.h"
#include "CanvasTools/Tool.h"
#include <array>
#include"../../global.h"

namespace sk {
    class CanvasScene : public Scene{
        private:
            sf::Font mFont;
            
            const sf::Vector2u mCanvasSize = {CANVAS_SIZE, CANVAS_SIZE};
            const float mGridPixelSize = 3.f;
            const float mGridPixelOutlineSize = 1.f;

            std::array<std::array<sf::Color, CANVAS_SIZE>, CANVAS_SIZE> mCanvas;

            sf::RectangleShape mColorPixel;
            sf::RectangleShape mCursorPixelSelect;

            sk::Tool mTool;

        private:
            void initButtons(sk::Window& window);
            void initCanvas(sk::Window& window);

        public:
            CanvasScene(sk::Window& window);
            ~CanvasScene();
            void update(const Input& input) override;
            void draw(sk::Window& window) override;
    };

}



#endif //!CANVASSCENE_H
