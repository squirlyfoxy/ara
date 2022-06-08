#pragma once

#include "commons.h"

#include <vector>
#include <string>

namespace ara {

    struct File {
        // File name
        std::string Name;

        // File path
        std::string Path;

        bool operator == (const File& other) const {
            return Name == other.Name && Path == other.Path;
        }
    };

    // Returns the content of the file at the given path
    ARA_API const char* GetFileContent(const std::string& filePath);

    // Get files by extension
    ARA_API std::vector<File> GetFilesByExtension(const std::string& path, const std::string& extension);

} // ara
