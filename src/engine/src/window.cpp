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

        gClearColor = glm::vec3(0.5f, 0.5f, 0.5f); // Gray as default

        Init();

        mInputManager = new InputManager(mWindow);
    }

    Window::~Window()
    {
        delete mInputManager;

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
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->SetWidth(width);
        w->SetHeight(height);

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

        // Set pointers to the window
        glfwSetWindowUserPointer(mWindow, this);

        // Set callbacks for window
        glfwSetWindowSizeCallback(mWindow, WindowResizeCallback);

        InitializeOpenGL();
    }

    void Window::Update()
    {
        // Update input
        if (mInputManager->CanUpdate())
        {
            // Call the mouse button callbacks
            for (auto& callback : mMouseButtonEvents)
            {
                callback(mInputManager);
            }

            // Call the key callbacks
            for (auto& callback : mKeyEvents)
            {
                callback(mInputManager);
            }
        }

        // Call the mouse callbacks
        for (auto& callback : mMouseEvents)
        {
            callback(mInputManager->GetMouseX(), mInputManager->GetMouseY());
        }

        // Call the mouse wheel callbacks
        if (mInputManager->CanScrollUpdate())
        {
            for (auto& callback : mScrollEvents)
            {
                callback(mInputManager);
            }

            mInputManager->Reset();
        }
    }

    void Window::Run()
    {
        while (!glfwWindowShouldClose(mWindow))
        {
            Update();

            if (mRenderStartSet) mRenderStart();

            glClear(GL_COLOR_BUFFER_BIT);

            if (mRenderEndSet) mRenderEnd();

            glClearColor(gClearColor.x, gClearColor.y, gClearColor.z, 1.0f);

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

    void Window::AddMouseMovedEvent(std::function<void(float, float)> event)
    {
        mMouseEvents.push_back(event);
    }

    void Window::AddMouseButtonEvent(std::function<void(InputManager*)> event)
    {
        mMouseButtonEvents.push_back(event);
    }

    void Window::AddMouseScrollEvent(std::function<void(InputManager*)> event)
    {
        mScrollEvents.push_back(event);
    }

    void Window::AddKeyEvent(std::function<void(InputManager*)> event)
    {
        mKeyEvents.push_back(event);
    }

    GLFWwindow* Window::GetWindow() const
    {
        return mWindow;
    }

    int Window::GetWidth() const
    {
        return mWidth;
    }

    int Window::GetHeight() const
    {
        return mHeight;
    }

    void Window::SetWidth(int width)
    {
        mWidth = width;
    }

    void Window::SetHeight(int height)
    {
        mHeight = height;
    }

} // ara
