#pragma once

#include "commons.h"
#include "entity.h"

namespace ara {

    // Will be the main entity for characters, word static objects, etc.
    class ARA_API EntitySquare : public Entity {
    public:
        EntitySquare();

        virtual void Render();
    private:
    };

} // ara