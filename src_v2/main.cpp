// main.cpp
#include "glfw.h"
#include "imgui_.h"
#include "main_view.h"

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
using namespace gl;

int main()
{
    glfwx::scoped_glfw glfw;

    if (!glfw.ok) return 1;

    auto window = glfwx::make_window_33("Docking Test", 1280, 720);
    if (!window) return 1;

    glfwMakeContextCurrent(window.get());
    glbinding::initialize(glfwGetProcAddress);

    // ---- Toggle docking here ----
    bool enable_docking = true;   // <---- CHANGE THIS
    // ----------------------------

    imguiwrap::glfw_opengl ui(window.get(), enable_docking);

    main_view view;

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        ui.render(window.get(), [&]{ view(); });
    }

    return 0;
}
