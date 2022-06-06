#pragma once

#include <glm/glm.hpp>

#include "window_input.h"

// ******************************************************
// Editor Matrix

glm::mat4 GetEditorProjectionMatrix();
glm::mat4 GetEditorViewMatrix();

// *******************************************************
// Editor Camera

void ZoomCamera(float delta);
void MoveCamera(float _posX, float _posY);

float GetCameraPositionX();
float GetCameraPositionY();

void CameraMovedCallback(ara::InputManager* inputManager);
void CameraScrollCallback(ara::InputManager* inputManager);
