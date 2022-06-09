#include "gui_window.h"

class ImWindowNewScene : public ImWindow {
public:
    ImWindowNewScene(std::string name);
    ~ImWindowNewScene();

    virtual void Draw();

private:
    std::string gui_scene_new_popup_scene_name = "";

};
