#pragma one

#include "commons.h"

#ifndef ARA_WEB

#include <string>
#include <vector>
#include <functional>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window_input.h"

namespace ara
{
    class ARA_API Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Run();
        // Executes before glClear
        void SetRenderStart(std::function<void()> renderU);
        // Executes after glClear
        void SetRenderEnd(std::function<void()> render);
        // Executes if the window is closed
        void SetDestroy(std::function<void()> destroy);

        // Set events

        void AddMouseMovedEvent(std::function<void(float, float)> event);
        void AddMouseButtonEvent(std::function<void(InputManager*)> event);
        void AddMouseScrollEvent(std::function<void(InputManager*)> event);
        void AddKeyEvent(std::function<void(InputManager*)> event);

        // Getters

        GLFWwindow* GetWindow() const;
        int GetWidth() const;
        int GetHeight() const;

        // Setters

        void SetWidth(int width);
        void SetHeight(int height);

        // Clear color
        glm::vec3 gClearColor;

        // Input
        InputManager *mInputManager;

    private:
        int mWidth, mHeight;
        std::string mTitle;

        GLFWwindow* mWindow;

        // Methods

        void Update();

        std::function<void()> mRenderStart;
        std::function<void()> mRenderEnd;
        std::function<void()> mDestroy;
        bool mRenderStartSet = false;
        bool mRenderEndSet = false;
        bool mDestroySet = false;

        // Events

        // Mouse moved: (x, y)
        std::vector<std::function<void(float, float)>> mMouseEvents;
        // Mouse button pressed
        std::vector<std::function<void(InputManager*)>> mMouseButtonEvents;
        // Mouse wheel scrolled
        std::vector<std::function<void(InputManager*)>> mScrollEvents;
        // Key pressed
        std::vector<std::function<void(InputManager*)>> mKeyEvents;

        // Initialize glfw
        void Init();

        // Callbacks

        // Glfw error callback
        static void ErrorCallback(int error, const char* description);
        // Glfw window resize callback
        static void WindowResizeCallback(GLFWwindow* window, int width, int height);    };
} // ara

#endif
