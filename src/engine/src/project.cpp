#include "project.h"

#include "version.hpp"

namespace ara {

    Project::Project() {
        // DEFAULT CONSTRUCTOR, DO NOT USE
    }

    Project::Project(const std::string& name) {
        mName = name;

        // Set the creation time
        mCreationTime = std::chrono::system_clock::now();

        // Create a default scene
        gScenes.push_back(Scene("Default"));
    }

    Project::~Project() {
    }

    const std::string& Project::GetName() const {
        return mName;
    }

    const std::chrono::system_clock::time_point& Project::GetCreationTime() const {
        return mCreationTime;
    }

    void Project::SetBasePath(const std::string& basePath) {
        mBasePath = basePath;
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

        // In a basic project, there isn't any scene
    }

} // ara
