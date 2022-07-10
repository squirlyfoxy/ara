#pragma once

#include "commons.h"

#include <string>

namespace ara {

    class ARA_API Texture {
    public:
        Texture(const std::string& path);
        ~Texture();

        unsigned int GetId() const;
        std::string GetPath() const;

        void Bind(int unit = 0);
    private:
        unsigned int mId;

        std::string mPath;

        void Init();
    };

}; // ara
