#pragma once

#include "entity.h"

#include "commons.h"

#include <glm/glm.hpp>

namespace ara {

    // Orthographic 2D camera
    class ARA_API EntityEmpty : public Entity {
    public:
        EntityEmpty();

        virtual void Render(bool selected = false);
        virtual void Edit();

    protected:
        virtual void Save(std::ofstream& file);
        virtual void CustomLoad(std::istringstream& file);

    private:
    
    };
}
