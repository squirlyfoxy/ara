#pragma once

#include <map>

#include "project.h"

class ProjectManager {
public:
    ProjectManager();
    ~ProjectManager();

    // Getters

    ara::Project* GetCurrentProject();

    void SetCurrentProject(std::string projectName);
    void AddProject(ara::Project project);
    int GetProjectCount();

    void RenderProjectEditor();

    std::vector<std::string> GetProjects();

private:
    std::string mCurrentProject;
    ara::Project mCurrentProjectData;
    
    std::vector<std::string> mProjects;

    void CreateProjectEnviroment(ara::Project project);
};

ProjectManager* GetProjectManager();

