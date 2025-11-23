// main_view.h
#pragma once
#include <imgui.h>

//One View, Works With or Without Docking

struct main_view
{
    void operator()()
    {
        maybe_dockspace();  // docking-aware

        ImGui::Begin("Main");
        ImGui::Text("Hello from main_view");
        ImGui::End();
    }

private:
    void maybe_dockspace()
    {
        ImGuiIO& io = ImGui::GetIO();
        if (!(io.ConfigFlags & ImGuiConfigFlags_DockingEnable))
            return; // docking disabled

        ImGuiViewport* vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);
        ImGui::SetNextWindowViewport(vp->ID);

        const ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));

        ImGui::Begin("DockRoot", nullptr, flags);
        ImGui::PopStyleVar(3);

        ImGui::DockSpace(ImGui::GetID("MainDockspace"));

        ImGui::End();
    }
};
