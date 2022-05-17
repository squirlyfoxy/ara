#include "gui_scene_editor.h"

#include "project_manager.h"

#include <glad/glad.h>

#include "imgui.h"

#include <gl_framebuffer.h>

ara::Framebuffer* mSceneEditorFramebuffer;

void initialize_scene_editor_framebuffer() {
    mSceneEditorFramebuffer = new ara::Framebuffer(800, 600);
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
            (void*)mSceneEditorFramebuffer->GetTexture(),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + 800, pos.y + 600)
        );
    ImGui::End();

    // List of the scenes in the project
    ImGui::Begin("Scenes", nullptr);
        for (auto& scene : GetProjectManager()->GetCurrentProject()->gScenes) {
            if (ImGui::Button(scene.GetName().c_str())) {
                GetProjectManager()->GetCurrentProject()->SetCurrentScene(scene);
            }
        }
    ImGui::End();

    // List of the entities in the scene
    ImGui::Begin("Entities");
        if (GetProjectManager()->GetCurrentProject()->GetCurrentScene().GetEntities().size() == 0) {
            ImGui::Text("No entities in this scene");
        } else {
            // List the entity in a tree
            ImGui::BeginChild("Entities", ImVec2(0, 0), true);
                for (auto& entity : GetProjectManager()->GetCurrentProject()->GetCurrentScene().GetEntities()) {
                    if (ImGui::TreeNode(entity->GetName().c_str())) {
                        // Buttons in a row (Edit and Delete)

                        if (ImGui::Button("Edit")) {
                            // TODO: Edit the entity
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete")) {
                            // TODO: Delete the entity
                        }

                        ImGui::TreePop();
                    }
                }
            ImGui::EndChild();
        }
    ImGui::End();
}

void gui_render_scene(ara::Scene s) {
    bind_scene_editor_framebuffer();
        glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

        // TODO: Render the scene editor

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    unbind_scene_editor_framebuffer();
}
