#pragma once


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
        const std::chrono::system_clock::time_point& GetCreationTime() const; // Get the creation time of the project

        Scene GetCurrentScene() const; // Get the current scene of the project

        // Setters

        void SetName(const std::string& name); // Set the name of the project
        void SetCreationTime(const std::chrono::system_clock::time_point& creationTime); // Set the creation time of the project
        void SetCurrentScene(const Scene& scene); // Set the current scene of the project

        // All scenes in the project
        std::vector<Scene> gScenes;

        static void Save(std::ofstream *fs, const Project& project);

        static Project ReadProject(const std::string& path);

    private:
        std::string mName;
        std::chrono::system_clock::time_point mCreationTime;    // When the project was created
    
        int mCurrentSceneIndex;
    };

} // ara
