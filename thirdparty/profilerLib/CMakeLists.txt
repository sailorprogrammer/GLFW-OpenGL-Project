cmake_minimum_required(VERSION 3.16.4.0)
project(profilerLib)


add_library(profilerLib INTERFACE)
target_include_directories(profilerLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
