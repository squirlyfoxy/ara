#pragma one

#include "commons.h"

#include <string>
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
        InputManager *gInputManager;

    private:
        int mWidth, mHeight;
        std::string mTitle;
    
        GLFWwindow* mWindow;

        // Methods

        std::function<void()> mRenderStart;
        std::function<void()> mRenderEnd;
        std::function<void()> mDestroy;
        bool mRenderStartSet = false;
        bool mRenderEndSet = false;
        bool mDestroySet = false;

        // Initialize glfw
        void Init();
        // Glfw error callback
        static void ErrorCallback(int error, const char* description);
        // Glfw window resize callback
        static void WindowResizeCallback(GLFWwindow* window, int width, int height);
    };
} // ara
