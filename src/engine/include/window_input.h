#pragma once

#include <GLFW/glfw3.h>
#include "commons.h"

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

namespace ara {

    class ARA_API InputManager
    {
    public:
        InputManager(GLFWwindow* window);
        ~InputManager();

        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);

        static double GetMouseX();
        static double GetMouseY();

    private:
        // Keyboard callback
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        // Mouse button callback
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        // Mouse position callback
        static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);

    };
} // namespace ara
