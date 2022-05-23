#include "utils_editor.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 GetEditorProjectionMatrix() {
    return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

glm::mat4 GetEditorViewMatrix() {
    return glm::mat4(1.0f);
}
