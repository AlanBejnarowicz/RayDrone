cmake_minimum_required(VERSION 3.10)
project(MyRaylibGame)

set(CMAKE_CXX_STANDARD 17)

# Find Raylib
find_package(raylib REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)

# Automatically add all source files in the Tools directory
file(GLOB TOOLS_SOURCES "Tools/*.cpp")
file(GLOB OBJECTS_SOURCES "Objects/*.cpp")
file(GLOB_RECURSE OBJECTS_RECURSE_SOURCES "Objects/**/*.cpp")
set(SOURCES ${TOOLS_SOURCES} ${OBJECTS_SOURCES} ${OBJECTS_RECURSE_SOURCES})

add_executable(MyRaylibGame main.cpp ${SOURCES})
target_include_directories(MyRaylibGame PRIVATE Tools Objects ${SDL2_INCLUDE_DIRS})
target_link_libraries(MyRaylibGame raylib SDL2)
