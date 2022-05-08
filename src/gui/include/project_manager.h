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

    void ProjectEditor();

    std::map<std::string, ara::Project> GetProjects();

private:
    std::string mCurrentProject;

    std::map<std::string, ara::Project> mProjects;

    void CreateProjectEnviroment(ara::Project project);
};

ProjectManager* GetProjectManager();

#define GET_PROJECT(...) GetProjectManager()->GetProjects()[__VA_ARGS__]
