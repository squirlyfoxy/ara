#include "gui_scene_editor.h"

#include "project_manager.h"

#include <glad/glad.h>

#include "gui/gui.h"

#include "imgui.h"
#include "imgui_stdlib.h"

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

bool gui_edit_entity_open = false;
ara::Entity* selected_entity = nullptr;
std::string selected_entity_name = "";
void gui_edit_entity() {
    ImGui::Begin("Edit Entity", &gui_edit_entity_open);
        ImGui::Text(("Editing " + selected_entity->GetName()).c_str());
        ImGui::Separator();

        // Position
        ImGui::Text("Position X | Y");
        ImGui::SameLine();
        float poss[] = {selected_entity->GetPosition().x, selected_entity->GetPosition().y};
        ImGui::InputFloat2("##Position", poss);    
        selected_entity->SetPosition(glm::vec2(poss[0], poss[1]));

        // Name
        ImGui::Text("Name");
        ImGui::SameLine();

        ImGui::InputText("##Name", &selected_entity_name);

        // Save
        if (ImGui::Button("Save")) {
            if (!selected_entity_name.empty()) {
                selected_entity->SetName(selected_entity_name);
            } else {
                ara::gui::ErrorMessageBox("Error", "Entity name cannot be empty");
                selected_entity_name = selected_entity->GetName();
            }
        }

    ImGui::End();
}

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
                            // Edit the entity
                            gui_edit_entity_open = true;
                            selected_entity_name = entity->GetName();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete")) {
                            // TODO: Delete the entity
                        }

                        selected_entity = entity;

                        ImGui::TreePop();
                    }
                }
            ImGui::EndChild();
        }
    ImGui::End();

    if (gui_edit_entity_open) gui_edit_entity(); else selected_entity = nullptr;
}

void gui_render_scene(ara::Scene s) {
    bind_scene_editor_framebuffer();
        glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

        // TODO: Render the scene editor

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    unbind_scene_editor_framebuffer();
}
