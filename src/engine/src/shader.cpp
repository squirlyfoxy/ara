#include "shader.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "commons.h"
#include "utils_fluids.h"

namespace ara {

    // Check if shader is compiled successfully
    #define SHADER_CHECK_COMPILATION_ERROR(...) int success; \
        char infoLog[512]; \
        glGetShaderiv(__VA_ARGS__, GL_COMPILE_STATUS, &success); \
        if (!success) { \
            glGetShaderInfoLog(__VA_ARGS__, 512, NULL, infoLog); \
            std::cout << "ERROR::SHADER::" << #__VA_ARGS__ << "::COMPILATION_FAILED\n" << infoLog << std::endl; \
            return ARA_GL_SHADER_COMPILATION_ERROR; \
        }

    // Check if shader is linked successfully
    #define SHADER_CHECK_LINK_ERROR(...) int success; \
        char infoLog[512]; \
        glGetProgramiv(__VA_ARGS__, GL_LINK_STATUS, &success); \
        if (!success) { \
            glGetProgramInfoLog(__VA_ARGS__, 512, NULL, infoLog); \
            std::cout << "ERROR::SHADER::" << #__VA_ARGS__ << "::LINK_FAILED\n" << infoLog << std::endl; \
        }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        mVertexPath = vertexPath;
        mFragmentPath = fragmentPath;

        Init();
    }

    Shader::~Shader() {
        glDeleteProgram(mID);
    }

    void Shader::Use() const {
        glUseProgram(mID);
    }

    void Shader::Unuse() const {
        glUseProgram(0);
    }

    void Shader::SetInt(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetVec3(const std::string& name, const glm::vec3& value) {
        glUniform3fv(GetUniformLocation(name), 1, &glm::value_ptr(value)[0]);
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &glm::value_ptr(value)[0]);
    }

    void Shader::Init() {
        unsigned int vertexShader;
        unsigned int fragmentShader;
        if ((vertexShader = CompileShader(GL_VERTEX_SHADER, 
            GetFileContent(mVertexPath)
        )) == ARA_GL_SHADER_COMPILATION_ERROR) { // Check if compilation fails
            return;
        }
        if ((fragmentShader = CompileShader(GL_FRAGMENT_SHADER,
            GetFileContent(mFragmentPath)
        )) == ARA_GL_SHADER_COMPILATION_ERROR) { // Check if compilation fails
            return;
        }

        // Create the program
        mID = glCreateProgram();
        glAttachShader(mID, vertexShader);
        glAttachShader(mID, fragmentShader);
        glLinkProgram(mID);
        
        SHADER_CHECK_LINK_ERROR(mID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    unsigned int Shader::CompileShader(int type, const char* source) {
        unsigned int id = glCreateShader(type);
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);

        SHADER_CHECK_COMPILATION_ERROR(id);

        return id;
    }

    int Shader::GetUniformLocation(const std::string& name) {
        if (uniform_locations.find(name) != uniform_locations.end()) {
            return uniform_locations[name];
        }
        
        return uniform_locations[name] = glGetUniformLocation(mID, name.c_str());
    }
}
