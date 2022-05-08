#pragma once

#include "commons.h"

#include <string>

namespace ara {

    // Returns the content of the file at the given path
    ARA_API const char* GetFileContent(const std::string& filePath);

} // ara
