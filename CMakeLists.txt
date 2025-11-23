cmake_minimum_required (VERSION 3.13)
project(gui_test_app VERSION 1.0 LANGUAGES CXX)
cmake_policy(SET CMP0074 NEW)


add_subdirectory(extern)
add_subdirectory(test_dock)
add_subdirectory(test_plain)
add_subdirectory(src)
add_subdirectory(src_v2)
