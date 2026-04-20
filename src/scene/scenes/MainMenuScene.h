//
// Author: Harry Rotheram
//
//
#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../Scene.h"
#include "../../Window.h"
#include "../../gui/Button.h"
#include "../../gui/Textbox.h"
#include <SFML/Graphics/Font.hpp>
#include <atomic>
#include "../../networking/NetworkClient.h"
#include "../SceneManager.h"

namespace sk {
    class MainMenuScene : public Scene{
        private:
            sf::Font mFont;
            sk::NetworkClient& mNetClient;
            bool mChangeToCanvas{false};
            sk::SceneManager& mSceneManager;
            std::string mErrResponse = "";
        private:
        public:
        public:
            MainMenuScene(sk::Window& window, sk::NetworkClient& net, sk::SceneManager& scManager);
            void update(const Input& input, sk::Window& window, float dt, float elapsed)override;
          
    };

}

#endif // !MAINMENUSCENE_H
