#include "entity_sprite.h"

#include <lib/json.hpp>

#include "utils_transforms.h"
#include "shader.h"
#include "gl_global_buffers.h"

#include <glad/glad.h>

namespace ara {

    static Shader* sSpriteShader = nullptr;

    EntitySprite::EntitySprite() {
        mType = "EntitySprite";
        mName = "Sprite";

        Init();

        // Edit modalities
        mEditModalities = {
            EntityEditModality::Textures
        };
    }

    void EntitySprite::Init() {    
        if (sSpriteShader == nullptr) sSpriteShader = new Shader("./shaders/base.vert", "./shaders/base_textured.frag");
        if (GetGBuffer("spr_buffer") == nullptr) InitGBufferSquare();
    }

    void EntitySprite::Render(bool selected) {
    }

    void EntitySprite::Edit() {
        BasicEdit();
    }

    void EntitySprite::Save(std::ofstream& file) {
    }

    void EntitySprite::CustomLoad(std::istringstream& file) {
    }

} // ara
