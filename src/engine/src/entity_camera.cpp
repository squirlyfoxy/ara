#include "entity_camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ara {

    EntityCamera::EntityCamera() {
        mName = "Camera";

        mPosition = glm::vec2(0.0f, 0.0f);
        mType = "EntityCamera";
    }

    // Render the camera
    void EntityCamera::Render() {
        // NOTE: Nothing
    }

    const glm::mat4& EntityCamera::GetViewMatrix() const {
        return glm::lookAt(glm::vec3(mPosition, 0.0f), glm::vec3(mPosition, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    const glm::mat4& EntityCamera::GetProjectionMatrix() const {
        return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    }
    
} // ara
