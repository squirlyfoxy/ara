#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "texture.h"

#include "commons.h"
#include "entity.h"

namespace ara {

    // Will be the main entity for characters, word static objects, etc.
    class ARA_API EntitySprite : public Entity {
    public:
        EntitySprite();

        virtual void Render(bool selected = false);
        virtual void Edit();

    protected:
        virtual void Save(std::ofstream& file);
        virtual void CustomLoad(std::istringstream& file);

    private:

        void Init();

        std::vector<Texture*> mTextures;
        unsigned int mFPS = 0; // if 0 not animated
        unsigned int mCurrentFrame = 0;

    };

} // ara
