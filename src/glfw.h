#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#include <cstdio>

namespace glfw {

inline void set_error_callback()
{
    glfwSetErrorCallback([](int error, const char* description) {
        std::fprintf(stderr, "GLFW error %d: %s\n", error, description);
    });
}

struct scoped_terminate
{
    scoped_terminate()
    {
        set_error_callback();
        if (!glfwInit()) {
            throw std::runtime_error("glfwInit() failed");
        }
    }

    ~scoped_terminate()
    {
        glfwTerminate();
    }

    scoped_terminate(const scoped_terminate&) = delete;
    scoped_terminate& operator=(const scoped_terminate&) = delete;
};

struct destroy_window {
    void operator()(GLFWwindow* w) const noexcept
    {
        if (w) glfwDestroyWindow(w);
    }
};

using scoped_window = std::unique_ptr<GLFWwindow, destroy_window>;

inline scoped_window make_window(int width, int height, const char* title)
{
    // Match your working ImGui example:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // DO NOT set core profile for 3.0 on Windows (3.2+ only)
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    // For macOS we must use 3.2 core + forward compat
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* win = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!win) {
        throw std::runtime_error("glfwCreateWindow() failed");
    }
    return scoped_window(win);
}

} // namespace glfw
