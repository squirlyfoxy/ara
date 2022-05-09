#pragma one

#include "commons.h"

namespace ara {

    class ARA_API Framebuffer {
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        void ChangeSize(int width, int height);

        // Getters

        unsigned int GetTexture() const;

        void Bind() const;
        void Unbind() const;
        
        int GetWidth() const;
        int GetHeight() const;

    private:
        unsigned int mFBO;
        unsigned int mRBO;
        unsigned int mTexture;

        int mWidth;
        int mHeight;

        // Methods

        void Init();

    };

} // ara
