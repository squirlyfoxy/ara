#include "entity_square.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ara {

    static unsigned int sqare_vbo = 0;
    static unsigned int sqare_vao = 0;
    static unsigned int sqare_ebo = 0;

    static Shader* shader = nullptr;

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    EntitySquare::EntitySquare() {
        mType = "EntitySquare";

        Init();
    }
    
    void EntitySquare::Render() {
        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.0f));
        
        /*shader->SetMat4("model", mModel);
        shader->SetMat4("view", mView);
        shader->SetMat4("projection", mProjection);*/

        shader->SetMat4("model", model);

        glBindVertexArray(sqare_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void EntitySquare::Init() {
        if (sqare_vbo != 0) return;
    
        shader = new Shader("./shaders/base.vert", "./shaders/base.frag");

        glGenVertexArrays(1, &sqare_vao);
        glGenBuffers(1, &sqare_vbo);
        glGenBuffers(1, &sqare_ebo);

        glBindVertexArray(sqare_vao);
        glBindBuffer(GL_ARRAY_BUFFER, sqare_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sqare_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Updind VAO
        glBindVertexArray(0);
    }

    void EntitySquare::Edit() {
        BasicEdit();

        // TODO: SQARE EDIT
    }
    
} // ara
