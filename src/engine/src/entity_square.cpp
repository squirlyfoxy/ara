#include "entity_square.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils_transforms.h"
#include "shader.h"

#include <glad/glad.h>

namespace ara {

    static unsigned int sqare_vbo = 0;
    static unsigned int sqare_vao = 0;
    static unsigned int sqare_ebo = 0;

    static Shader* shader = nullptr;

    float vertices[] = {
        // positions          // texture coords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    EntitySquare::EntitySquare() {
        mType = "EntitySquare";
        mName = "Square";

        Init();

        gColor = glm::vec3(1.0f, 1.0f, 1.0f);

        // Edit modalities
        mEditModalities = {
            EntityEditModality::Color
        };
    }
    
    void EntitySquare::Render(bool selected) {
        if (selected) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.0f));

        shader->SetMat4("view", GetView());
        shader->SetMat4("proj", GetProjection());
        shader->SetMat4("model", model);

        shader->SetVec3("u_color", gColor);

        glBindVertexArray(sqare_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        if (selected) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void EntitySquare::Save(std::ofstream& file) {
        // NOTE: Nothing
    }

    void EntitySquare::CustomLoad(std::istringstream& file) {
        // NOTE: Nothing
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

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Updind VAO
        glBindVertexArray(0);
    }

    void EntitySquare::Edit() {
        BasicEdit();

        // TODO: SQARE EDIT
    }
    
} // ara
