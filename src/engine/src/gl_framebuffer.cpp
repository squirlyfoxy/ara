#include "gl_framebuffer.h"

#include <assert.h>

#include <glad/glad.h>

namespace ara {

// OPTIONS FOR THE BINDED TEXTURE
#define ARA_FRAMEBUFFER_TEXTURE_OPTIONS glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); \
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); \
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); \
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); \
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Framebuffer::Framebuffer(int width, int height, std::vector<FramebufferTexture> textures) {
        mWidth = width;
        mHeight = height;
        mTextures = textures;

        mTexturesID = new unsigned int[mTextures.size()];

        Init();
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &mFBO);
        glDeleteRenderbuffers(1, &mRBO);
        glDeleteTextures(mTextures.size(), mTexturesID);
    }

    unsigned int Framebuffer::GetTexture(int index) const {
        assert(index >= 0 && index < mTextures.size());
        return mTexturesID[index];
    }

    int Framebuffer::ReadPixel(uint32_t attachment, int x, int y) const {
        assert(attachment < mTextures.size());
        int pData;
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment);
        glReadPixels(x, y, 1, 1, (int)mTextures[attachment].format, (int)mTextures[attachment].type, &pData);

        return pData;
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    }

    void Framebuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::ChangeSize(int width, int height) {
        mWidth = width;
        mHeight = height;

        glDeleteFramebuffers(1, &mFBO);
        glDeleteRenderbuffers(1, &mRBO);
        glDeleteTextures(mTextures.size(), mTexturesID);

        Init();
    }

    void Framebuffer::Init() {
        // Create framebuffer
        glCreateFramebuffers(1, &mFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

        // Create textures
        glCreateTextures(GL_TEXTURE_2D, mTextures.size(), mTexturesID);
        for (int i = 0; i < mTextures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, mTexturesID[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, (int)mTextures[i].internalFormat, mWidth, mHeight, 0, (int)mTextures[i].format, (int)mTextures[i].type, NULL);
            ARA_FRAMEBUFFER_TEXTURE_OPTIONS
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mTexturesID[i], 0);
        }

        // Prepare render targets
        GLenum DrawBuffers[mTextures.size()];
        for (int i = 0; i < mTextures.size(); i++) {
            DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
        }
        glDrawBuffers(mTextures.size(), DrawBuffers);
    
        // Create renderbuffer
        glGenRenderbuffers(1, &mRBO);
        glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

        // Check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Framebuffer is not complete!" << std::endl;

            glDeleteFramebuffers(1, &mFBO);
            glDeleteRenderbuffers(1, &mRBO);
            glDeleteTextures(mTextures.size(), mTexturesID);
        }

        // Unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    int Framebuffer::GetWidth() const {
        return mWidth;
    }

    int Framebuffer::GetHeight() const {
        return mHeight;
    }
}
