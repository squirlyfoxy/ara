#include "grid.h"

#include "utils_editor.h"
#include "gui_scene_editor.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
#include <iostream>
#include <vector>

float gGridResolution = 0.1f;
float gGridScale = 1.0f;

static float *vert = nullptr;
static unsigned int *ind = nullptr;

unsigned int grid_vao = 0;
unsigned int grid_vbo = 0;
unsigned int grid_ebo = 0;

ara::Shader* grid_shader = nullptr;

void GenerateGridBuffers() {
    if (vert != nullptr && ind != nullptr) {
        return;
    }

    vert = new float[GRID_VERTICES_COUNT * 3];
    ind = new unsigned int[GRID_INDICES_COUNT];

    int i = 0;
    for (int x = 0; x <= GRID_SIZE; x++) {
        for (int y = 0; y <= GRID_SIZE; y++) {
            vert[i * 3 + 0] = ((float)x / (float)GRID_SIZE) * 2.0f - 1.0f;
            vert[i * 3 + 1] = ((float)y / (float)GRID_SIZE) * 2.0f - 1.0f;
            vert[i * 3 + 2] = 0.0f;
            i++;
        }
    }

    i = 0;
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            int row1 = x * (GRID_SIZE + 1);
            int row2 = (x + 1) * (GRID_SIZE + 1);

            ind[i * 6 + 0] = row1 + y;
            ind[i * 6 + 1] = row1 + y + 1;
            ind[i * 6 + 2] = row2 + y;

            ind[i * 6 + 3] = row1 + y;
            ind[i * 6 + 4] = row2 + y + 1;
            ind[i * 6 + 5] = row2 + y;
            i++;
        }
    }

    glGenVertexArrays(1, &grid_vao);
    glGenBuffers(1, &grid_vbo);
    glGenBuffers(1, &grid_ebo);

    glBindVertexArray(grid_vao);

    glBindBuffer(GL_ARRAY_BUFFER, grid_vbo);
    glBufferData(GL_ARRAY_BUFFER, GRID_VERTICES_COUNT * 3 * sizeof(float), vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GRID_INDICES_COUNT * sizeof(unsigned int), ind, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    grid_shader = new ara::Shader("shaders/base.vert", "shaders/grid.frag");
}

void DrawGrid() {
    // Draw the grid
    grid_shader->Use();

    grid_shader->SetVec3("u_color", glm::vec3(1.0f, 1.0f, 1.0f));
    grid_shader->SetMat4("proj", GetEditorProjectionMatrix());

    // Scale and resolution
    grid_shader->SetFloat("u_scale", gGridScale);
    grid_shader->SetFloat("u_resolution", gGridResolution);

    glBindVertexArray(grid_vao);
    glDrawElements(GL_LINES, GRID_INDICES_COUNT, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
