#include "gui_scene_editor.h"

#include <iostream>
#include <chrono>

#include "grid.h"

// GUI
#include "gui_explorer.h"
#include "gui_entities.h"

#include <glad/glad.h>

#include "imgui.h"
#include "imgui_stdlib.h"

#include <gl_framebuffer.h>
#include <render_text.h>

ara::Framebuffer* mSceneEditorFramebuffer;
ara::Text* mSceneEditorText;

ImWindowExplorer* mExplorerWindow;
ImWindowEntities* mEntitiesWindow;

void initialize_scene_editor() {
    mSceneEditorFramebuffer = new ara::Framebuffer(800, 600);

    GenerateGridBuffers();

    // *
    // * Initialize the windows
    // *

    mExplorerWindow = new ImWindowExplorer("Explorer");
    mEntitiesWindow = new ImWindowEntities("Entities");
    mSceneEditorText = new ara::Text("", "system", glm::vec2(10.0f, 10.0f), 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void destroy_scene_editor_framebuffer() {
    delete mSceneEditorFramebuffer;
}

void bind_scene_editor_framebuffer() {
    mSceneEditorFramebuffer->Bind();
}

void unbind_scene_editor_framebuffer() {
    mSceneEditorFramebuffer->Unbind();
}

int GetWindowWidth() {
    return mSceneEditorFramebuffer->GetWidth();
}

int GetWindowHeight() {
    return mSceneEditorFramebuffer->GetHeight();
}

bool first_frame = true;
std::string old_scene_name = "";

void gui_render_scene_editor(ara::Scene s) {
    ImGui::Begin(std::string("Scene Editor - " + s.GetName()).c_str(), nullptr, ImGuiWindowFlags_NoResize);
        // Render the texture
        
        if (first_frame || old_scene_name != s.GetName()) {
            ImGui::SetWindowPos(ImVec2(1, 20));
            ImGui::SetWindowSize(ImVec2(GetWindowWidth(), GetWindowHeight()));
        
            first_frame = false;
            old_scene_name = s.GetName();
        }

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)mSceneEditorFramebuffer->GetTexture(),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + 800, pos.y + 600)
        );
    ImGui::End();

    // Explorer
    mExplorerWindow->Draw();

    // List of the entities in the scene
    mEntitiesWindow->Draw();
}

std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
void gui_render_scene(ara::Scene s) {
    begin = std::chrono::system_clock::now();

    bind_scene_editor_framebuffer();
        glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO: Render the scene editor
        DrawGrid();

        // Render the scene without physics
        s.Render(false);

        mSceneEditorText->SetText(std::string("frame time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(begin - end).count()) + "ms"));
        mSceneEditorText->Render();

    unbind_scene_editor_framebuffer();

    end = std::chrono::system_clock::now();
}
