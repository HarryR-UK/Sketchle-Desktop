#ifndef SCENE_H
#define SCENE_H

#include "../gui/GUIElement.h"
#include "../Input.h"
#include <memory>
#include <vector>
namespace sk {
    class Scene{
        private:
            std::vector<std::unique_ptr<GUIElement>> mGUIElements = {};
 

        public:
            void draw(sk::Window& window);
            void update(const Input& input);
            void addGUIElement(std::unique_ptr<GUIElement> e);

            Scene();
            virtual ~Scene(); // delete all GUIElements!!!!

    };
}


#endif //!SCENE_H
