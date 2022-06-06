#pragma once

#include "commons.h"

#include <vector>
#include <string>

namespace ara {

    // Returns the content of the file at the given path
    ARA_API const char* GetFileContent(const std::string& filePath);

    // Get files by extension
    ARA_API std::vector<std::string> GetFilesByExtension(const std::string& path, const std::string& extension);

} // ara
