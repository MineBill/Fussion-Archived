# We use 3.25 because it introduced SYSTEM options for FetchContent_Declare
cmake_minimum_required(VERSION 3.24)
project(Fussion VERSION 0.0.1)

include(FetchContent)
include(CMake/Warnings.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(RENDER_API "OpenGL")
add_definitions(-DFSN_USE_ASSERTIONS)
add_definitions(-DFSN_ENABLE_PROFILING)

add_subdirectory(ThirdParty)
add_subdirectory(Fussion)
add_subdirectory(Editor)
