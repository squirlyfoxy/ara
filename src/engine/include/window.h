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
        void SetRenderUpdate(std::function<void()> renderUpdate);

    private:
        int mWidth, mHeight;
        std::string mTitle;
    
        GLFWwindow* mWindow;

        // Methods
        std::function<void()> mRenderUpdate;
        bool mRenderUpdateSet = false;

        // Initialize glfw
        void Init();
        // Glfw error callback
        static void ErrorCallback(int error, const char* description);

    };
} // ara
