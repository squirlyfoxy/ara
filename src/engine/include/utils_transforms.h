#pragma once

#include <functional>

#include <glm/glm.hpp>

namespace ara {

    void SetProjectionCallback(std::function<glm::mat4()> callback);
    void SetViewCallback(std::function<glm::mat4()> callback);

    glm::mat4 GetProjection();
    glm::mat4 GetView();

} // ara
