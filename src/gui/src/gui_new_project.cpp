#include "gui_new_project.h"

#include "project_manager.h"

#include "imgui.h"

ImWindowNewProject::ImWindowNewProject(std::string name) : ImWindow(name) {
    open = false;
    gui_new_project_project_name = new char[256];
}

ImWindowNewProject::~ImWindowNewProject() {
}

void ImWindowNewProject::Draw() {
    if (!IsOpen()) return;

    ImGui::Begin("New Project", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Create a new project");
        ImGui::Separator();
        ImGui::InputText("Project Name", gui_new_project_project_name, 256);
        ImGui::Separator();
        if (ImGui::Button("Create")) {
            // Create the project
            if (gui_new_project_project_name != "") {
                ara::Project project(gui_new_project_project_name);

                GetProjectManager()->AddProject(project);
                gui_new_project_project_name = {};
                open = false;
            }
        }
    ImGui::End();
}
