cmake_minimum_required(VERSION 3.15)
project(entt VERSION 0.1)

add_library(entt entt.hpp dummy.cpp)

target_include_directories(entt SYSTEM PUBLIC .)

