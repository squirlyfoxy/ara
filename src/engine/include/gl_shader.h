#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

//#include "glm.hpp"

namespace ara {

    enum ShaderType {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    struct Shader {
        unsigned int id;
        ShaderType type;
        
        const char *source;
    };

    Shader ReadShader(const char *file, ShaderType type);

    class Program {
    public:
        Program(std::vector<Shader> shs);

        // Binds the program
        void Bind();

        void BindInt(const std::string& name, const int& value);
        void BindFloat(const std::string& name, const float& value);
        void BindBool(const std::string& name, const bool& value);
        /*void BindVec4(const std::string& name, const glm::vec4& v);
        void BindVec3(const std::string& name, const glm::vec3& v);
        void BindMat4(const std::string& name, const glm::mat4& m);*/
    private:
        unsigned int mId;

        std::vector<Shader> mShaders;

        // Cache for uniform locations (thanks cherno)
        std::unordered_map<std::string, int> mUniformLocations;

        // Methods
        unsigned int GetUniformLocation(const std::string& name);
    };

} // ara
