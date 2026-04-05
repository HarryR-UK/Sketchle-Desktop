#ifndef SCENE_H
#define SCENE_H

#include "../gui/GUIElement.h"
#include <memory>
#include <vector>
namespace sk {
    class Scene{
        private:
            std::vector<std::unique_ptr<GUIElement>> mGUIElements = {};
 

        public:
            virtual void update();
            virtual void draw(sk::Window& window);

            Scene();
            virtual ~Scene(); // delete all GUIElements!!!!

    };
}


#endif //!SCENE_H
