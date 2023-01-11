cmake_minimum_required(VERSION 3.25)
project(Fussion VERSION 0.0.1)

include(FetchContent)
include(CMake/Warnings.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Fussion)
add_subdirectory(Editor)
