#include <version.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>

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

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430 core");

    float vertices[] = {
        // first triangle
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left 
        // second triangle
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int vao;
    unsigned int vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create a shader
    ara::Shader shader("shaders/base.vert", "shaders/base.frag");

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
        
            bind_scene_editor_framebuffer();
            glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            unbind_scene_editor_framebuffer();
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