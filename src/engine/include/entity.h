#pragma once

#include <string>

#include <glm/glm.hpp>

#include "commons.h"

namespace ara {

    class ARA_API Entity {
    public:
        Entity();
        Entity(const std::string& name, const glm::vec2& position);
        ~Entity();

        // Methods

        // Called every frame when needed, the child entities of this class need to implement this method
        virtual void Render() = 0;

        // Called when editing the entity in the scene editor
        virtual void Edit() = 0;

        // Getters
        const std::string& GetName() const;
        const glm::vec2& GetPosition() const;
        const unsigned int GetUid() const;
        const std::string& GetType() const;

        // Setters
        void SetName(const std::string& name);
        void SetPosition(const glm::vec2& position);

        glm::vec3 gColor;

    protected:
        std::string mName;
        glm::vec2 mPosition;

        // Methods

        void Update();

        // Called when in edit mode, will edit name and position
        void BasicEdit();

        std::string mType;

    private:
        unsigned int mUid;
    };


}; // ara
