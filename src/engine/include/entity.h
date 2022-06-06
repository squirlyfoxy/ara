#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>

#include "commons.h"

namespace ara {

    enum class EntityEditModality {
        Color,
        Texture
    };

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

        // Static methods
        static void     Save(std::ofstream& file, Entity& entity);
        static Entity*  Load(std::istringstream& file);

    protected:
        std::string mName;
        glm::vec2 mPosition;

        std::vector<EntityEditModality> mEditModalities;

        // Methods

        void Update();

        // Called when in edit mode, will edit name and position
        void BasicEdit();

        // Called when saving the entity to a file
        virtual void Save(std::ofstream& file) = 0;

        // Called when we need to deserialize the entity from a file
        virtual void CustomLoad(std::istringstream& file) = 0;

        std::string mType;

    private:
        unsigned int mUid;
    };


}; // ara
