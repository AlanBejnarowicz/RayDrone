cmake_minimum_required(VERSION 3.10)
project(MyRaylibGame)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

# Automatically add all source files in the Tools directory
file(GLOB TOOLS_SOURCES "Tools/*.cpp")

add_executable(MyRaylibGame main.cpp ${TOOLS_SOURCES})
target_include_directories(MyRaylibGame PRIVATE Tools)
target_link_libraries(MyRaylibGame raylib)