#include "gui_window.h"

class ImWindowNewProject : public ImWindow {
public:
    ImWindowNewProject(std::string name);
    ~ImWindowNewProject();

    virtual void Draw();

private:
    char* gui_new_project_project_name;

};
