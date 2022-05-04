#include "gui_menu.h"

#include "version.hpp"

#include <iostream>

#include "imgui.h"

bool gui_help_about_open = false;

void gui_render_menu() {
    // Main menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) { }
            if (ImGui::MenuItem("Open Project")) { }
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
        // No Resize
        ImGui::Begin("About", &gui_help_about_open, ImGuiWindowFlags_NoResize);
            ImGui::Text("ARA is a simple 2D Game Engine");
            ImGui::Text("Version: %d.%d", ara_VERSION_MAJOR, ara_VERSION_MINOR);
        ImGui::End();
    }
}
