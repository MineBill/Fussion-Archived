cmake_minimum_required(VERSION 3.15)
project(stb)

add_library(stb
        include/stb_image.h
        stb_image.c
        )

target_include_directories(stb PUBLIC include)