#include "entity_square.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils_transforms.h"
#include "shader.h"
#include "gl_global_buffers.h"

#include <glad/glad.h>

namespace ara {
    static Shader* sSquareShader = nullptr;

    EntitySquare::EntitySquare() {
        mType = "EntitySquare";
        mName = "Square";

        Init();

        gColor = glm::vec3(1.0f, 1.0f, 1.0f);
        canBeSelected = true;

        // Edit modalities
        mEditModalities = {
            EntityEditModality::Color
        };
    }
    
    void EntitySquare::Render(bool selected) {
        if (selected) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        sSquareShader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.0f));
        model = glm::scale(model, glm::vec3(mSize.x, mSize.y, 1.0f));

        sSquareShader->SetMat4("view", GetView());
        sSquareShader->SetMat4("proj", GetProjection());
        sSquareShader->SetMat4("model", GetModelMatrix());
        sSquareShader->SetInt("u_uid", (int)GetUid());

        sSquareShader->SetVec3("u_color", gColor);

        glBindVertexArray(GetGBuffer("sq_buffer")->buffers[ARA_GLOBAL_BUFFER_VAO_LOCATION]);
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
        if (sSquareShader == nullptr) sSquareShader = new Shader("./shaders/base.vert", "./shaders/base.frag");
        if (GetGBuffer("spr_buffer") == nullptr) InitGBufferSquare();
    }

    void EntitySquare::Edit() {
        BasicEdit();

        // TODO: SQARE EDIT
    }
    
} // ara
