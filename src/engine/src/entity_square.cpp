#include "entity_square.h"

#include <glad/glad.h>

namespace ara {

    unsigned int sqare_vbo = 0;
    unsigned int sqare_vao = 0;
    unsigned int sqare_ebo = 0;

    float sqare_vertices[] = {
        // Positions        // Texture Coords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int sqare_indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    EntitySquare::EntitySquare() {
        mType = "EntitySquare";

        Init();
    }
    
    void EntitySquare::Render() {
    }

    void EntitySquare::Init() {
        if (sqare_vbo != 0) return;
    
        glGenVertexArrays(1, &sqare_vao);
        glGenBuffers(1, &sqare_vbo);
        glGenBuffers(1, &sqare_ebo);

        glBindVertexArray(sqare_vao);
        glBindBuffer(GL_ARRAY_BUFFER, sqare_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sqare_vertices), sqare_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sqare_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sqare_indices), sqare_indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Updind VAO
        glBindVertexArray(0);
    }

    void EntitySquare::Edit() {
        BasicEdit();

        // TODO: SQARE EDIT
    }
    
} // ara
