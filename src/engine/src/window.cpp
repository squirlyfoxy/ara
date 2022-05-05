#include <glad/glad.h> // GLAD include (before glfw)

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
        if (mDestroySet) mDestroy();

        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void Window::ErrorCallback(int error, const char* description)
    {
        std::cerr << "GLFW Error: " << description << std::endl;
    }

    void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height); // Update viewport
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        if (!(mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr)))
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(mWindow);

        // Set callbacks for window
        glfwSetWindowSizeCallback(mWindow, WindowResizeCallback);

        InitializeOpenGL();
    }

    void Window::Run()
    {
        while (!glfwWindowShouldClose(mWindow))
        {
            if (mRenderStartSet) mRenderStart();

            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (mRenderEndSet) mRenderEnd();

            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }
    }

    void Window::SetRenderStart(std::function<void()> render)
    {
        mRenderStart = render;
        mRenderStartSet = true;
    }

    void Window::SetRenderEnd(std::function<void()> render)
    {
        mRenderEnd = render;
        mRenderEndSet = true;
    }

    void Window::SetDestroy(std::function<void()> destroy)
    {
        mDestroy = destroy;
        mDestroySet = true;
    }

    GLFWwindow* Window::GetWindow() const
    {
        return mWindow;
    }

} // ara
