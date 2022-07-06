#include "gui_entities.h"

#include <iostream>

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
                    if (j["if_selected"] && !selected_from_tree) {
                        selected_entity = entities[i];
                    }

                    // Treenode that opens automatically when the entity is selected
                    if (selected_entity == entities[i])
                        ImGui::SetNextItemOpen(true);
                    else // only one selected entity at a time
                        ImGui::SetNextItemOpen(false);

                    if (ImGui::TreeNode(entities[i]->GetName().c_str())) {
                        // Buttons in a row (Edit and Delete)
                        selected_entity = entities[i];
                        selected_from_tree = true;

                        if (ImGui::Button("Edit")) {
                            // Edit the entity
                            gui_edit_entity_open = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete")) {
                            // TODO: Delete the entity
                        }

                        // get data and set it
                        j["if_selected"] = entities[i]->GetName() == selected_entity->GetName();
                        ARA_GET_CUSTOMER_DATA("entities").mData[entities[i]->GetName()] = j.dump();

                        ImGui::TreePop();
                    }
                }
            ImGui::EndChild();
        }
    ImGui::End();

    if (gui_edit_entity_open)
        edit_entity(); 
    else { // Reset
        selected_from_tree = false;
        selected_entity = nullptr;
    }
}

void ImWindowEntities::edit_entity() {
    ImGui::Begin("Edit Entity", &gui_edit_entity_open);
        ImGui::Text(("Editing " + selected_entity->GetName()).c_str());
        ImGui::Separator();

        selected_entity->Edit();

    ImGui::End();
}
