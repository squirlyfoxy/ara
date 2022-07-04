#include "entity.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_stdlib.h"

#include "entity_camera.h"
#include "entity_square.h"
#include "entity_empty.h"
#include "entity_text.h"

#include "gui/gui.h"

#include "lib/json.hpp"

#include "utils_data.h"

namespace ara {

    static unsigned int sEntityCount = 0;

    Entity::Entity() {
        // DEFAULT CONSTRUCTOR, DO NOT USE

        mUid = sEntityCount++;
    }

    Entity::Entity(const std::string& name, const glm::vec2& position) {
        mName = name;
        mPosition = position;
        mUid = sEntityCount++;
    }

    Entity::~Entity() {
    }

    void Entity::SetName(const std::string& name) {
        auto entities = ARA_GET_CUSTOMER_DATA("entities");

        // Check if name is unique; if not, error
        for (auto& entity : entities.mData) {
            if (entity.first == name && !mAlreadyOnNameError) {
                mAlreadyOnNameError = true;
                    
                ara::gui::ErrorMessageBox("Error", "An entity with this name already exists");

                return;
            }
        }

        auto data = entities.mData[mName];
        nlohmann::json j = nlohmann::json::parse(data, nullptr, false);
        if (j.find("name") != j.end()) {
            j["name"] = name;
            data = j.dump();

            entities.mData[name] = data;

            ARA_SET_CUSTOMER_DATA("entities", entities);
        }

        mName = name;
    }

    void Entity::SetPosition(const glm::vec2& position) {
        mPosition = position;
    }

    const std::string& Entity::GetName() const {
        return mName;
    }

    const glm::vec2& Entity::GetPosition() const {
        return mPosition;
    }

    void Entity::SetSize(const glm::vec2& size) {
        mSize = size;
    }

    const glm::vec2& Entity::GetSize() const {
        return mSize;
    }

    const unsigned int Entity::GetUid() const {
        return mUid;
    }

    const std::string& Entity::GetType() const {
        return mType;
    }

    void Entity::BasicEdit() {
        std::string name = mName;
        
        // Name
        ImGui::Text("Name");
        ImGui::SameLine();
        ImGui::InputText("##Name", &name);
        if (!name.empty() && name != mName) {
            SetName(name);
        }

        // Position
        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::InputFloat2("##Position", glm::value_ptr(mPosition));

        // Size
        ImGui::Text("Size");
        ImGui::SameLine();
        ImGui::InputFloat2("##Size", glm::value_ptr(mSize));

        ImGui::Separator();
        ImGui::Text("Entity Specifics");
        for (int i = 0; i < mEditModalities.size(); i++) {
            switch (mEditModalities[i]) {
                case EntityEditModality::Color: // Edit base color
                    ImGui::Text("Color");
                    ImGui::SameLine();
                    ImGui::ColorEdit3("##Color", glm::value_ptr(gColor));
                    break;
            }
        }
    }

    void Entity::Save(std::ofstream& file, Entity& entity) {
        // Write the entity name and type ([type]|[name])
        file.write((entity.GetType() + "|" + entity.GetName() + "\n").c_str(), entity.GetType().size() + entity.GetName().size() + 2);

        // Write the entity position (in one line, x and y separated by a space)
        file.write((std::to_string(entity.GetPosition().x) + " " + std::to_string(entity.GetPosition().y) + "\n").c_str(), (std::to_string(entity.GetPosition().x) + " " + std::to_string(entity.GetPosition().y) + "\n").size());

        // Write the color
        file.write((std::to_string(entity.gColor.x) + " " + std::to_string(entity.gColor.y) + " " + std::to_string(entity.gColor.z) + "\n").c_str(), (std::to_string(entity.gColor.x) + " " + std::to_string(entity.gColor.y) + " " + std::to_string(entity.gColor.z) + "\n").size());
    
        // Write the size
        file.write((std::to_string(entity.GetSize().x) + " " + std::to_string(entity.GetSize().y) + "\n").c_str(), (std::to_string(entity.GetSize().x) + " " + std::to_string(entity.GetSize().y) + "\n").size());

        entity.Save(file);
    }

    Entity* Entity::Load(std::istringstream& file) {
        Entity *entity = nullptr;

        std::string entity_line;
        std::getline(file, entity_line);

        std::string type_name = entity_line;
        std::string type = type_name.substr(0, type_name.find("|"));
        std::string name = type_name.substr(type_name.find("|") + 1);

        // position
        std::getline(file, entity_line);
        std::string position = entity_line;

        // color
        std::getline(file, entity_line);
        std::string color = entity_line;

        // size
        std::getline(file, entity_line);
        std::string size = entity_line;

        // Create the entity
        if (type == "EntityCamera") {
            entity = new EntityCamera();
        } else if (type == "EntitySquare") {
            entity = new EntitySquare();
        } else if (type == "EntityEmpty") {
            entity = new EntityEmpty();
        } else if (type == "EntityText") {
            entity = new EntityText();
        } else {
            // TODO: ERROR

            std::cout << "ERROR: Unknown entity type: " << type << std::endl;
        }

        entity->SetName(name);

        // Set the position
        entity->SetPosition(glm::vec2(std::stof(position.substr(0, position.find(" "))), std::stof(position.substr(position.find(" ") + 1))));
        
        // Set the color
        float x = std::stof(color.substr(0, color.find(" ")));
        float y = std::stof(color.substr(color.find(" ") + 1, color.find(" ")));
        float z = std::stof(color.substr(color.find(" ") + 1));
        entity->gColor = glm::vec3(x, y, z);

        // Set the size
        x = std::stof(size.substr(0, size.find(" ")));
        y = std::stof(size.substr(size.find(" ") + 1));
        entity->SetSize(glm::vec2(x, y));

        // Custom deserialization
        entity->CustomLoad(file);

        return entity;
    }

} // ara
