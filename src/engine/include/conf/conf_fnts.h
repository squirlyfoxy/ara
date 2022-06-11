#pragma once

#include "lib/json.hpp"

#include <map>

#include <glm/glm.hpp>

#include "commons.h"

#define ARA_TOML_CONF_PATH "./assets/fnts_assoc.toml"

namespace ara {

    namespace conf {

        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            char         Value;      // The character value
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        // Load all the fonts that have been associated with the engine into the toml file
        ARA_API void DecodeFnts();

        // Get the characters of a font
        ARA_API std::map<char, Character> GetFntCharacters(std::string fontName);

        // Get the loaded fonts
        ARA_API std::vector<std::string> GetFnts();

    } // conf

}; // ara
