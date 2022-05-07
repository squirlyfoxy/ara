#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <fstream>

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

        bool Validate();

        // Getters

        const std::string& GetName() const; // Get the name of the project
        const std::string& GetBasePath() const; // Get the base path of the project
        const std::chrono::system_clock::time_point& GetCreationTime() const; // Get the creation time of the project

        // Setters

        void SetName(const std::string& name); // Set the name of the project
        void SetBasePath(const std::string& basePath); // Set the base path of the project
        void SetCreationTime(const std::chrono::system_clock::time_point& creationTime); // Set the creation time of the project

        // All scenes in the project
        std::vector<Scene> gScenes;

        static void InitializeBasicProject(std::ofstream *fs, const Project& project);

    private:
        std::string mName;
        std::string mBasePath;
        std::chrono::system_clock::time_point mCreationTime;    // When the project was created
    };

} // ara
