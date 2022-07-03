#include "gui_entities.h"

#include "project_manager.h"

#include "imgui.h"
#include "lib/json.hpp"

#include <utils_data.h>

ImWindowEntities::ImWindowEntities(std::string name) : ImWindow(name) {
}

ImWindowEntities::~ImWindowEntities() {
}

void ImWindowEntities::Draw() {
        ImGui::Begin(name.c_str(), nullptr);
        if (GetProjectManager()->GetCurrentProject()->GetCurrentScene()->GetEntities().size() == 0) {
            ImGui::Text("No entities in this scene");
        } else {
            // List the entity in a tree
            ImGui::BeginChild("Entities", ImVec2(0, 0), true);
            std::vector<ara::Entity*> entities = GetProjectManager()->GetCurrentProject()->GetCurrentScene()->GetEntities();
                for (int i = 0; i < entities.size(); i++) {
                    nlohmann::json j = nlohmann::json::parse(ARA_GET_CUSTOMER_DATA("entities").mData[entities[i]->GetName()]);
                    if (j["if_selected"]) {
                        selected_entity = entities[i];
                        gui_edit_entity_open = true;
                    } else {
                        selected_entity = nullptr;
                        gui_edit_entity_open = false;
                    }

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

    if (gui_edit_entity_open) edit_entity(); else selected_entity = nullptr;
}

void ImWindowEntities::edit_entity() {
    ImGui::Begin("Edit Entity", &gui_edit_entity_open);
        ImGui::Text(("Editing " + selected_entity->GetName()).c_str());
        ImGui::Separator();

        selected_entity->Edit();

    ImGui::End();
}
