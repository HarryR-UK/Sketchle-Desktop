cmake_minimum_required(VERSION 3.16)
project(Sketchle)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include(FetchContent) # SFMLv2.6 
FetchContent_Declare( 
    SFML 
    GIT_REPOSITORY https://github.com/SFML/SFML.git 
    GIT_TAG 2.6.x 
) 

FetchContent_MakeAvailable(SFML) 

if(WIN32)
    FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_7_1
    )

    set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(curl)

    set(CURL_LIB libcurl)
else()
    find_package(CURL REQUIRED)
    set(CURL_LIB CURL::libcurl)
endif()

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

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${CURL_LIB}
    sfml-graphics
    sfml-window
    sfml-system
)
