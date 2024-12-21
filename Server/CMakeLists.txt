cmake_minimum_required(VERSION 3.16)
project(Server LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Server
main.cpp
BaseOld.cpp
BotsServer.cpp
FeedServer.cpp
FoodServer.cpp
GameEngine.cpp
HeroServer.cpp
ObjectsServer.cpp
PiecesServer.cpp
ThornServer.cpp
MessageServer.cpp
)
target_link_libraries(Server PRIVATE sfml-network)
target_compile_features(Server PRIVATE cxx_std_17)
target_include_directories(Server  PUBLIC ..\\jsonLib\\include)

install(TARGETS Server)