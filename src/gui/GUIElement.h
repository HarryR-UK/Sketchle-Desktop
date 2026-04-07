#ifndef GUIELEMENT_H

#include "../Window.h"


// class should be inherited by GUI elements
namespace sk {
    class GUIElement{
        private:

        private:

        public:

        public:
            virtual void update();
            virtual void draw(sk::Window& window);
            virtual ~GUIElement();

    };

}

#endif // !GUIELEMENT_H
