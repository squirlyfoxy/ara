#include "texture.h"

#include <iostream>
#include <cstring>

#include "utils_fluids.h"

#include "lib/stb_image.h"

#include <glad/glad.h>

namespace ara {

    Texture::Texture(const std::string& path) {
        mId = 0;
        mPath = path;

        Init();
    }

    Texture::~Texture() {
        glDeleteTextures(1, &mId);
    }

    unsigned int Texture::GetId() const {
        return mId;
    }

    std::string Texture::GetPath() const {
        return mPath;
    }

    void Texture::Bind(int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, mId);
    }

    void Texture::Init() {
        char* content = (char*)GetFileContent(mPath);

        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load_from_memory((const unsigned char*)content, FileSize(mPath), &width, &height, &nrChannels, 0);

        if (data) {
            glGenTextures(1, &mId);
            glBindTexture(GL_TEXTURE_2D, mId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else if (nrChannels == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }

            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        // Free stbi
        stbi_image_free(data);
    }

}; // ara
