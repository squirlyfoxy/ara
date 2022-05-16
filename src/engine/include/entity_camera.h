#include "entity.h"

#include "commons.h"

#include <glm/glm.hpp>

namespace ara {

    // Orthographic 2D camera
    class ARA_API EntityCamera : public Entity {
    public:
        EntityCamera();

        virtual void Render();

        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;

    private:
    
    };
}
