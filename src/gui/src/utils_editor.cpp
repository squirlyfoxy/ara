#include "utils_editor.h"

#include <glm/gtc/matrix_transform.hpp>

float gZoom = 1.0f;

float posX = 0.0f;
float posY = 0.0f;

glm::mat4 GetEditorProjectionMatrix() {
    return glm::ortho(-1.0f * gZoom, 1.0f * gZoom, -1.0f * gZoom, 1.0f * gZoom, -1.0f, 1.0f);
}

glm::mat4 GetEditorViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(posX, posY, 0.0f));

    return view;
}

void Zoom(float delta) {
    gZoom += delta;
}

void Move(float _posX, float _posY) {
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
    // IF ctrl + wasd
    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_W)) {
        Move(GetCameraPositionX(), GetCameraPositionY() + velocity);
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_S)) {
        Move(GetCameraPositionX(), GetCameraPositionY() - velocity);
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_A)) {
        Move(GetCameraPositionX() + velocity, GetCameraPositionY());
    }

    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && inputManager->IsKeyPressed(GLFW_KEY_D)) {
        Move(GetCameraPositionX() - velocity, GetCameraPositionY());
    }
}

void CameraScrollCallback(ara::InputManager* inputManager) {
    if (inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        Zoom(inputManager->GetScrollY() * velocity);
    }
}
