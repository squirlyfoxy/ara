#pragma once

#include <string>

namespace ara {

    // Returns the content of the file at the given path
    const char* GetFileContent(const std::string& filePath);

} // namespace ara
