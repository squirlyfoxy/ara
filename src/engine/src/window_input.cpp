#include "window_input.h"

#include <iostream>

#include <glm/glm.hpp>

namespace ara {

    static bool gKeys[MAX_KEYS];
    static bool gMouseButtons[MAX_BUTTONS];
    static double gMouseX, gMouseY;
    static double gScrollX, gScrollY;

    static bool gCanUpdate = false;
    static bool gCanScrollUpdate = false;
    static int gUpdatesSinceMouse = 0;

    // **********************************

    InputManager::InputManager(GLFWwindow* window)
    {
        for (int i = 0; i < MAX_KEYS; i++) gKeys[i] = false;
        for (int i = 0; i < MAX_BUTTONS; i++) gMouseButtons[i] = false;

        // Set callbacks
        glfwSetKeyCallback(window, KeyCallback); // Keyboard
        glfwSetMouseButtonCallback(window, MouseButtonCallback); // Mouse button
        glfwSetCursorPosCallback(window, MousePositionCallback); // Mouse position
        glfwSetScrollCallback(window, ScrollCallback); // Scroll
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::Reset()
    {
        gScrollX = 0.0;
        gScrollY = 0.0;

        gCanScrollUpdate = false;
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

    double InputManager::GetScrollX()
    {
        return gScrollX;
    }

    double InputManager::GetScrollY()
    {
        return gScrollY;
    }

    bool InputManager::CanUpdate()
    {
        return gCanUpdate;
    }

    bool InputManager::CanScrollUpdate()
    {
        return gCanScrollUpdate;
    }

    void InputManager::SetCanUpdate(bool canUpdate)
    {
        gCanUpdate = canUpdate;
    }
    // **********************************

    void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_RELEASE) gCanUpdate = false;
        else gCanUpdate = true;

        gKeys[key] = action != GLFW_RELEASE;
    }

    void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_RELEASE) gCanUpdate = false;
        else gCanUpdate = true;

        gMouseButtons[button] = action != GLFW_RELEASE;
    }

    void InputManager::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        gMouseX = xpos;
        gMouseY = ypos;
    }

    void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        // If scroll is not zero, then we can update
        if (yoffset != 0) gCanScrollUpdate = true;
        else gCanScrollUpdate = false;

        gScrollX = xoffset;
        gScrollY = yoffset;
    }

}
