#include "scene.h"

#include "entity_camera.h"
#include "entity_square.h"

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

    void Scene::AddEntity(Entity* entity) {
        mEntities.push_back(entity);
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

                    // Write the entity name and type ([type]|[name])
                    entity_file.write((entity->GetType() + "|" + entity->GetName() + "\n").c_str(), entity->GetType().size() + entity->GetName().size() + 2);

                    // Write the entity position (in one line, x and y separated by a space)
                    entity_file.write((std::to_string(entity->GetPosition().x) + " " + std::to_string(entity->GetPosition().y) + "\n").c_str(), (std::to_string(entity->GetPosition().x) + " " + std::to_string(entity->GetPosition().y) + "\n").size());

                entity_file.close();
            }
        scene_file.close();
    }
    
    void Scene::Load(const std::string scene_path, Scene& scene) {
        std::ifstream scene_file(scene_path + "/" + scene.GetName() + ".sara");
            // First line the name, the following the name of the entities
            std::string line;
            std::getline(scene_file, line);

            scene.mName = line;

            while (std::getline(scene_file, line)) {
                // Create a file for the entity (.ent)
                std::ifstream entity_file(scene_path + "/" + line + ".ent");
                    // First line the type and name, the following the position of the entity
                    std::string entity_line;
                    std::getline(entity_file, entity_line);

                    std::string type_name = entity_line;
                    std::string type = type_name.substr(0, type_name.find("|"));
                    std::string name = type_name.substr(type_name.find("|") + 1);

                    std::getline(entity_file, entity_line);
                    std::string position = entity_line;

                    // Create the entity
                    // TODO: MOVE THIS TO A FUNCTION
                    Entity* entity = nullptr;
                    if (type == "EntityCamera") {
                        entity = new EntityCamera();
                    } else if (type == "EntitySquare") {
                        entity = new EntitySquare();
                    }

                    entity->SetName(name);

                    // Set the position
                    entity->SetPosition(glm::vec2(std::stof(position.substr(0, position.find(" "))), std::stof(position.substr(position.find(" ") + 1))));

                    // Add the entity to the scene
                    scene.AddEntity(entity);
                entity_file.close();
            }

        scene_file.close();
    }

} // ara
