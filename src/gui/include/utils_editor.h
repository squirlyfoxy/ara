#pragma once

#include <glm/glm.hpp>

#include "window_input.h"

glm::mat4 GetEditorProjectionMatrix();
glm::mat4 GetEditorViewMatrix();

void Zoom(float delta);
void Move(float _posX, float _posY);

float GetCameraPositionX();
float GetCameraPositionY();

void CameraMovedCallback(ara::InputManager* inputManager);
void CameraScrollCallback(ara::InputManager* inputManager);
