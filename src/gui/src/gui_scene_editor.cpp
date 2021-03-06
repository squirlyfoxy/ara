#include "gui_scene_editor.h"

#include <iostream>
#include <chrono>

#include "grid.h"

// GUI
#include "gui_explorer.h"
#include "gui_entities.h"

#include "utils_editor.h"

#include "project_manager.h"

#include "lib/json.hpp"

#include <utils_data.h>
#include <utils_transforms.h>
#include <window_input_keys.h>

#include <glad/glad.h>

#include "imgui.h"
#include "imgui_stdlib.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gl_framebuffer.h>
#include <window.h>
#include <render_text.h>

ara::Framebuffer* mSceneEditorFramebuffer;
ara::Text* mSceneEditorText;

ImWindowExplorer* mExplorerWindow;
ImWindowEntities* mEntitiesWindow;

void initialize_scene_editor() {
    mSceneEditorFramebuffer = new ara::Framebuffer(800, 600, {
        { ara::FramebufferTextureInternalFormat::ARA_RGBA8, ara::FramebufferTextureFormat::ARA_RGBA, ara::FramebufferTextureType::ARA_UNSIGNED_BYTE },
        { ara::FramebufferTextureInternalFormat::ARA_RED, ara::FramebufferTextureFormat::ARA_RED_INTEGER, ara::FramebufferTextureType::ARA_INT }
    });

    GenerateGridBuffers();

    // *
    // * Initialize the windows
    // *

    mExplorerWindow = new ImWindowExplorer("Explorer");
    mEntitiesWindow = new ImWindowEntities("Entities");
    mSceneEditorText = new ara::Text("", "system", glm::vec2(10.0f, 10.0f), 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void destroy_scene_editor_framebuffer() {
    delete mSceneEditorFramebuffer;
}

void bind_scene_editor_framebuffer() {
    mSceneEditorFramebuffer->Bind();
}

void unbind_scene_editor_framebuffer() {
    mSceneEditorFramebuffer->Unbind();
}

int GetWindowWidth() {
    return mSceneEditorFramebuffer->GetWidth();
}

int GetWindowHeight() {
    return mSceneEditorFramebuffer->GetHeight();
}

bool first_frame = true;

bool we_are_over_scene = false;
ImVec2 scene_editor_window_pos;
glm::vec2 viewport_bounds[2];

ImVec2 old_size;

void gui_render_scene_editor(ara::Scene s) {
    ImGui::Begin(std::string("Scene Editor - " + s.GetName()).c_str(), nullptr);
        // Render the texture  
        we_are_over_scene = ImGui::IsWindowHovered();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        scene_editor_window_pos = pos;

        if (old_size.x != ImGui::GetWindowSize().x ||
            old_size.y != ImGui::GetWindowSize().y) {
            mSceneEditorFramebuffer->ChangeSize(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);        
        
            old_size = ImGui::GetWindowSize();

            viewport_bounds[0] = glm::vec2(pos.x, pos.y);
            viewport_bounds[1] = glm::vec2(pos.x + GetWindowWidth(), pos.y + GetWindowHeight());
        }

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)mSceneEditorFramebuffer->GetTexture(0),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + GetWindowWidth(), pos.y + GetWindowHeight())
        );
    ImGui::End();

    // Explorer
    mExplorerWindow->Draw();

    // List of the entities in the scene
    mEntitiesWindow->Draw();
}

std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
void gui_render_scene(ara::Scene s) {
    begin = std::chrono::system_clock::now();

    bind_scene_editor_framebuffer();
        glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO: Render the scene editor
        DrawGrid();

        // Render the scene without physics
        s.Render(false);

        ara::Window* instance = (ara::Window*)glfwGetWindowUserPointer(glfwGetCurrentContext());
        SceneEditorMousePicking(instance->mInputManager);

        mSceneEditorText->SetText(std::string("frame time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(begin - end).count()) + "ms"));
        mSceneEditorText->Render();
    unbind_scene_editor_framebuffer();

    end = std::chrono::system_clock::now();
}

void SceneEditorMousePicking(ara::InputManager* inputManager) {
    if (GetProjectManager()->GetCurrentProject() == nullptr) return;

    // if we are moving the camera, we don't want to pick anything
    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL) && (
        inputManager->IsKeyPressed(KEY_A) ||
        inputManager->IsKeyPressed(KEY_D) ||
        inputManager->IsKeyPressed(KEY_W) ||
        inputManager->IsKeyPressed(KEY_S)
    )) {
        return;
    }

    // check if the mouse is over the scene editor
    if (!we_are_over_scene) { // if no
        // if right button is pressed, deselect

        if (inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            // deselect entity
            for (auto& entity : GetProjectManager()->GetCurrentProject()->GetCurrentScene()->gEntities) {
                nlohmann::json j = nlohmann::json::parse(ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()]);
                if (j["if_selected"]) {
                    j["if_selected"] = false;
                    ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()] = j.dump();

                    break;
                }            
            }
        }

        return;
    }

    glm::vec2 viewportSize = viewport_bounds[1] - viewport_bounds[0];
    
    float x = ((inputManager->GetMouseX() - viewport_bounds[0].x) / viewportSize.x) * GetWindowWidth();
    float y = ((inputManager->GetMouseY() - viewport_bounds[0].y) / viewportSize.y) * GetWindowHeight();

    int val = mSceneEditorFramebuffer->ReadPixel(1, (int)x, (int)y);

    // Loop thorught the entities and check if the mouse is over them
    // use 2d picking to check if the mouse is over an entity
    for (auto& entity : GetProjectManager()->GetCurrentProject()->GetCurrentScene()->gEntities){
        if (!entity->canBeSelected) continue;

        nlohmann::json j = nlohmann::json::parse(ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()]);
        
        if (val == entity->GetUid()) {
            // Set the selected entity
            if (inputManager->IsMouseButtonPressed(0) && !j["if_selected"]) { // left, select
                j["if_selected"] = true;
                ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()] = j.dump();

                return;
            }
        }

        if (inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && j["if_selected"]) { // right, deselect
            j["if_selected"] = false;
            ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()] = j.dump();
        
            return;
        }
    }

}

static float velocity = 1.0f;

void CameraMovedCallback(ara::InputManager* inputManager) {
    if (GetProjectManager()->GetCurrentProject() == nullptr) return;
    if (!we_are_over_scene) return;
    
    // IF l_ctrl + wasd
    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(KEY_W)) {
        MoveCamera(GetCameraPositionX(), GetCameraPositionY() + velocity);
    }

    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(KEY_S)) {
        MoveCamera(GetCameraPositionX(), GetCameraPositionY() - velocity);
    }

    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(KEY_A)) {
        MoveCamera(GetCameraPositionX() + velocity, GetCameraPositionY());
    }

    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(KEY_D)) {
        MoveCamera(GetCameraPositionX() - velocity, GetCameraPositionY());
    }
}

void CameraScrollCallback(ara::InputManager* inputManager) {
    if (GetProjectManager()->GetCurrentProject() == nullptr) return;
    if (!we_are_over_scene) return;

    float yoffset = inputManager->GetScrollY();

    if (inputManager->IsKeyPressed(KEY_LEFT_CONTROL)) {
        ZoomCamera(yoffset);
    }
}
