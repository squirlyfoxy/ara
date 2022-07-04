#include "gui_window.h"

#include "entity.h"

class ImWindowEntities : public ImWindow {
public:
    ImWindowEntities(std::string name);
    ~ImWindowEntities();

    virtual void Draw();

private:
    bool gui_edit_entity_open = false;
    bool selected_from_tree = false;
    ara::Entity* selected_entity;

    void edit_entity();

};
