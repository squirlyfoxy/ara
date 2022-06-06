#include "utils_editor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float gZoom = 1.0f;

float posX = 0.0f;
float posY = 0.0f;

bool cantMove = false;

glm::mat4 GetEditorProjectionMatrix() {
    // 800x600

    return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
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

void ZoomCamera(float delta) {
    gZoom = glm::clamp(gZoom + delta, 0.1f, 100.0f);
    if (gZoom == 0.0f) {
        gZoom = 0.1f;
    }
}

void MoveCamera(float _posX, float _posY) {
    if (cantMove) return;

    posX = _posX;
    posY = _posY;
}

float GetCameraPositionX() {
    return posX;
}

float GetCameraPositionY() {
    return posY;
}

static float velocity = 0.1f;

void CameraMovedCallback(ara::InputManager* inputManager) {
    if (cantMove) return;
    
    // IF ctrl + wasd
    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_W)) {
        MoveCamera(GetCameraPositionX(), GetCameraPositionY() + velocity);
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_S)) {
        MoveCamera(GetCameraPositionX(), GetCameraPositionY() - velocity);
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_A)) {
        MoveCamera(GetCameraPositionX() + velocity, GetCameraPositionY());
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_D)) {
        MoveCamera(GetCameraPositionX() - velocity, GetCameraPositionY());
    }
}

void CameraScrollCallback(ara::InputManager* inputManager) {
    // If we are scrolling, we can't move the camera
    cantMove = true;

    float yoffset = inputManager->GetScrollY();

    if (yoffset != 0.0f) {
        ZoomCamera(-yoffset * velocity);
    }

    cantMove = false;
}
