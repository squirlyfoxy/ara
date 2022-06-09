#pragma once

#include <string>

// Virtual base class for all windows.
class ImWindow {
public:
    ImWindow(std::string name);
    ~ImWindow();

    // Draws the window
    virtual void Draw() = 0;

    // Getters

    std::string GetName();
    bool IsOpen();

    // Setters

    void SetOpen(bool open);
    void SetName(std::string name);

protected:
    std::string name;
    bool open;
};
