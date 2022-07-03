#pragma one

#include <iostream>
#include <vector>

#include "commons.h"

namespace ara {

    enum class FramebufferTextureInternalFormat {
        ARA_RGBA8 = 0x8058, // GL_RGBA8
        ARA_RED = 0x8235, // GL_R32I
    };

    enum class FramebufferTextureFormat {
        ARA_RGBA = 0x1908, // GL_RGBA 0x1908
        ARA_RED_INTEGER = 0x8D94, // GL_RED_INTEGER 0x8D94
    };

    enum class FramebufferTextureType {
        ARA_UNSIGNED_BYTE = 0x1401, // GL_UNSIGNED_BYTE 0x1401
        ARA_INT = 0x1404 // GL_INT 0x1404
    };

    // Framebuffer Texture
    struct FramebufferTexture {
        FramebufferTextureInternalFormat    internalFormat;
        FramebufferTextureFormat            format;
        FramebufferTextureType              type;
    };

    class ARA_API Framebuffer {
    public:
        Framebuffer(int width, int height, std::vector<FramebufferTexture> textures);
        ~Framebuffer();

        void ChangeSize(int width, int height);

        // Getters

        unsigned int GetTexture(int index = 0) const;
        int ReadPixel(uint32_t attachment, int x, int y) const;

        void Bind() const;
        void Unbind() const;
        
        int GetWidth() const;
        int GetHeight() const;

    private:
        unsigned int mFBO;
        unsigned int mRBO;

        unsigned int* mTexturesID;
        std::vector<FramebufferTexture> mTextures;

        int mWidth;
        int mHeight;

        // Methods

        void Init();

    };

} // ara
