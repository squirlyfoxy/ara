#include "gl_shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h> 

namespace ara {
    Shader ReadShader(const char *file, ShaderType type) {
        Shader shader;
        shader.type = type;

        std::ifstream stream(file);
        if (stream.fail()) {
            std::cout << "Failed to open file " << file << std::endl;
            return shader;
        }

        std::string line;
        std::stringstream ss;
        while (std::getline(stream, line)) {
            ss << line << "\n";
        }
        stream.close();

        shader.source = ss.str().c_str();

        return shader;
    }

    // **********************************
    // Program class

    Program::Program(std::vector<Shader> shs) {
        for (unsigned int i = 0; i < shs.size(); i++) {
            switch (shs[i].type) {
                case VERTEX_SHADER:
                    mShaders.push_back(shs[i]);
                    mShaders[i].id = glCreateShader(GL_VERTEX_SHADER);
                    break;
                case FRAGMENT_SHADER:
                    mShaders.push_back(shs[i]);
                    mShaders[i].id = glCreateShader(GL_FRAGMENT_SHADER);
                    break;
            }
            glShaderSource(mShaders[i].id, 1, &mShaders[i].source, NULL);
            glCompileShader(mShaders[i].id);
        
            // TODO: CHECK ERRORS
        }

        // TODO: CREATE PROGRAM

        // TODO: LINK PROGRAM

        // TODO: CHECK ERRORS
    }
};
