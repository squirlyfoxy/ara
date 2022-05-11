#include <version.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// GUI
#include "gui_menu.h"

#include "project_manager.h"
#include "gui_scene_editor.h"

#include <iostream>

// ARA includes
#include <shader.h>
#include <window.h>

int main() {
    std::cout << "Starting ARA version: " << ara_VERSION_MAJOR << "." << ara_VERSION_MINOR << "..." << std::endl;

    // Create a window
    ara::Window window(1024, 768, "ARA");
    initialize_scene_editor_framebuffer();

    // Initialize the ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Move only when using the title bar
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430 core");

    window.SetRenderStart(
        [&]() {
            // Render code goes here for editor
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

                gui_render_menu();

                GetProjectManager()->RenderProjectEditor();

            ImGui::Render();
        }
    );

    window.SetRenderEnd(
        [&]() {
            // End imgui frame
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
            // Render code goes here for editor
            gui_render_scene(GetProjectManager()->GetCurrentProject()->GetCurrentScene());
            glViewport(0, 0, window.GetWidth(), window.GetHeight());
        }
    );

    window.SetDestroy(
        [&]() {
            // Cleanup code goes here for editor
            destroy_scene_editor_framebuffer();

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    );

    window.Run();

    return 0;
}