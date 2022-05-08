#include "window_input.h"

namespace ara {

    static bool gKeys[MAX_KEYS];
    static bool gMouseButtons[MAX_BUTTONS];
    static double gMouseX, gMouseY;

    // **********************************

    InputManager::InputManager(GLFWwindow* window)
    {
        for (int i = 0; i < MAX_KEYS; i++) gKeys[i] = false;
        for (int i = 0; i < MAX_BUTTONS; i++) gMouseButtons[i] = false;

        // Set callbacks
        glfwSetKeyCallback(window, KeyCallback); // Keyboard
        glfwSetMouseButtonCallback(window, MouseButtonCallback); // Mouse button
        glfwSetCursorPosCallback(window, MousePositionCallback); // Mouse position
    }

    InputManager::~InputManager()
    {
    }

    bool InputManager::IsKeyPressed(int key)
    {
        if (key < 0 || key >= MAX_KEYS) return false;

        return gKeys[key];
    }

    bool InputManager::IsMouseButtonPressed(int button)
    {
        if (button < 0 || button >= MAX_BUTTONS) return false;

        return gMouseButtons[button];
    }

    double InputManager::GetMouseX()
    {
        return gMouseX;
    }

    double InputManager::GetMouseY()
    {
        return gMouseY;
    }

    // **********************************

    void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        gKeys[key] = action != GLFW_RELEASE;
    }

    void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        gMouseButtons[button] = action != GLFW_RELEASE;
    }

    void InputManager::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        gMouseX = xpos;
        gMouseY = ypos;
    }

}
