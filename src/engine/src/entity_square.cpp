#include "entity_square.h"

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
    }
    
    void EntitySquare::Render() {
    }
    
} // ara
