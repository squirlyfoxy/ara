#include "utils_fluids.h"

#include <fstream>
#include <filesystem>
#include <iostream>

#define ALL_DIRECTORY_ITERATOR(path) std::filesystem::directory_iterator(path)

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

    long FileSize(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        return file.tellg();
    }

    std::vector<File> GetFilesByExtension(const std::string& path, const std::string& extension) {
        std::vector<File> files;

    #ifdef ARA_WEB
        // TODO: IF WEB, NOT IMPLEMENTED YET
        return files;
    #else
        for (const auto& entry : ALL_DIRECTORY_ITERATOR(path)) {
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

    std::vector<File> GetFiles(const std::string& path) {
        std::vector<File> files;

    #ifdef ARA_WEB
        // TODO: IF WEB, NOT IMPLEMENTED YET
        return files;
    #else
        for (const auto& entry : ALL_DIRECTORY_ITERATOR(path)) {
            FileType type = FileType::GenericFile;
            if (entry.path().extension() == ".sara") {
                type = FileType::Scene;
            } else if (entry.path().extension() == ".ent") {
                type = FileType::Entity;
            } else if (entry.path().extension() == ".ara") {
                type = FileType::Project;
            } else {
                type = FileType::Directory;
            }

            files.push_back({
                Name: entry.path().filename(),
                Path: path + "/" + entry.path().filename().c_str(),
                Type: type
            });
        }

        return files;
    #endif
    }

} // namespace ara
