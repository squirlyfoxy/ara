#pragma once

#include "commons.h"

#include <unordered_map>
#include <string>

namespace ara {

    class ARA_API Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Use() const;
        void Unuse() const;
    private:
        unsigned int mID;

        std::string mVertexPath;
        std::string mFragmentPath;

        std::unordered_map<std::string, unsigned int> uniform_locations;

        // Methods
        void Init();
        unsigned int CompileShader(int type, const char* source);
        unsigned int GetUniformLocation(const std::string& name);
    };

} // ara
