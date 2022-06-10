#pragma once

#include "lib/json.hpp"

#include <glm/glm.hpp>

#include "commons.h"

#define ARA_TOML_CONF_PATH "./assets/fnts_assoc.toml"

namespace ara {

    namespace conf {

        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        ARA_API void DecodeFnts();

    } // conf

}; // ara
