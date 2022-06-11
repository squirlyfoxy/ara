#pragma once

#include <vector>
#include <string>
#include <memory>

#include "entity.h"
#include "render_text.h"

#include "commons.h"

namespace ara {

    // Scenes are saved as .sara binary files, to access these you will need to use the assets manager
    class ARA_API Scene {
    public:
        Scene();
        Scene(const std::string& name);
        ~Scene();

        // Methods

        void Render(bool physics = true); // Will render the scene

        // Getters

        const std::string& GetName() const; // Get the name of the scene
        std::vector<Entity*> GetEntities(); // Get all the entities in the scene

        // Add an entity to the scene
        void AddEntity(Entity *entity);

        static void Save(const std::string scene_path, Scene& scene); // Save the scene to a file
        static void Load(const std::string scene_path, Scene& scene); // Load the scene from a file

        std::vector<Text*> gTexts; // All the texts in the scene
        std::vector<Entity*> gEntities;

    private:
        std::string mName;

        // Methods

        void Update(); // Will update the physics

        
    };

} // ara

