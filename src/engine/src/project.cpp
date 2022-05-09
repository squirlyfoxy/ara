#include "project.h"

#include "utils_fluids.h"

#include <iostream>
#include <sstream>

#include "version.hpp"

namespace ara {

    Project::Project() {
        mCurrentSceneIndex = 0;

        // DEFAULT CONSTRUCTOR, DO NOT USE
    }

    Project::Project(const std::string& name) {
        mName = name;
        mCurrentSceneIndex = 0;

        // Set the creation time
        mCreationTime = std::chrono::system_clock::now();

        // Create a default scene
        gScenes.push_back(Scene("Default"));
    }

    Project::~Project() {
    }

    bool Project::Validate() {
        // Read the first line from the file, and check if the version is correct
        std::ifstream fs;
        fs.open(mBasePath + "/" + mName + ".ara");
        if (!fs.is_open()) {
            return false;
        }

        std::string fL;
        std::string sL;
        std::string tL;

        std::getline(fs, fL);
        std::getline(fs, sL);
        std::getline(fs, tL);
        fs.close();

        // The line should be "ARA [version]"
        if (fL.substr(0, 4) != "ARA ") {
            return false;
        }
/*
        if (sL != std::to_string(mCreationTime.time_since_epoch().count())) {
            std::cout << "Creation time is not correct" << std::endl;
            std::cout << "Expected: " << sL << std::endl;
            std::cout << "Actual: " << mCreationTime.time_since_epoch().count() << std::endl;
            return false;
        }
*/
        if (tL != mName) {
            std::cout << "Project name is not correct" << std::endl;
            return false;
        }

        // Check the version
        std::string version = fL.substr(4);
        if (version != std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR)) {
            return false;
        }

        return true;
    }

    const std::string& Project::GetName() const {
        return mName;
    }

    const std::string& Project::GetBasePath() const {
        return mBasePath;
    }

    const std::chrono::system_clock::time_point& Project::GetCreationTime() const {
        return mCreationTime;
    }

    Scene Project::GetCurrentScene() const {
        return gScenes[mCurrentSceneIndex];
    }

    void Project::SetBasePath(const std::string& basePath) {
        mBasePath = basePath;
    }

    void Project::SetName(const std::string& name) {
        mName = name;
    }

    void Project::SetCreationTime(const std::chrono::system_clock::time_point& creationTime) {
        mCreationTime = creationTime;
    }

    void Project::SetCurrentScene(const Scene& scene) {
        for (int i = 0; i < gScenes.size(); i++) {
            if (gScenes[i].GetName() == scene.GetName()) {
                mCurrentSceneIndex = i;
                return;
            }
        }
    }



    void Project::InitializeBasicProject(std::ofstream *fs, const Project& project) {
        // STRUCTURE FO THE FILE
        //

        // ARA [version]
        // [creation time]
        // [name]
        // Scene [name] ....

        fs->write(std::string("ARA " + std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR) + "\n").c_str(), std::string("ARA " + std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR) + "\n").size());
        fs->write(std::to_string(project.mCreationTime.time_since_epoch().count()).c_str(), std::to_string(project.mCreationTime.time_since_epoch().count()).size()); fs->write("\n", 1);
        fs->write(project.mName.c_str(), project.mName.size()); fs->write("\n", 1);

        for (auto& scene : project.gScenes) {
            fs->write("Scene ", 6);
            fs->write(scene.GetName().c_str(), scene.GetName().size());
            fs->write("\n", 1);
        }

        // In a basic project, there isn't any scene
    }

    Project Project::ReadProject(const std::string& path) {
        Project project;

        // Read the file
        const char* content = GetFileContent(path);

        // Loop through the file lines
        std::string line;
        std::stringstream ss(content);
        int l_count = 0;
        while (std::getline(ss, line)) {
            l_count++;

            // Check if starts with "ARA "
            if (line.substr(0, 4) == "ARA ") {
                // Check the version
                std::string version = line.substr(4);
                if (version != std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR)) {
                    std::cout << "Wrong version" << std::endl;
                    return project;
                }

                continue;
            }

            if (l_count == 2) {
                // Set the creation time
                //project.SetCreationTime(std::chrono::system_clock::from_time_t(std::stoi(line)));
                continue;
            }

            if (l_count == 3) {
                // Set the name
                project.SetName(line);
                continue;
            }

            if (line.substr(0, 6) == "Scene ") {
                std::cout << "Scene found" << std::endl;

                // Add the scene
                Scene scene = Scene(line.substr(6));
                project.gScenes.push_back(scene);
                continue;
            }
        }

        return project;
    }

} // ara
