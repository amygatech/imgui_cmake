#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

#include <memory>
#include <stdexcept>

namespace imgui {

struct destroy_context {
    void operator()(ImGuiContext* c) const noexcept
    {
        ImGui::DestroyContext(c);
    }
};

using scoped_context = std::unique_ptr<ImGuiContext, destroy_context>;

inline scoped_context make_context(bool enable_docking)
{
    IMGUI_CHECKVERSION();
    auto* ctx = ImGui::CreateContext();
    if (!ctx) {
        throw std::runtime_error("ImGui::CreateContext() failed");
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (enable_docking) {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    ImGui::StyleColorsDark();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    return scoped_context(ctx);
}

struct glfw_opengl {
    scoped_context ctx;

    glfw_opengl(GLFWwindow* window, bool enable_docking)
        : ctx(make_context(enable_docking))
    {
        // Note: glbinding::initialize() must be done in main BEFORE constructing this
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    ~glfw_opengl()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    template <typename Fn>
    void render(GLFWwindow* window, Fn&& fn)
    {
        using namespace gl;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        std::forward<Fn>(fn)();

        ImGui::Render();
        int display_w = 0, display_h = 0;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(window);
    }
};

} // namespace imgui
