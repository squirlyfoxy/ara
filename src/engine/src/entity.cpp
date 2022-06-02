#include "entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_stdlib.h"

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

} // ara
