#include "entity_text.h"

#include <iostream>

#include "lib/json.hpp"
#include "conf/conf_fnts.h"

#include <imgui.h>
#include <imgui_stdlib.h>

namespace ara {

    EntityText::EntityText() {
        mTextEntity = new Text("Hello Word", "", glm::vec2(0.0f, 0.0f), 0.01f, glm::vec3(1.0f, 1.0f, 1.0f));
        mTextEntity->mFont = "arial";

        mType = "EntityText";
        mName = "Text";

        // Edit modalities
        mEditModalities = {
            EntityEditModality::Color
        };
    }

    void EntityText::Render(bool selected) {
        mTextEntity->mPosition = mPosition;
        mTextEntity->mColor = gColor;

        mTextEntity->Render(true);
    }

    // Possible dimensions: 10, 12, 14, 16... to 48
    static std::vector<const char*> font_sizes = {
        "10", "12", "14", "16", "18", "20", "22", "24", "26", "28", "30", "32", "34", "36", "38", "40", "42", "44", "46", "48"
    };

    void EntityText::Edit() {
        BasicEdit();

        ImGui::Text("Text");
        ImGui::SameLine();
        ImGui::InputText("##Text", &mTextEntity->mText);

        // selected_font_size is equal to the size of the text * 10000, this is because ImGui::Combo() works with ints
        int to_find = mTextEntity->mSize * 10000;
        for (int i = 0; i < font_sizes.size(); i++) {
            if (atoi(font_sizes[i]) == to_find) {
                mSelected_font_size = i;
                break;
            }
        }

        ImGui::Text("Size");
        ImGui::SameLine();
        ImGui::Combo("##Size", &mSelected_font_size, font_sizes.data(), font_sizes.size());

        auto fonts = ara::conf::GetFnts();
        int selected_font = std::find(fonts.begin(), fonts.end(), mTextEntity->mFont) - fonts.begin();
        ImGui::Text("Font");
        ImGui::SameLine();
        std::vector<const char*> font_names;
        for (auto& font : fonts) {
            font_names.push_back(font.c_str());
        }
        ImGui::Combo("##Font", &selected_font, font_names.data(), fonts.size());
        mTextEntity->mFont = fonts[selected_font];

        mTextEntity->mSize = std::stof(font_sizes[mSelected_font_size]) / 10000.0f;
    }

    void EntityText::SetText(const std::string& text) {
        mTextEntity->SetText(text);
    }

    void EntityText::Save(std::ofstream& file) {
        file << "text" << std::endl;

        file << "{" << std::endl;
        file << "    \"text\": \"" << mTextEntity->mText << "\"," << std::endl;
        file << "    \"font\": \"" << mTextEntity->mFont << "\"," << std::endl;
        file << "    \"size\": " << mTextEntity->mSize << std::endl;
        file << "}" << std::endl;
    }

    void EntityText::CustomLoad(std::istringstream& file) {
        nlohmann::json json;
    
        // Remove "text" line
        std::string line;
        std::getline(file, line);
        if (line != "text") {
            std::cout << "Error: Expected \"text\" line, got \"" << line << "\"" << std::endl;
            exit(1);
        }

        file >> json;

        mTextEntity->SetText(json["text"]);
        mTextEntity->mFont = json["font"];
        mTextEntity->mSize = json["size"];
        mTextEntity->mColor = gColor;
    }

} // ara
