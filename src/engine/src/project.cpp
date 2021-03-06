#include "project.h"

#include "lib/json.hpp"

#include "utils_fluids.h"
#include "utils_data.h"

#include <iostream>
#include <sstream>
#include <filesystem>

#include "version.hpp"

#include "entity_camera.h"

#ifndef ARA_WEB
namespace fs = std::filesystem;
#endif

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
        EntityCamera* camera = new EntityCamera();

        Scene def = Scene("Default");
        def.AddEntity(camera);
        gScenes.push_back(def);
    }

    Project::~Project() {
    }

    bool Project::Validate() {
        // Read the first line from the file, and check if the version is correct
        std::ifstream fs;
        fs.open("./projects/" + mName  + "/" + mName + ".ara");
        if (!fs.is_open()) {
            std::cout << "Project file not found" << std::endl;
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
            std::cout << "Invalid file format" << std::endl;
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
            std::cout << "Version is not correct" << std::endl;
            return false;
        }

        return true;
    }

    const std::string& Project::GetName() const {
        return mName;
    }

    const std::chrono::system_clock::time_point& Project::GetCreationTime() const {
        return mCreationTime;
    }

    Scene* Project::GetCurrentScene() {
        return &gScenes[mCurrentSceneIndex];
    }

    void Project::SetName(const std::string& name) {
        mName = name;
    }

    void Project::SetCreationTime(const std::chrono::system_clock::time_point& creationTime) {
        mCreationTime = creationTime;
    }

    void Project::SetCurrentScene(const Scene& scene) {
        if (gScenes[mCurrentSceneIndex].GetName() == scene.GetName()) {
            CustomerData engine = ARA_GET_CUSTOMER_DATA("engine");
            engine.mData["current_path"] = "./projects/" + mName + "/" + scene.GetName();
            ARA_SET_CUSTOMER_DATA("engine", engine);

            return;
        }

        for (int i = 0; i < gScenes.size(); i++) {
            if (gScenes[i].GetName() == scene.GetName()) {
                mCurrentSceneIndex = i;

                CustomerData entities;
                for (auto& e : gScenes[i].GetEntities()) {
                    // Save a json object with the entity data (we need name and if_selected)
                    nlohmann::json j;
                    j["name"] = e->GetName();
                    j["if_selected"] = false;

                    std::stringstream ss;
                    ss << j;

                    entities.mData[e->GetName()] = ss.str();
                }

                ARA_SET_CUSTOMER_DATA("entities", entities);

                // Update current path
                CustomerData engine = ARA_GET_CUSTOMER_DATA("engine");
                engine.mData["current_path"] = "./projects/" + mName + "/" + scene.GetName();
                ARA_SET_CUSTOMER_DATA("engine", engine);

                return;
            }
        }
    }



    void Project::Save(std::ofstream *fs, Project& project) {
        #ifndef ARA_WEB
        // STRUCTURE FO THE FILE
        //

        // ARA [version]
        // [creation time]
        // [name]
        // Scene [name] ....

        std::cout << "Saving " << project.GetName() << std::endl;

        fs->write(std::string("ARA " + std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR) + "\n").c_str(), std::string("ARA " + std::to_string(ara_VERSION_MAJOR) + "." + std::to_string(ara_VERSION_MINOR) + "\n").size());
        fs->write(std::to_string(project.mCreationTime.time_since_epoch().count()).c_str(), std::to_string(project.mCreationTime.time_since_epoch().count()).size()); fs->write("\n", 1);
        fs->write(project.mName.c_str(), project.mName.size()); fs->write("\n", 1);

        for (int i = 0; i < project.gScenes.size(); i++) {
            // Create folder for the scene
            if (!fs::exists("./projects/" + project.mName + "/" + project.gScenes[i].GetName())) {
                fs::create_directory("./projects/" + project.mName + "/" + project.gScenes[i].GetName());
            }

            std::cout << "-> Saving scene: " << project.gScenes[i].GetName() << std::endl;

            // Save the scene
            ara::Scene::Save("./projects/" + project.mName + "/" + project.gScenes[i].GetName(), project.gScenes[i]);
            fs->write("Scene ", 6);
            fs->write(project.gScenes[i].GetName().c_str(), project.gScenes[i].GetName().size());
            fs->write("\n", 1);

            // If first time saving this scene, create the assets folder
            if (!fs::exists("./projects/" + project.mName + "/" + project.gScenes[i].GetName() + "/assets")) {
                fs::create_directory("./projects/" + project.mName + "/" + project.gScenes[i].GetName() + "/assets");
                fs::create_directory("./projects/" + project.mName + "/" + project.gScenes[i].GetName() + "/assets/textures");
            }
        }
        #endif
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
                // Add the scene
                Scene scene = Scene(line.substr(6));

                // Read the scene
                ara::Scene::Load("./projects/" + project.mName + "/" + scene.GetName(), scene);

                project.gScenes.push_back(scene);
                continue;
            }
        }

        return project;
    }

} // ara
