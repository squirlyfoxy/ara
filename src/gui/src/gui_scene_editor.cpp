#include "gui_scene_editor.h"

#include <iostream>

#include "grid.h"

// GUI
#include "gui_explorer.h"
#include "gui_entities.h"

#include <glad/glad.h>

#include "imgui.h"
#include "imgui_stdlib.h"

#include <gl_framebuffer.h>

ara::Framebuffer* mSceneEditorFramebuffer;

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

void gui_render_scene(ara::Scene s) {
    bind_scene_editor_framebuffer();
        glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO: Render the scene editor
        DrawGrid();

        // Render the scene without physics
        s.Render(false);

    unbind_scene_editor_framebuffer();
}
