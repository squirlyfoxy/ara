#pragma once

#include <scene.h>
#include <window_input.h>

void initialize_scene_editor();
void destroy_scene_editor_framebuffer();

int GetWindowWidth();
int GetWindowHeight();

void gui_render_scene_editor(ara::Scene s);
void gui_render_scene(ara::Scene s);

void SceneEditorMousePicking(ara::InputManager* inputManager);
