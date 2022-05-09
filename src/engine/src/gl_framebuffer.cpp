#include "gl_framebuffer.h"

#include <iostream>

#include <glad/glad.h>

namespace ara {

    Framebuffer::Framebuffer(int width, int height) {
        mWidth = width;
        mHeight = height;

        Init();
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &mFBO);
        glDeleteRenderbuffers(1, &mRBO);
        glDeleteTextures(1, &mTexture);
    }

    unsigned int Framebuffer::GetTexture() const {
        return mTexture;
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
        glDeleteTextures(1, &mTexture);

        Init();
    }

    void Framebuffer::Init() {
        // Create framebuffer
        glGenFramebuffers(1, &mFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

        // Create texture
        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);
    
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
            glDeleteTextures(1, &mTexture);
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
