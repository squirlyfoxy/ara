#pragma once

#include <glm/glm.hpp>

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

        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVec3(const std::string& name, const glm::vec3& value);
        void SetMat4(const std::string& name, const glm::mat4& value);

    private:
        unsigned int mID;

        std::string mVertexPath;
        std::string mFragmentPath;

        std::unordered_map<std::string, int> uniform_locations;

        // Methods
        void Init();
        unsigned int CompileShader(int type, const char* source);
        int GetUniformLocation(const std::string& name);
    };

} // ara
