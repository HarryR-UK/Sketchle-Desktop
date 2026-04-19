# SKETCHLE-DESKTOP


## About

Sketchle Desktop works in conjunction with the ![sketchle web server](https://github.com/nicoloveneziale/sketchle)

This allows containment of two functions to allow a more specialised focus on different features: 

- The live web server allows the user to make an account, like, report and review other art pieces
- The desktop application provides a login interface and a canvas with various tools and camera panning that allows the user to paint their desired art based on the daily theme


### Libraries

The number of external libraries used in this C++ application were attempted to keep as minimal as possible.

For the Drawing of pixels to the screen as well as some media functions such as window creation and input handling, SFMLv2.6 was used.
This was to ensure full freedom and control as a developer, but also ensures that the program can be easily made as cross platform.

The networking functionality will use Curl as a means of communicating with the backend server. This will allow automatically handling of TLS, whilst allowing control over the content that will be sent across a network. This will be used to send POST and GET requests as well as receiving responses from the server itself. 


## Instructions (How To Use)

A user can use this application by ensuring they have an account already signed up via the webserver. Once this is done, a user can login at the home page on the desktop application.

Once complete, the user will be presented with an empty canvas and a set of colors and tools that allow the user to display their creativity given the daily theme.

As soon as the user is happy with their drawing a simple tap of the submit button will let the user know they have send their art work. As this artwork is only once a day, the user cannot submit more than one.

## Instructions (How to Compile and Run)
As this program is made in C++, CMake is used as a compilation tool. This allows for library paths to be found easily. SFMLv2.6 is automatically fetched via CMake. 

### MacOS
1. Ensure homebrew is installed (or any preferred package manager). This can be installed ![here](https://brew.sh/) 
2. Once homebrew is properly setup use the following commands
    ```sh
    brew upgrade
    brew install cmake make curl freetype
    ```
3. Then to compile and run the application ensure you are working in the project root directory. Run the following commands:
```sh
    cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix)"
    cd build && make
    cd bin/
    ./Sketchle
```

### Linux
1. Ensure your package manager is up to date:
`sudo apt update`
2.Ensure all packages are installed:
```sh
sudo apt install cmake build-essential \
libcurl4-openssl-dev \
libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
libudev-dev libfreetype6-dev libopenal-dev libvorbis-dev libflac-dev
```
3. Then to compile and run the application ensure you are working in the project root directory. Run the following commands:
```sh
    cmake -S . -B build
    cd build && make
    cd bin/
    ./Sketchle
```

### Windows
1. To compile and run the application ensure you are working in the project root directory. Run the following commands:
```sh
    cmake -S . -B build
    cd build && cmake --build .
    cd bin
    .\Sketchle
```

