#include "entity.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_stdlib.h"

#include "entity_camera.h"
#include "entity_square.h"
#include "entity_empty.h"

namespace ara {

    Entity::Entity() {
        // DEFAULT CONSTRUCTOR, DO NOT USE
    }

    Entity::Entity(const std::string& name, const glm::vec2& position) {
        mName = name;
        mPosition = position;

        // TODO: UID
    }

    Entity::~Entity() {
    }

    void Entity::SetName(const std::string& name) {
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

    const unsigned int Entity::GetUid() const {
        return mUid;
    }

    const std::string& Entity::GetType() const {
        return mType;
    }

    void Entity::BasicEdit() {
        // Position
        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::InputFloat2("##Position", glm::value_ptr(mPosition));

        // Name
        ImGui::Text("Name");
        ImGui::SameLine();
        std::string name = mName;
        ImGui::InputText("##Name", &name);
        if (!name.empty()) {
            SetName(name);
        }

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
    
        entity.Save(file);
    }

    Entity* Entity::Load(std::istringstream& file) {
        Entity *entity = nullptr;

        std::string entity_line;
        std::getline(file, entity_line);

        std::string type_name = entity_line;
        std::string type = type_name.substr(0, type_name.find("|"));
        std::string name = type_name.substr(type_name.find("|") + 1);

        std::getline(file, entity_line);
        std::string position = entity_line;

        // color
        std::getline(file, entity_line);
        std::string color = entity_line;

        // Create the entity
        if (type == "EntityCamera") {
            entity = new EntityCamera();
        } else if (type == "EntitySquare") {
            entity = new EntitySquare();
        } else if (type == "EntityEmpty") {
            entity = new EntityEmpty();
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

        // Custom deserialization
        entity->CustomLoad(file);

        return entity;
    }

} // ara
