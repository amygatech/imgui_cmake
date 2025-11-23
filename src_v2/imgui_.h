// imgui_.h
#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
using namespace gl;

#include <GLFW/glfw3.h>

//ImGui RAII wrapper + Docking On/Off
//This includes two public methods:
//enable_docking()

namespace imguiwrap {

struct imgui_context
{
    imgui_context(bool docking)
    {
        // Create context
        IMGUI_CHECKVERSION();
        ctx = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        if (docking)
            enable_docking();
        else
            disable_docking();

        ImGui::StyleColorsDark();
    }

    ~imgui_context()
    {
        ImGui::DestroyContext(ctx);
    }

    // ---- Docking controls ----
    static void enable_docking()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    static void disable_docking()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;
    }

    ImGuiContext* ctx = nullptr;
};


struct glfw_opengl
{
    imgui_context ctx;

    glfw_opengl(GLFWwindow* window, bool docking)
        : ctx(docking)
    {
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    ~glfw_opengl()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    template<typename Fn>
    void render(GLFWwindow* window, Fn&& draw_fn)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        draw_fn();   // calls your main_view

        ImGui::Render();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
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

} // namespace imguiwrap
