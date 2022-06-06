#include "entity_empty.h"

namespace ara {

    EntityEmpty::EntityEmpty() {
        mName = "Empty entity";

        mPosition = glm::vec2(0.0f, 0.0f);
        mType = "EntityEmpty";
    }

    // Render the camera
    void EntityEmpty::Render() {
        // NOTE: Nothing
    }

    void EntityEmpty::Save(std::ofstream& file) {
        // NOTE: Nothing
    }

    void EntityEmpty::CustomLoad(std::istringstream& file) {
        // NOTE: Nothing
    }

    void EntityEmpty::Edit() {
        BasicEdit();

        // TODO: CAMERA SETTINGS
    }
    
} // ara
