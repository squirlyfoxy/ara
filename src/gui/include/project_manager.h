#pragma once

#include <map>

#include "project.h"

class ProjectManager {
public:
    ProjectManager();
    ~ProjectManager();

    ara::Project* GetCurrentProject();
    void SetCurrentProject(std::string projectName);
    void AddProject(ara::Project project);
    int GetProjectCount();

private:
    std::string mCurrentProject;

    std::map<std::string, ara::Project> mProjects;
};

ProjectManager* GetProjectManager();