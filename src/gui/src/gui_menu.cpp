#include "gui_menu.h"

#include "imgui_stdlib.h"

#include "gui/gui.h"

#include "project_manager.h"
#include "version.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

#include "imgui.h"

bool gui_new_project_open = false;
bool gui_project_open_popup_open = false;
bool gui_scene_new_popup_open = false;
std::string gui_project_open_popup_project_name = "";
std::string gui_new_project_project_name = "";
std::string gui_scene_new_popup_scene_name = "";

void gui_new_project() {
    // No Resize
    ImGui::Begin("New Project", &gui_new_project_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Create a new project");
        ImGui::Separator();
        ImGui::InputText("Project Name", &gui_new_project_project_name);
        ImGui::Separator();
        if (ImGui::Button("Create")) {
            // Create the project
            if (gui_new_project_project_name != "") {
                ara::Project project(gui_new_project_project_name);
                //project.SetBasePath("projects/" + gui_new_project_project_name);

                GetProjectManager()->AddProject(project);
                gui_new_project_project_name = "";
                gui_new_project_open = false;
            }
        }
    ImGui::End();
}

void gui_open_project() {
    // No Resize
    ImGui::Begin("Open Project", &gui_project_open_popup_open, ImGuiWindowFlags_NoCollapse);
        if (GetProjectManager()->GetProjectCount() == 0) {
            ImGui::Text("No projects found");
        } else {
            // List all the projects, when selection change show the name and the creation time in a label.
            // Use a button to open the project
            ImGui::Text("Projects");
            if (gui_project_open_popup_project_name != "") {
                ImGui::Text("Selected: %s", gui_project_open_popup_project_name.c_str());
                std::time_t today_time = std::chrono::system_clock::to_time_t(GET_PROJECT(gui_project_open_popup_project_name).GetCreationTime());
                ImGui::Text("Created: %s", std::ctime(&today_time));
            }
            ImGui::Separator();
            for (auto& project : GetProjectManager()->GetProjects()) {
                if (ImGui::Selectable(project.first.c_str())) {
                    gui_project_open_popup_project_name = project.first;
                }
            }
            ImGui::Separator();
            if (gui_project_open_popup_project_name != "") {
                if (ImGui::Button("Open")) {
                    if (!GET_PROJECT(gui_project_open_popup_project_name).Validate()) {
                        std::cout << "Project is not valid" << std::endl;
                    } else {
                        GetProjectManager()->SetCurrentProject(gui_project_open_popup_project_name);
                        gui_project_open_popup_project_name = "";
                        gui_project_open_popup_open = false;
                    }                
                }
            }
        }
    ImGui::End();
}

void gui_new_scene() {
    ImGui::Begin("New Scene", &gui_scene_new_popup_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Create a new scene");
        ImGui::Separator();
        ImGui::InputText("Scene Name", &gui_scene_new_popup_scene_name);
        ImGui::Separator();
        if (ImGui::Button("Create")) {
            // Create the scene
            if (gui_scene_new_popup_scene_name != "") {
                ara::Scene scene(gui_scene_new_popup_scene_name);

                // Create scene folder
                std::string scene_folder = "projects/" + GetProjectManager()->GetCurrentProject()->GetName() + "/" + gui_scene_new_popup_scene_name;
                std::filesystem::create_directory(scene_folder);

                GetProjectManager()->GetCurrentProject()->gScenes.push_back(scene);

                ara::Scene::Save(scene_folder, scene);

                // Save the project
                std::ofstream project_file = std::ofstream("projects/" +  GetProjectManager()->GetCurrentProject()->GetName() + "/" + GetProjectManager()->GetCurrentProject()->GetName() + ".ara");
                    ara::Project::Save(&project_file, *GetProjectManager()->GetCurrentProject());
                project_file.close();

                gui_scene_new_popup_scene_name = "";
                gui_scene_new_popup_open = false;
            }
        }
    ImGui::End();
}

void gui_render_menu() {
    // Main menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) { gui_new_project_open = true; }
            if (ImGui::MenuItem("Open Project")) { gui_project_open_popup_open = true; }
            if (ImGui::MenuItem("Save")) { }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { exit(0); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project")) {
            // Submenu for scenes
            if (ImGui::BeginMenu("Scenes")) {
                if (ImGui::MenuItem("New Scene")) { if (GetProjectManager()->GetCurrentProject() != nullptr) { gui_scene_new_popup_open = true; } }
                ImGui::EndMenu();
            }

            // TODO: SUBMENU FOR ASSETS

            // TODO: SUBMENU FOR ENTITIES

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
    if (gui_new_project_open) {
        gui_new_project();
    }

    // Project open list
    if (gui_project_open_popup_open) {
        gui_open_project();
    }

    // New scene
    if (gui_scene_new_popup_open) {
        gui_new_scene();
    }
}
