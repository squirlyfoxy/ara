#include "gui_open_project.h"

#include "project_manager.h"

#include "imgui.h"
#include "imgui_stdlib.h"

#include "gui/gui.h"

ImWindowOpenProject::ImWindowOpenProject(std::string name) : ImWindow(name) {
    open = false;
}

ImWindowOpenProject::~ImWindowOpenProject() {
}

void ImWindowOpenProject::Draw() {
    if (!IsOpen()) return;

    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
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
                        ara::gui::ErrorMessageBox("Error", "Project is corrupted");
                    } else {
                        GetProjectManager()->SetCurrentProject(gui_project_open_popup_project_name);
                        gui_project_open_popup_project_name = "";
                        open = false;
                    }                
                }
            }
        }
    ImGui::End();
}
