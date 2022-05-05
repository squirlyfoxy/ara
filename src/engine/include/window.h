#pragma one

#include "commons.h"

#include <string>
#include <functional>

#include <GLFW/glfw3.h>

namespace ara
{
    class ARA_API Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Run();
        // Executes before glClearColor and glClear
        void SetRenderStart(std::function<void()> renderU);
        // Executes after glClearColor and glClear
        void SetRenderEnd(std::function<void()> render);
        // Executes if the window is closed
        void SetDestroy(std::function<void()> destroy);

        GLFWwindow* GetWindow() const;

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
