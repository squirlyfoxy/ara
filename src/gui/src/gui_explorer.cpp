#include "gui_explorer.h"

#include "project_manager.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include <imgui.h>

#include <texture.h>
#include <utils_data.h>
#include <utils_fluids.h>
#include <gui/gui.h>

static ara::Texture* mFolderIcon;
static ara::Texture* mSaraFileIcon;
static ara::Texture* mEntFileIcon;
static ara::Texture* mGeneralFileIcon;

ImWindowExplorer::ImWindowExplorer(std::string name) : ImWindow(name) {
    Init();
}

ImWindowExplorer::~ImWindowExplorer() {
    delete mFolderIcon;
    delete mSaraFileIcon;
    delete mEntFileIcon;
    delete mGeneralFileIcon;
}

void ImWindowExplorer::Init() {
    if (mFolderIcon == nullptr) {
        mFolderIcon = new ara::Texture("./assets/icons/folder.png");
    }

    if (mSaraFileIcon == nullptr) {
        mSaraFileIcon = new ara::Texture("./assets/icons/file_sara.png");
    }

    if (mEntFileIcon == nullptr) {
        mEntFileIcon = new ara::Texture("./assets/icons/file_ent.png");
    }

    if (mGeneralFileIcon == nullptr) {
        mGeneralFileIcon = new ara::Texture("./assets/icons/file.png");
    }
}

void ImWindowExplorer::Draw() {
    // List of the scenes in the project
    ImGui::Begin(name.c_str(), nullptr); // TODO: MOVE TO A CLASS
        int width = ImGui::GetContentRegionAvail().x;
        int columnCount = width / 200; if (columnCount < 1) columnCount = 1;
        float cellWidth = width / columnCount;

        std::vector<ara::File> f = ara::GetFiles(ARA_GET_CUSTOMER_DATA("engine").mData["current_path"]);
        // Add at the beginning ../ (going back)
        f.push_back({
            Name: "../",
            Path: "/../",
            Type: ara::FileType::Directory
        });
        std::rotate(f.rbegin(), f.rbegin() + 1, f.rend());

        ImGui::Columns(columnCount, 0, false);

        for (const auto& file : f) {
            // If directory, add a folder icon as button
            if (file.Type == ara::FileType::Directory) {
                ImGui::ImageButton(
                    (ImTextureID)mFolderIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } else if (file.Type == ara::FileType::Scene) {
                ImGui::ImageButton(
                    (ImTextureID)mSaraFileIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } else if (file.Type == ara::FileType::Entity) {
                ImGui::ImageButton(
                    (ImTextureID)mEntFileIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } else {
                ImGui::ImageButton(
                    (ImTextureID)mGeneralFileIcon->GetId(),
                    ImVec2(cellWidth, cellWidth),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } 
            
            if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (file.Type == ara::FileType::Directory) {
                    ara::CustomerData engine = ARA_GET_CUSTOMER_DATA("engine");
                    if (file.Path == "/../") {
                        engine.mData["current_path"] += file.Path;
                    } else {
                        engine.mData["current_path"] = file.Path;
                    }
                    ARA_SET_CUSTOMER_DATA("engine", engine);
                    break;
                } else if (file.Type == ara::FileType::Scene) {
                    // remove the ".sara" extension
                    std::string scene_name = file.Name.substr(0, file.Name.size() - 5);
                    GetProjectManager()->GetCurrentProject()->SetCurrentScene(scene_name);

                    break;
                } else if (file.Type == ara::FileType::Entity) {
                    // TODO

                    break;
                } else if (file.Type == ara::FileType::Project) {
                    // remove from the name of the file ".ara"
                    std::string project_name = file.Name.substr(0, file.Name.size() - 4);
                    if (project_name == GetProjectManager()->GetCurrentProject()->GetName()) {
                        break;
                    }
                    
                    if (ara::gui::SimpleYesNoBox("Are you sure?", "Do you want to open the project " + project_name + "?\nUnsaved changes will be lost.")) {
                        GetProjectManager()->SetCurrentProject(project_name);
                    }

                    break;
                }
            }
            ImGui::Text(file.Name.c_str());

            ImGui::NextColumn();
        }

        // Footer
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::Text("Files: %d", (f.size() - 1));

    ImGui::End();
}


