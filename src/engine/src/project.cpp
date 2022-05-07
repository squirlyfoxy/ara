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

    bool Project::Validate() {
        // Read the first line from the file, and check if the version is correct
        std::ifstream fs;
        fs.open(mBasePath + "/" + mName + ".ara");
        if (!fs.is_open()) {
            return false;
        }

        std::string line;
        std::getline(fs, line);
        fs.close();

        // The line should be "ARA [version]"
        if (line.substr(0, 4) != "ARA ") {
            return false;
        }

        // Check the version
        std::string version = line.substr(4);
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

    void Project::SetBasePath(const std::string& basePath) {
        mBasePath = basePath;
    }

    void Project::SetName(const std::string& name) {
        mName = name;
    }

    void Project::SetCreationTime(const std::chrono::system_clock::time_point& creationTime) {
        mCreationTime = creationTime;
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
