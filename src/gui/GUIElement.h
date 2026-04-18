//
// Author: Harry Rotheram
//
//
#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "../Window.h"
#include "../Input.h"
#include <functional>

// class should be inherited by GUI elements
namespace sk {
    class GUIElement{
        private:

        private:

        public:

        public:
            virtual ~GUIElement()= default;
            virtual void update(const Input& input);
            virtual void update(const Input& input, float dt, float elapsed);
            virtual void draw(sk::Window& window);
            

    };

}

#endif // !GUIELEMENT_H
