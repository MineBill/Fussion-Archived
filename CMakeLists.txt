cmake_minimum_required(VERSION 3.24)
project(Core VERSION 0.0.1)

include(CMake/Warnings.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Core)
add_subdirectory(Sandbox)
