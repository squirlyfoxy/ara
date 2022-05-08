#include "gl_globals.h"

#include "commons.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void InitializeOpenGL() {
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(ARA_GLAD_ERROR_EXIT_CODE);
    }

    // Print OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}
