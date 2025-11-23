cmake_minimum_required(VERSION 3.14)
add_executable(viwer_app "")
target_sources(viwer_app
  PRIVATE
    "main.cpp"
  PUBLIC
    "glfw.h"
    "imgui_.h"
    "main_view.h")
target_include_directories(viwer_app
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_definitions(viwer_app
  PUBLIC _USE_MATH_DEFINES _CRT_SECURE_NO_WARNINGS
  PRIVATE DOCTEST_CONFIG_DISABLE
)
target_compile_features(viwer_app PUBLIC cxx_std_20)
target_link_libraries(viwer_app asio::asio imgui::glfw imgui::opengl3)

if(MSVC)
  target_link_options(viwer_app
    PRIVATE
      "/ENTRY:mainCRTStartup" "/SUBSYSTEM:WINDOWS")
endif()
