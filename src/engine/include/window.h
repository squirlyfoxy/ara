#pragma one

#include <string>
#include <functional>

#include <GLFW/glfw3.h>

namespace ara
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Run();
        void SetRenderStart(std::function<void()> renderUpdate);
        void SetRenderEnd(std::function<void()> render);

        GLFWwindow* GetWindow() const;

    private:
        int mWidth, mHeight;
        std::string mTitle;
    
        GLFWwindow* mWindow;

        // Methods
        std::function<void()> mRenderUpdate;
        std::function<void()> mRender;
        bool mRenderUpdateSet = false;
        bool mRenderSet = false;

        // Initialize glfw
        void Init();
        // Glfw error callback
        static void ErrorCallback(int error, const char* description);
        // Glfw window resize callback
        static void WindowResizeCallback(GLFWwindow* window, int width, int height);
    };
} // ara
