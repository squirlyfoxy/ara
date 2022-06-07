#pragma once

#include <glm/glm.hpp>

#include "commons.h"
#include "entity.h"

namespace ara {

    // Will be the main entity for characters, word static objects, etc.
    class ARA_API EntitySquare : public Entity {
    public:
        EntitySquare();

        virtual void Render(bool selected = false);
        virtual void Edit();

    protected:
        virtual void Save(std::ofstream& file);
        virtual void CustomLoad(std::istringstream& file);

    private:

        void Init();
    };

} // ara
