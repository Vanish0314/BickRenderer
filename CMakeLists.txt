# C++版本要求 c++17
cmake_minimum_required(VERSION 3.15)
project(BickRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")


set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(3rd/glfw)
add_subdirectory(3rd/glm)
include_directories(${CMAKE_SOURCE_DIR}/3rd/glm)
include_directories(${CMAKE_SOURCE_DIR}/3rd/assimp/include)

add_subdirectory(Source)