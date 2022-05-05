#pragma once

#include <vector>
#include <string>
#include <chrono>

#include "commons.h"

#include "scene.h"

namespace ara {

    // Projects are saved as .ara binary files.
    // When a project is distributed, only scenes saved (in gane database there will be the list of them).
    class ARA_API Project {
    public:
        Project();
        Project(const std::string& name);
        ~Project();

        // Getters

        const std::string& GetName() const; // Get the name of the project

        // All scenes in the project
        std::vector<Scene> gScenes;

    private:
        std::string mName;
        std::chrono::system_clock::time_point mCreationTime;    // When the project was created
    };

} // ara
