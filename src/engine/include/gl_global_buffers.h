#pragma once

#include <string>
#include <functional>

#include "commons.h"

#define ARA_GLOBAL_BUFFER_VBO_LOCATION 0
#define ARA_GLOBAL_BUFFER_VAO_LOCATION 1
#define ARA_GLOBAL_BUFFER_EBO_LOCATION 2

namespace ara {

    struct ARA_API GBuffer {
        unsigned int *buffers; // Array of buffers

        // size = number of buffers, init = function to initialize the buffers
        GBuffer(unsigned int size, std::function<void(GBuffer*)> init);
        ~GBuffer();
    };

    void ARA_API RegisterGBuffer(
        std::string name,
        unsigned int size,
        std::function<void(GBuffer*)> init
    );

    GBuffer* ARA_API GetGBuffer(std::string name);

    // ****************************
    // Standard GBuffers

    void ARA_API InitGBufferSquare();

} // ara
