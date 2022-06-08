#pragma once

#include "commons.h"

#include <vector>
#include <string>
#include <iterator>

namespace ara {

    enum class FileType {
        Scene,
        Entity,
        Directory,
        Project,
        GenericFile
    };

    struct File {
        // File name
        std::string Name;

        // File path
        std::string Path;

        // Type
        FileType Type;

        bool operator == (const File& other) const {
            return Name == other.Name && Path == other.Path;
        }

        bool operator != (const File& other) const {
            return !(*this == other);
        }
    };

    // Returns the content of the file at the given path
    ARA_API const char* GetFileContent(const std::string& filePath);

    // Returns the size of the file at the given path
    ARA_API long FileSize(const std::string& filePath);

    // Get files by extension
    ARA_API std::vector<File> GetFilesByExtension(const std::string& path, const std::string& extension);

    // Get all files in the given path
    ARA_API std::vector<File> GetFiles(const std::string& path);

} // ara
