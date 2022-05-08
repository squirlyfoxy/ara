#include <version.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// GUI
#include "gui_menu.h"

#include "project_manager.h"

#include "utils_fluids.h"

#include <iostream>

// ARA includes
#include <window.h>

int main() {
    std::cout << "Starting ARA version: " << ara_VERSION_MAJOR << "." << ara_VERSION_MINOR << "..." << std::endl;

    // Create a window
    ara::Window window(800, 600, "ARA Window");

    //GetProjectManager()->AddProject(ara::Project("test"));

    std::cout << ara::GetFileContent("test.txt") << std::endl;

    // Initialize the ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    window.SetRenderStart(
        []() {
            // Render code goes here for editor
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

                gui_render_menu();

            ImGui::Render();
        }
    );

    window.SetRenderEnd(
        []() {
            // End imgui frame
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());        }
    );

    window.SetDestroy(
        []() {
            // Cleanup code goes here for editor
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    );

    window.Run();

    return 0;
}