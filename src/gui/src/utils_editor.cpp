#include "utils_editor.h"

#include <iostream>
#include <filesystem>

#include "project_manager.h"

#include "window_input_keys.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float gZoom = 500.0f;

float posX = 0.0f;
float posY = 0.0f;

//bool cantMove = false;

glm::mat4 GetEditorProjectionMatrix() {
    // 800x600

    return glm::ortho(-1.0f, 800.0f, -1.0f, 600.0f, -1.0f, 1.0f);
}

const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 GetEditorViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), up);

    view = glm::translate(view, glm::vec3(posX, posY, 0.0f));

    // Zoom in/out
    view = glm::scale(view, glm::vec3(gZoom, gZoom, 1.0f));

    return view;
}

float GetCameraPositionX() {
    return posX;
}

float GetCameraPositionY() {
    return posY;
}

static float zoom_velocity = 10.0f;

void ZoomCamera(float delta) {
    gZoom = glm::clamp(gZoom + delta * zoom_velocity, 0.1f, 1000.0f);
}

void MoveCamera(float _posX, float _posY) {
    //if (cantMove) return;

    posX = _posX;
    posY = _posY;
}

void Save() {
    if (GetProjectManager()->GetCurrentProject() != nullptr) {
        std::ofstream project_file = std::ofstream("projects/" +  GetProjectManager()->GetCurrentProject()->GetName() + "/" + GetProjectManager()->GetCurrentProject()->GetName() + ".ara");
            ara::Project::Save(&project_file, *GetProjectManager()->GetCurrentProject());
        project_file.close();
    }
}
