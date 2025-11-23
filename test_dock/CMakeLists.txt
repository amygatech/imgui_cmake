cmake_minimum_required(VERSION 3.14)
add_executable(viwer_docking "")
target_sources(viwer_docking
  PUBLIC
    main.cpp
)
target_include_directories(viwer_docking
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(viwer_docking
    PUBLIC _USE_MATH_DEFINES _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
target_link_libraries(viwer_docking asio::asio fmt::fmt 
                              imgui::glfw imgui::opengl3)
if (UNIX)
    include(CheckPIESupported)
    check_pie_supported()
    target_link_libraries(viwer_docking stdc++fs atomic)
    set_property(TARGET viwer_docking PROPERTY POSITION_INDEPENDENT_CODE FALSE)
    target_compile_options(viwer_docking PRIVATE -Wno-deprecated -Wno-dev)
endif(UNIX)

target_compile_features(viwer_docking PUBLIC cxx_std_17)
target_include_directories(viwer_docking PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(viwer_docking PUBLIC "/permissive-" "/Zc:__cplusplus")
    target_link_libraries(viwer_docking Delayimp.lib)
    target_link_options(viwer_docking PRIVATE
        "/ignore:4099" "/ignore:4199" "/ENTRY:mainCRTStartup" "/SUBSYSTEM:WINDOWS"
    )
endif()
