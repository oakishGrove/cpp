cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)

# Below line is for using C++20 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fmodules-ts")

# Our project name
project (gamesDev)

add_executable(gamesDev main.cpp game/Game.h game/Game.cpp game/actors/actor/Actor.cpp game/actors/actor/Actor.h game/actors/ball/Ball.cpp game/actors/ball/Ball.h game/actors/actor/Visitor.h game/actors/pad/Pad.cpp game/actors/pad/Pad.h game/actors/crums/Crums.cpp game/actors/crums/Crums.h)

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Linking SDL2 library with our project.
target_link_libraries(gamesDev ${SDL2_LIBRARIES})
