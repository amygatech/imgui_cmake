// glfw.h
#pragma once

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>
#include <memory>
#include <cstdio>

//Always requests modern 3.3 Core
//Uses RAII safely

namespace glfwx {

inline void set_error_callback()
{
    glfwSetErrorCallback([](int error, const char* desc) {
        std::fprintf(stderr, "[GLFW] Error %d: %s\n", error, desc);
    });
}

struct scoped_glfw
{
    scoped_glfw()
    {
        set_error_callback();
        if (!glfwInit()) {
            std::fprintf(stderr, "[GLFW] glfwInit() failed\n");
            ok = false;
        } else {
            ok = true;
        }
    }

    ~scoped_glfw()
    {
        if (ok)
            glfwTerminate();
    }

    bool ok = false;
};

struct window_deleter {
    void operator()(GLFWwindow* w) const {
        if (w) glfwDestroyWindow(w);
    }
};

using window_ptr = std::unique_ptr<GLFWwindow, window_deleter>;

inline window_ptr make_window_33(const char* title, int w, int h)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* win = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!win)
        std::fprintf(stderr, "[GLFW] glfwCreateWindow() failed\n");

    return window_ptr(win);
}

} // namespace glfwx
