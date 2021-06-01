cmake_minimum_required (VERSION 3.15)
project(imgui_cmake VERSION 1.0 LANGUAGES CXX)
cmake_policy(SET CMP0074 NEW)

# add third party libs
add_subdirectory(3pp)
# My example project
add_subdirectory(example_src)