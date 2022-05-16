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

        // Getters
        const std::string& GetName() const;
        const glm::vec2& GetPosition() const;
        const unsigned int GetUid() const;

        // Setters
        void SetName(const std::string& name);
        void SetPosition(const glm::vec2& position);

    private:
        unsigned int mUid;

        std::string mName;
        glm::vec2 mPosition;

        // Methods

        void Update();
    };

}; // ara
