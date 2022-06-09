#include "gui_window.h"

class ImWindowExplorer : public ImWindow {
public:
    ImWindowExplorer(std::string name);
    ~ImWindowExplorer();

    virtual void Draw();

private:
    void Init();

};
