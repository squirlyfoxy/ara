#include "render_text.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "conf/conf_fnts.h"

#include "utils_transforms.h"

#include <glad/glad.h>

namespace ara {

    static Shader* sTextShader = nullptr;

    // buffers

    Text::Text(const std::string& text, const std::string& font, glm::vec2 position, float size, glm::vec3 color) {
        mText = text;
        mFont = font;
        mSize = size;
        mColor = color;
        mPosition = position;

        Init();
    }

    Text::~Text() {
    }

    void Text::Init() {
        if (sTextShader == nullptr) {
            sTextShader = new Shader("./shaders/text_vertex.vert", "./shaders/text_fragment.frag");
        }

        if (mVAO == 0 || mVBO == 0) {
            glGenVertexArrays(1, &mVAO);
            glGenBuffers(1, &mVBO);
            glBindVertexArray(mVAO);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    void Text::Render(bool is_entity) {
        if (sTextShader == nullptr) return;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        sTextShader->Use();
        sTextShader->SetVec3("textColor", mColor);
        sTextShader->SetMat4("projection", GetProjection());
        
        if (is_entity) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.0f));
            sTextShader->SetMat4("model", model);
            
            glm::mat4 view = GetView();
            sTextShader->SetMat4("view", view);
        } else {
            sTextShader->SetMat4("model", glm::mat4(1.0f));
            sTextShader->SetMat4("view", glm::mat4(1.0f));
        }

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(mVAO);

        auto font = conf::GetFntCharacters(mFont);
        std::string::const_iterator c;

        float x = mPosition.x;

        int maxAscent = 0;

        for (c = mText.begin(); c != mText.end(); c++) {
            auto character = font[*c];

            // Calculate max descent and ascent
            if (character.Bearing.y > maxAscent) {
                maxAscent = character.Bearing.y;
            }

            float xpos = x + character.Bearing.x * mSize;
            float ypos = (mPosition.y * mSize) - (character.Bearing.y * mSize) + (maxAscent * mSize);
            
            // width and height with descent and ascent
            float w = character.Size.x * mSize;
            float h = character.Size.y * mSize;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 1.0f },            
                { xpos,     ypos,       0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f }
            };

            glBindTexture(GL_TEXTURE_2D, character.TextureID);

            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (character.Advance >> 6) * mSize;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);
    }

    void Text::SetText(const std::string& text) {
        mText = text;
    }

} // ara

