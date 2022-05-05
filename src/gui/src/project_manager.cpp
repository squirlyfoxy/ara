#include "project_manager.h"

ProjectManager mProjectManager;

ProjectManager::ProjectManager() {
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

void ProjectManager::AddProject(ara::Project project) {
    // Add the given project to the list of projects, if already exists, return
    if (mProjects.find(project.GetName()) != mProjects.end()) {
        return;
    }

    // Add the project to the list of projects
    mProjects[project.GetName()] = project;
}

ProjectManager* GetProjectManager() {
    // Return the global project manager, pointer
    return &mProjectManager;
}

