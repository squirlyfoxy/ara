#include "gui_menu.h"

#include "project_manager.h"
#include "version.hpp"

#include <iostream>

#include "imgui.h"

bool gui_help_about_open = false;
bool gui_new_project_open = false;
bool gui_project_open_popup_open = false;

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
    ImGui::End();
}

void gui_open_project() {
    // No Resize
    ImGui::Begin("Open Project", &gui_project_open_popup_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (GetProjectManager()->GetProjectCount() == 0) {
            ImGui::Text("No projects found");
        } else {
            // TODO: Add project names to list
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
