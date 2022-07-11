#pragma once

#include "commons.h"
#include "render_text.h"
#include "entity.h"

namespace ara {

    // Will be the main entity for characters, word static objects, etc.
    class ARA_API EntityText : public Entity {
    public:
        EntityText();

        virtual void Render(bool selected = false);
        virtual void Edit();

        void SetText(const std::string& text);

    protected:
        virtual void Save(std::ofstream& file);
        virtual void CustomLoad(std::istringstream& file);

    private:
        int mSelected_font_size = 0;
        ara::Text* mTextEntity;

        void Init();
    };

} // ara
