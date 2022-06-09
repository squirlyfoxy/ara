#include "gui_window.h"

class ImWindowOpenProject : public ImWindow {
public:
    ImWindowOpenProject(std::string name);
    ~ImWindowOpenProject();

    virtual void Draw();

private:
    std::string gui_project_open_popup_project_name = "";

};
