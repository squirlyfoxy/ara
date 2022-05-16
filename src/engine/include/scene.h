#pragma once

#include <vector>
#include <string>

#include "entity.h"

#include "commons.h"

namespace ara {

    // Scenes are saved as .sara binary files, to access these you will need to use the assets manager
    class ARA_API Scene {
    public:
        Scene();
        Scene(const std::string& name);
        ~Scene();

        // Methods

        void Render(); // Will render the scene

        // Getters

        const std::string& GetName() const; // Get the name of the scene
        std::vector<Entity*> GetEntities() const; // Get the entities of the scene

        static void Save(const std::string scene_path, const Scene& scene); // Save the scene to a file

    private:
        std::string mName;

        // Methods

        void Update(); // Will update the physics

        std::vector<Entity*> mEntities;
    };

} // ara

