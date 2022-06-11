#pragma once

#include <string>

#include <glm/glm.hpp>

#include "commons.h"

namespace ara {

    class ARA_API Text {
    public:
        Text(const std::string& text, const std::string& font, glm::vec2 position, float size = 1.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
        ~Text();

        void Render(bool is_entity = false);

        void SetText(const std::string& text);
        
        std::string mText;
        float mSize;
        std::string mFont;
        glm::vec3 mColor;
        glm::vec2 mPosition;

    private:

        unsigned int mVAO = 0;
        unsigned int mVBO = 0;

        void Init();
    };

} // ara
