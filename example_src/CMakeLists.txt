cmake_minimum_required(VERSION 3.15)
add_executable(my_example "")
target_sources(my_example
  PRIVATE
    src/main.cpp
)
target_include_directories(my_example
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)
target_compile_definitions(my_example
    PUBLIC _USE_MATH_DEFINES _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
target_link_libraries(my_example imgui::glfw imgui::opengl3)
if (UNIX)
    include(CheckPIESupported)
    check_pie_supported()
    target_link_libraries(my_example stdc++fs)
    set_property(TARGET my_example PROPERTY POSITION_INDEPENDENT_CODE FALSE)
    target_compile_options(my_example PRIVATE -Wno-deprecated)
endif(UNIX)

target_compile_features(my_example PUBLIC cxx_std_17)
target_include_directories(my_example PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
    PRIVATE src ${OpenCV_INCLUDE_DIRS}
)

if(MSVC)
    target_compile_options(my_example PUBLIC "/permissive-" "/Zc:__cplusplus")
    set_target_properties(my_example PROPERTIES
        LINK_FLAGS "/ignore:4099 /ignore:4199")
endif()
