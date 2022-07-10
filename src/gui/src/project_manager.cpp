#include "project_manager.h"

#include "utils_editor.h"
#include "utils_fluids.h"
#include "utils_data.h"
#include "utils_transforms.h"
#include "gui_scene_editor.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include <SQLiteCpp/SQLiteCpp.h>

namespace fs = std::filesystem;

ProjectManager* mProjectManager;

ProjectManager::ProjectManager() {
    // Check if opengl is initialized
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
    }

    // Connect to editor_db.db3
    SQLite::Database editor_db("editor_db.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Create the projects table if it doesn't exist
    editor_db.exec("CREATE TABLE IF NOT EXISTS Projects (Name TEXT PRIMARY KEY, Path TEXT, Creation_Time TEXT)");

    // Get all projects from the database
    SQLite::Statement query(editor_db, "SELECT * FROM Projects");
    while (query.executeStep()) {
        // Get the project name
        std::string projectName = query.getColumn(0);

        // Get the project path
        std::string projectPath = query.getColumn(1);

        // Get the project creation time
        std::string projectCreationTime = query.getColumn(2);

        // Add the project to the map
        mProjects.push_back(projectName);
        //mCurrentProject = projectName;
    }

    // Set the current edited
    ara::CustomerData engine;
    engine.mData["current_path"] = "./projects/";
    engine.mData["current_project"] = "";
    engine.mData["current_scene"] = "";
    ARA_SET_CUSTOMER_DATA("engine_gui", engine);

    ara::SetProjectionCallback(std::bind(GetEditorProjectionMatrix));
    ara::SetViewCallback(std::bind(GetEditorViewMatrix));
}

ProjectManager::~ProjectManager() {
}

ara::Project* ProjectManager::GetCurrentProject() {
    if (mCurrentProject.empty()) {
        return nullptr;
    }

    return &mCurrentProjectData;
}

void ProjectManager::SetCurrentProject(std::string projectName) {
    // Check if project exists
    bool projectExists = false;
    for (auto& p : mProjects) {
        if (p == projectName) {
            projectExists = true;
        }
    }
    if (!projectExists) {
        return;
    }

    mCurrentProject = projectName;
    mCurrentProjectData = ara::Project::ReadProject("./projects/" + projectName + "/" + projectName + ".ara");
    if (!mCurrentProjectData.Validate()) {
        std::cout << "Project is invalid" << std::endl;
        mCurrentProjectData = ara::Project();
        return;
    }

    // Cleanup
    for (auto &scene : mCurrentProjectData.gScenes)
    {
        std::string path = "./projects/" + mCurrentProjectData.GetName() + "/" + scene.GetName();

        std::vector<ara::File> files = ara::GetFilesByExtension(path, ".ent");

        // Loop through all entities
        for (auto &ent : scene.GetEntities())
        {
            std::string ent_path = path + "/" + ent->GetName() + ".ent";

            // Remove ent_path from files
            for (auto &file : files)
            {
                if (file.Path == ent_path)
                {
                    files.erase(std::remove(files.begin(), files.end(), file), files.end());
                    break;
                }
            }
        }

        // Remove all files that are not entities
        for (auto &file : files)
        {
            fs::remove(file.Path);
        }
    }

    // Set the current scene
    if (mCurrentProjectData.gScenes.size() > 0) {
        mCurrentProjectData.SetCurrentScene(mCurrentProjectData.gScenes[0].GetName());
    }

    // Update the engine gui data
    ara::CustomerData engine;
    engine.mData["current_path"] = "./projects/" + projectName + "/";
    engine.mData["current_project"] = projectName;
    engine.mData["current_scene"] = mCurrentProjectData.GetCurrentScene()->GetName();
    ARA_SET_CUSTOMER_DATA("engine_gui", engine);
}

int ProjectManager::GetProjectCount() {
    return mProjects.size();
}

void ProjectManager::CreateProjectEnviroment(ara::Project project) {
    std::string path = "projects/" + project.GetName();

    // Create the project directory
    if (!fs::create_directory(path)) {
        return;
    }

    // Create the project file
    std::ofstream projectFile(path + "/" + project.GetName() + ".ara");
        ara::Project::Save(&projectFile, project); // Will initialize the project file
    projectFile.close();

    // Add the project to the database
    SQLite::Database editor_db("editor_db.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(editor_db, "INSERT INTO Projects VALUES (?, ?, ?)");
    query.bind(1, project.GetName());
    query.bind(2, path);
    query.bind(3, std::to_string(project.GetCreationTime().time_since_epoch().count()));
    query.exec();
}

void ProjectManager::AddProject(ara::Project project) {
    // Add the given project to the list of projects, if already exists, return
    for (auto& p : mProjects) {
        if (p == project.GetName()) {
            return;
        }
    }

    CreateProjectEnviroment(project);

    // Add the project to the list of projects
    mProjects.push_back(project.GetName());
}

void ProjectManager::RenderProjectEditor() {
    if (GetCurrentProject() == nullptr) {
        return;
    }

    // TODO: Implement project editor

    gui_render_scene_editor(*GetCurrentProject()->GetCurrentScene());
}

std::vector<std::string> ProjectManager::GetProjects() {
    return mProjects;
}

ProjectManager* GetProjectManager() {
    if (mProjectManager == nullptr) {
        mProjectManager = new ProjectManager();
    }

    return mProjectManager;
}

