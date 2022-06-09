#include "gui_new_scene.h"

#include <iostream>
#include <filesystem>

#include "project_manager.h"
#include "utils_editor.h"

#include "imgui_stdlib.h"
#include "imgui.h"

ImWindowNewScene::ImWindowNewScene(std::string name) : ImWindow(name) {
    open = false;
}

ImWindowNewScene::~ImWindowNewScene() {
}

void ImWindowNewScene::Draw() {
    if (!IsOpen()) return;

        ImGui::Begin("New Scene", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
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

                Save();

                gui_scene_new_popup_scene_name = "";
                open = false;
            }
        }
    ImGui::End();
}
