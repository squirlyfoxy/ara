#include "project_manager.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <SQLiteCpp/SQLiteCpp.h>

namespace fs = std::filesystem;

ProjectManager mProjectManager;

ProjectManager::ProjectManager() {
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

        // Create a new project
        ara::Project project;
        project.SetName(projectName);
        project.SetBasePath(projectPath);
        project.SetCreationTime(std::chrono::system_clock::from_time_t(std::stoul(projectCreationTime)));

        // Add the project to the map
        mProjects[projectName] = project;
    }
}

ProjectManager::~ProjectManager() {
}

ara::Project* ProjectManager::GetCurrentProject() {
    return &mProjects[mCurrentProject];
}

void ProjectManager::SetCurrentProject(std::string projectName) {
    // Check if project exists
    if (mProjects.find(projectName) == mProjects.end()) {
        return;
    }

    mCurrentProject = projectName;
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
        ara::Project::InitializeBasicProject(&projectFile, project); // Will initialize the project file
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
    if (mProjects.find(project.GetName()) != mProjects.end()) {
        return;
    }

    CreateProjectEnviroment(project);

    // Add the project to the list of projects
    mProjects[project.GetName()] = project;
}

void ProjectManager::ProjectEditor() {
    // TODO: Implement project editor
}

std::map<std::string, ara::Project> ProjectManager::GetProjects() {
    return mProjects;
}

ProjectManager* GetProjectManager() {
    // Return the global project manager, pointer
    return &mProjectManager;
}

