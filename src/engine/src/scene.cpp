#include "scene.h"

#include <fstream>

namespace ara {

    Scene::Scene() {
        // DEFAULT CONSTRUCTOR, DO NOT USE
    }

    Scene::Scene(const std::string& name) {
        mName = name;
    }

    Scene::~Scene() {
    }

    void Scene::Render() {
        Update();

        // TODO: Render the scene
    }

    void Scene::Update() {
        // TODO: Update the physics
    }

    const std::string& Scene::GetName() const {
        return mName;
    }

    std::vector<Entity*> Scene::GetEntities() const {
        return mEntities;
    }

    void Scene::Save(const std::string scene_path, const Scene& scene) {
        // Create a [scene_name].sara file in the scene path
        std::ofstream scene_file(scene_path + "/" + scene.GetName() + ".sara", std::ios::trunc);
            // Erase the file
            scene_file.seekp(0, std::ios::end);
            scene_file.seekp(0, std::ios::beg);

            // Write the scene name
            scene_file.write((scene.GetName() + "\n").c_str(), scene.GetName().size() + 1);

            // Write the entities
            for (auto& entity : scene.GetEntities()) {
                // Write the entity name
                scene_file.write((entity->GetName() + "\n").c_str(), entity->GetName().size() + 1);

                // Create a file for the entity (.ent)
                std::ofstream entity_file(scene_path + "/" + entity->GetName() + ".ent", std::ios::trunc);
                    // Erase the file
                    entity_file.seekp(0, std::ios::end);
                    entity_file.seekp(0, std::ios::beg);

                    // Write the entity name
                    entity_file.write((entity->GetName() + "\n").c_str(), entity->GetName().size() + 1);

                    // Write the entity position (in one line, x and y separated by a space)
                    entity_file.write((std::to_string(entity->GetPosition().x) + " " + std::to_string(entity->GetPosition().y) + "\n").c_str(), (std::to_string(entity->GetPosition().x) + " " + std::to_string(entity->GetPosition().y) + "\n").size());

                entity_file.close();
            }
        scene_file.close();
    }

} // ara
