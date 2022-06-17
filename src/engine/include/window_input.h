#pragma once

#include "commons.h"

#ifndef ARA_WEB

#define NO_GL
#include <GLFW/glfw3.h>

#define MAX_KEYS    1024
#define MAX_BUTTONS 32

namespace ara {

    class ARA_API InputManager
    {
    public:
        InputManager(GLFWwindow* window);
        ~InputManager();

        void Reset();

        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);

        static double GetMouseX();
        static double GetMouseY();

        static double GetScrollX();
        static double GetScrollY();

        bool CanUpdate();
        bool CanScrollUpdate();
        void SetCanUpdate(bool canUpdate);

    private:
        // Keyboard callback
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        // Mouse button callback
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        // Mouse position callback
        static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
        // Scroll callback
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    };
} // ara

#endif
