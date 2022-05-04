#include "window.h"

#include "gl_globals.h"

#include <iostream>

namespace ara
{
    Window::Window(int width, int height, const std::string& title)
    {
        mWidth = width;
        mHeight = height;
        mTitle = title;

        Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void Window::ErrorCallback(int error, const char* description)
    {
        std::cerr << "GLFW Error: " << description << std::endl;
    }

    void Window::Init()
    {
        // Initialize glfw
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW" << std::endl;
            return;
        }
        glfwSetErrorCallback(ErrorCallback);
        
        // Context version 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!(mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr)))
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(mWindow);

        InitializeOpenGL();
    }

    void Window::Run()
    {
        while (!glfwWindowShouldClose(mWindow))
        {
            if (mRenderUpdateSet) mRenderUpdate();

            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }
    }

    void Window::SetRenderUpdate(std::function<void()> renderUpdate)
    {
        mRenderUpdate = renderUpdate;
        mRenderUpdateSet = true;
    }
} // ara
