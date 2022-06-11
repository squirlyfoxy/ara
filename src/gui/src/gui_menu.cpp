#include "gui_menu.h"

#include "imgui_stdlib.h"

#include "gui/gui.h"

// Entities
#include "entity_empty.h"
#include "entity_square.h"
#include "entity_camera.h"
#include "entity_text.h"

#include "project_manager.h"
#include "utils_editor.h"
#include "version.hpp"

// Windows
#include "gui_open_project.h"
#include "gui_new_project.h"
#include "gui_new_scene.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>

#include "imgui.h"

ImWindowOpenProject *gui_project_open_popup = new ImWindowOpenProject("Open Project");
ImWindowNewProject *gui_project_new_popup = new ImWindowNewProject("New Project");
ImWindowNewScene *gui_scene_new_popup = new ImWindowNewScene("New Scene");

void gui_render_menu() {
    // Main menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) { gui_project_new_popup->SetOpen(true); }
            if (ImGui::MenuItem("Open Project")) { gui_project_open_popup->SetOpen(true); }
            if (ImGui::MenuItem("Save")) { Save(); }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { exit(0); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project")) {
            // Submenu for scenes
            if (ImGui::BeginMenu("Scenes")) {
                if (ImGui::MenuItem("New Scene")) { if (GetProjectManager()->GetCurrentProject() != nullptr) { gui_scene_new_popup->SetOpen(true); } }
                ImGui::EndMenu();
            }
            ImGui::Separator();

            // TODO: SUBMENU FOR ASSETS

            // TODO: SUBMENU FOR ENTITIES
            if (ImGui::BeginMenu("New")) {
                if (ImGui::MenuItem("Empty Entity")) {
                    if (GetProjectManager()->GetCurrentProject() != nullptr) { GetProjectManager()->GetCurrentProject()->GetCurrentScene()->AddEntity(dynamic_cast<ara::Entity*>(new ara::EntityEmpty())); }
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Camera")) {
                    if (GetProjectManager()->GetCurrentProject() != nullptr) { GetProjectManager()->GetCurrentProject()->GetCurrentScene()->AddEntity(dynamic_cast<ara::Entity*>(new ara::EntityCamera())); }
                }
                if (ImGui::MenuItem("Square")) {
                    if (GetProjectManager()->GetCurrentProject() != nullptr) { GetProjectManager()->GetCurrentProject()->GetCurrentScene()->AddEntity(dynamic_cast<ara::Entity*>(new ara::EntitySquare())); }
                }
                if (ImGui::MenuItem("Text")) {
                    if (GetProjectManager()->GetCurrentProject() != nullptr) { GetProjectManager()->GetCurrentProject()->GetCurrentScene()->AddEntity(dynamic_cast<ara::Entity*>(new ara::EntityText())); }
                }
                ImGui::EndMenu();
            }

            // TODO: PROJECT OPTIONS

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) { 
                ara::gui::SimpleMessageBox("About", "Ara 2D Game Engine\n\nVersion: " + std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR)  + "\nCreated by: @sqirlyfoxy\n\nCopyright (c) 2022 7Software. All rights reserved.");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // New project window
    gui_project_new_popup->Draw();

    // Project open list
    gui_project_open_popup->Draw();

    // New scene
    gui_scene_new_popup->Draw();
}
