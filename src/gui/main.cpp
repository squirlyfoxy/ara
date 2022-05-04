#include <version.hpp>

#include <iostream>

// ARA includes
#include <window.h>

int main() {
    std::cout << "Starting ARA version: " << ara_VERSION_MAJOR << "." << ara_VERSION_MINOR << "..." << std::endl;

    // Create a window
    ara::Window window(800, 600, "ARA Window");
    window.SetRenderUpdate(
        []() {
            // Render code goes here for editor
        }
    );
    window.Run();

    return 0;
}