#include "utils_fluids.h"

#include <fstream>
#include <iostream>

namespace ara {

    const char* GetFileContent(const std::string& filePath) {
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
    }

} // namespace ara
