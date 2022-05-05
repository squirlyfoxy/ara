#include "entity.h"

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

} // ara
