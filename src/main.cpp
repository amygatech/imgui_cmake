#include "glfw.h"
#include "imgui_.h"
#include "main_view.h"

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
#include <exception>
#include <iostream>

int main()
{
    try {
        glfw::scoped_terminate glfw_ctx;  // calls glfwInit()/glfwTerminate()

        auto main_win = glfw::make_window(1280, 720, "Main");
        glfwMakeContextCurrent(main_win.get());

        // init glbinding
        glbinding::initialize([](const char* name) {
            return glfwGetProcAddress(name);
        });

        using namespace gl;
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

        // true = enable docking + multi viewport
        imgui::glfw_opengl imgui_ctx(main_win.get(), true);
        main_view v;

        while (!glfwWindowShouldClose(main_win.get())) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
            imgui_ctx.render(main_win.get(), v);
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 3;
    }
}
