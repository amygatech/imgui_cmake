cmake_minimum_required(VERSION 3.14)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")
add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_subdirectory(glbinding EXCLUDE_FROM_ALL)
set(OPTION_BUILD_TOOLS OFF CACHE INTERNAL "")
set(OPTION_BUILD_EXAMPLES OFF CACHE INTERNAL "")



add_library(imgui)
target_sources(imgui
  PUBLIC
    imgui/imgui.h
  PRIVATE
    imgui/imconfig.h
    imgui/imgui_internal.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
)
add_library(imgui::imgui ALIAS imgui)
target_include_directories(imgui PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
  $<INSTALL_INTERFACE:include>
)

add_library(imgui_glfw)
target_sources(imgui_glfw
  PUBLIC
    imgui/examples/imgui_impl_glfw.h
  PRIVATE
    imgui/examples/imgui_impl_glfw.cpp
)
add_library(imgui::glfw ALIAS imgui_glfw)
target_include_directories(imgui_glfw PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(imgui_glfw PUBLIC imgui glfw)
target_compile_definitions(imgui_glfw
                             PUBLIC GLFW_INCLUDE_NONE)

add_library(imgui_opengl3)
target_sources(imgui_opengl3
  PUBLIC
    imgui/examples/imgui_impl_opengl3.h
  PRIVATE
    imgui/examples/imgui_impl_opengl3.cpp
)
add_library(imgui::opengl3 ALIAS imgui_opengl3)
target_include_directories(imgui_opengl3 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(imgui_opengl3
                             PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLBINDING)
target_link_libraries(imgui_opengl3 PUBLIC imgui glbinding)
