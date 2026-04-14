cmake_minimum_required(VERSION 3.16)
project(Sketchle)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/EventHandler.cpp
    src/Input.cpp

    src/gui/GUIElement.cpp
    src/gui/Button.cpp

    src/scene/Scene.cpp
    src/scene/SceneManager.cpp

    src/scene/scenes/MainMenuScene.cpp


    src/networking/NetworkClient.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
