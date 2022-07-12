#include "gl_global_buffers.h"

#include <map>

#include <glad/glad.h>

namespace ara {

    static std::map<std::string, GBuffer*> sGBuffers;

    GBuffer::GBuffer(unsigned int size, std::function<void(GBuffer*)> init) {
        buffers = new unsigned int[size];
        init(this);
    }

    GBuffer::~GBuffer() {
        glDeleteBuffers(ARRAY_SIZE(buffers), buffers);

        delete[] buffers;
    }

    void RegisterGBuffer(
        std::string name,
        unsigned int size,
        std::function<void(GBuffer*)> init
    ) {
        sGBuffers[name] = new GBuffer(size, init);
    }

    GBuffer* GetGBuffer(std::string name) {
        // if not found, return nullptr
        if (sGBuffers.find(name) == sGBuffers.end()) {
            return nullptr;
        }

        return sGBuffers[name];
    }

    // ****************************

    void InitGBufferSquare() {
        if (GetGBuffer("sq_buffer") != nullptr) return;

        float vertices[] = {
            // positions          // texture coords
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
            0.5f, 0.5f, 0.0f,       1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f,      0.0f, 1.0f
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        RegisterGBuffer("sq_buffer", 3, [vertices, indices](GBuffer* buffer) {
            glGenVertexArrays(1, &buffer->buffers[ARA_GLOBAL_BUFFER_VAO_LOCATION]);
            glGenBuffers(1, &buffer->buffers[ARA_GLOBAL_BUFFER_VBO_LOCATION]);
            glGenBuffers(1, &buffer->buffers[ARA_GLOBAL_BUFFER_EBO_LOCATION]);

            glBindVertexArray(buffer->buffers[ARA_GLOBAL_BUFFER_VAO_LOCATION]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer->buffers[ARA_GLOBAL_BUFFER_VBO_LOCATION]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->buffers[ARA_GLOBAL_BUFFER_EBO_LOCATION]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // Updind VAO
            glBindVertexArray(0);
        });
    }

} // ara
