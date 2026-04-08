#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "../Window.h"
#include "../Input.h"

// class should be inherited by GUI elements
namespace sk {
    class GUIElement{
        private:

        private:

        public:

        public:
            virtual ~GUIElement();
            virtual void update(const Input& input);
            virtual void draw(sk::Window& window);


    };

}

#endif // !GUIELEMENT_H
