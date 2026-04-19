cmake_minimum_required(VERSION 3.16)
project(Sketchle)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include(FetchContent)


# SFMLv2.6
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(SFML)

find_package(CURL REQUIRED)


add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/EventHandler.cpp
    src/Input.cpp

    src/gui/GUIElement.cpp
    src/gui/Button.cpp
    src/gui/Textbox.cpp

    src/scene/Scene.cpp
    src/scene/SceneManager.cpp

    src/scene/scenes/MainMenuScene.cpp
    src/scene/scenes/CanvasScene.cpp

    src/scene/scenes/CanvasTools/Tool.cpp
   

    src/networking/NetworkClient.cpp
)


# include .dll files in the exe
if (WIN32)
    add_custom_command(TARGET Sketchle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Sketchle>
        $<TARGET_FILE_DIR:Sketchle>
        COMMAND_EXPAND_LISTS
        )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    CURL::libcurl
    sfml-graphics
    sfml-window
    sfml-system
)
