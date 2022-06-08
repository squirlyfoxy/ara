#include "utils_fluids.h"

#include <fstream>
#include <filesystem>
#include <iostream>

namespace ara {

    const char* GetFileContent(const std::string& filePath) {
    #ifdef ARA_WEB
        // TODO: IF WEB, WE NEED TO USE A WEB API TO GET THE FILE CONTENT
        // TODO: DESIGN THE WEB REST API USING GOLANG

        return "";
    #else
        FILE* file = fopen(filePath.c_str(), "r");
        if (file == nullptr) {
            std::cout << "Failed to open file: " << filePath << std::endl;
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* fileContent = new char[fileSize + 1];
        fread(fileContent, 1, fileSize, file);

        fileContent[fileSize] = '\0';

        fclose(file);

        return fileContent;
    #endif
    }

    std::vector<File> GetFilesByExtension(const std::string& path, const std::string& extension) {
        std::vector<File> files;

    #ifdef ARA_WEB
        // TODO: IF WEB, NOT IMPLEMENTED YET
        return files;
    #else
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == extension) {
                files.push_back({
                    Name: entry.path().filename(),
                    Path: path + "/" + entry.path().filename().c_str()
                });
            }
        }

        return files;
    #endif
    }

} // namespace ara
