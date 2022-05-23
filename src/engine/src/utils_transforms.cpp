#include "utils_transforms.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ara {

    static std::function<glm::mat4()> projection_callback = nullptr;
    static std::function<glm::mat4()> view_callback = nullptr;

    void SetProjectionCallback(std::function<glm::mat4()> callback) {
        projection_callback = callback;
    }

    void SetViewCallback(std::function<glm::mat4()> callback) {
        view_callback = callback;
    }

    glm::mat4 GetProjection() {
        if (projection_callback == nullptr) {
            return glm::mat4(1.0f);
        }

        return projection_callback();
    }

    glm::mat4 GetView() {
        if (view_callback == nullptr) {
            return glm::mat4(1.0f);
        }

        return view_callback();
    }

} // ara
