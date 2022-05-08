#include "gui_menu.h"

#include "imgui_stdlib.h"

#include "project_manager.h"
#include "version.hpp"

#include <iostream>

#include "imgui.h"

bool gui_help_about_open = false;
bool gui_new_project_open = false;
bool gui_project_open_popup_open = false;
std::string gui_project_open_popup_project_name = "";
std::string gui_new_project_project_name = "";

void gui_render_help() {
    // No Resize
    ImGui::Begin("About", &gui_help_about_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("ARA is a simple 2D Game Engine");
        ImGui::Text("Version: %d.%d", ara_VERSION_MAJOR, ara_VERSION_MINOR);
    ImGui::End();
}

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
                project.SetBasePath("projects/" + gui_new_project_project_name);

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
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) { gui_help_about_open = true; }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Help window
    if (gui_help_about_open) {
        gui_render_help();
    }

    // New project window
    if (gui_new_project_open) {
        gui_new_project();
    }

    // Project open list
    if (gui_project_open_popup_open) {
        gui_open_project();
    }
}
