#include "conf/conf_fnts.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glad/glad.h>

#include <iostream>
#include <map>

#include "utils_data.h"
#include "utils_fluids.h"

#include <toml.hpp>

namespace ara {

    namespace conf {

        void DecodeFnts() {
            // *
            // * Initialize freetype
            // *
            FT_Library ft;
            if (FT_Init_FreeType(&ft)) {
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
                exit(1);
            }

            std::istringstream iss(ara::GetFileContent(ARA_TOML_CONF_PATH));

            auto data = toml::parse(iss);
            // gett all the entries at fonts
            auto fonts = toml::find(data, "fonts");

            ara::CustomerData fontsD;

            // iterate over all the entries
            for (auto& font : fonts.as_table()) {
                // get the key
                auto key = font.first;
                // get the value
                auto value = font.second;

                std::string fontPath = value.as_string().str;
                fontPath = "./assets/" + fontPath;

                FT_Face face;
                if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
                    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
                    exit(1);
                }

                FT_Set_Pixel_Sizes(face, 0, 48);
                std::map<char, Character> characters;

                glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
                for (GLubyte c = 0; c < 128; c++) {
                    // load character glyph 
                    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                        continue;
                    }
                    // generate texture
                    unsigned int texture;
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer
                    );
                    // set texture options
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // now store character for later use
                    Character character = {
                        texture, 
                        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                        face->glyph->advance.x
                    };
                    characters.insert(std::pair<char, Character>(c, character));
                }
                // convert the map to json
                nlohmann::json j;
                for (auto& c : characters) {
                    j[c.first] = std::vector<int>{(int)c.second.TextureID, c.second.Size.x, c.second.Size.y, c.second.Bearing.x, c.second.Bearing.y, (int)c.second.Advance};
                }
                fontsD.mData[key] = j.dump();
                
                FT_Done_Face(face);
            }
            FT_Done_FreeType(ft);

            ARA_SET_CUSTOMER_DATA("fonts", fontsD);
        }

    } // conf

}; // ara
