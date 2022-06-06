#include "window_input.h"

#include <iostream>

#include <glm/glm.hpp>

namespace ara {

    static bool gKeys[MAX_KEYS];
    static bool gMouseButtons[MAX_BUTTONS];
    static double gMouseX, gMouseY;
    static double gScrollX, gScrollY;

    static bool gCanUpdate = false;
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
        gScrollX = xoffset;
        gScrollY = yoffset;

        std::cout << "Scroll: " << xoffset << ", " << yoffset << std::endl;
    }

}
