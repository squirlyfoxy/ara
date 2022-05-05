#include "project.h"

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

} // ara
