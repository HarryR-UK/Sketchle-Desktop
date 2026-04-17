#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include "../Scene.h"
#include "../../Window.h"
#include "../../gui/Button.h"
#include <array>

#define CANVAS_SIZE 65

namespace sk {
    class CanvasScene : public Scene{
        private:
            sf::Font mFont;
            
            const sf::Vector2u mCanvasSize = {CANVAS_SIZE, CANVAS_SIZE};
            const float mGridPixelSize = 3.f;

            std::array<std::array<sf::Color, CANVAS_SIZE>, CANVAS_SIZE> mCanvas;

            sf::RectangleShape mColorPixel;
            sf::RectangleShape mCursorPixelSelect;

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
