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
            ImGui::Separator();
            for (auto& project : GetProjectManager()->GetProjects()) {
                if (ImGui::Selectable(project.c_str())) {
                    gui_project_open_popup_project_name = project;
                }
            }
            ImGui::Separator();
            if (gui_project_open_popup_project_name != "") {
                if (ImGui::Button("Open")) {
                    GetProjectManager()->SetCurrentProject(gui_project_open_popup_project_name);
                    gui_project_open_popup_project_name = "";
                    open = false;              
                }
            }
        }
    ImGui::End();
}
