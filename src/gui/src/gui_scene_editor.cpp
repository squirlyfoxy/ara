#include "gui_scene_editor.h"

#include "lib/json.hpp"

#include "project_manager.h"
#include "grid.h"

#include <glad/glad.h>

#include "gui/gui.h"

#include "imgui.h"
#include "imgui_stdlib.h"

#include <gl_framebuffer.h>
#include <texture.h>
#include <utils_data.h>
#include <utils_fluids.h>

ara::Framebuffer* mSceneEditorFramebuffer;

ara::Texture* mFolderIcon;
ara::Texture* mGeneralFileIcon;

void initialize_scene_editor() {
    mSceneEditorFramebuffer = new ara::Framebuffer(800, 600);

    GenerateGridBuffers();

    mFolderIcon = new ara::Texture("./assets/icons/folder.png");
    mGeneralFileIcon = new ara::Texture("./assets/icons/file.png");
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
ara::Entity* selected_entity;
void gui_edit_entity() { // TODO: MOVE TO A CLASS
    ImGui::Begin("Edit Entity", &gui_edit_entity_open);
        ImGui::Text(("Editing " + selected_entity->GetName()).c_str());
        ImGui::Separator();

        selected_entity->Edit();

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
            (ImTextureID)mSceneEditorFramebuffer->GetTexture(),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + 800, pos.y + 600)
        );
    ImGui::End();

    // List of the scenes in the project
    ImGui::Begin("Explorer", nullptr); // TODO: MOVE TO A CLASS
        int width = ImGui::GetContentRegionAvail().x;
        int columnCount = width / 200; if (columnCount < 1) columnCount = 1;
        float cellWidth = width / columnCount;

        std::vector<ara::File> f = ara::GetFiles(ARA_GET_CUSTOMER_DATA("engine").mData["current_path"]);
        // Add at the beginning ../ (going back)
        f.push_back({
            Name: "../",
            Path: "/../",
            Type: ara::FileType::Directory
        });
        std::rotate(f.rbegin(), f.rbegin() + 1, f.rend());

        ImGui::Columns(columnCount, 0, false);

        for (const auto& file : f) {
            // If directory, add a folder icon as button
            if (file.Type == ara::FileType::Directory) {
                ImGui::ImageButton(
                    (ImTextureID)mFolderIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } else {
                ImGui::ImageButton(
                    (ImTextureID)mGeneralFileIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            }
            if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (file.Type == ara::FileType::Directory) {
                    ara::CustomerData engine = ARA_GET_CUSTOMER_DATA("engine");
                    if (file.Path == "/../") {
                        engine.mData["current_path"] += file.Path;
                    } else {
                        engine.mData["current_path"] = file.Path;
                    }
                    ARA_SET_CUSTOMER_DATA("engine", engine);
                    break;
                } else if (file.Type == ara::FileType::Scene) {
                    break;
                } else if (file.Type == ara::FileType::Entity) {
                    break;
                } else if (file.Type == ara::FileType::Project) {
                    break;
                }
            }
            ImGui::Text(file.Name.c_str());

            ImGui::NextColumn();
        }
    ImGui::End();

    // List of the entities in the scene
    ImGui::Begin("Entities"); // TODO: MOVE TO A CLASS
        if (GetProjectManager()->GetCurrentProject()->GetCurrentScene()->GetEntities().size() == 0) {
            ImGui::Text("No entities in this scene");
        } else {
            // List the entity in a tree
            ImGui::BeginChild("Entities", ImVec2(0, 0), true);
            std::vector<ara::Entity*> entities = GetProjectManager()->GetCurrentProject()->GetCurrentScene()->GetEntities();
                for (int i = 0; i < entities.size(); i++) {
                    if (ImGui::TreeNode(entities[i]->GetName().c_str())) {
                        // Buttons in a row (Edit and Delete)

                        if (ImGui::Button("Edit")) {
                            // Edit the entity
                            gui_edit_entity_open = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete")) {
                            // TODO: Delete the entity
                        }

                        selected_entity = entities[i];

                        // get data and set it
                        for (auto& entity : entities) {
                            nlohmann::json j = nlohmann::json::parse(ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()]);
                            j["if_selected"] = entity->GetName() == selected_entity->GetName();
                            ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()] = j.dump();
                        }

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO: Render the scene editor
        DrawGrid();

        // Render the scene without physics
        s.Render(false);

    unbind_scene_editor_framebuffer();
}
