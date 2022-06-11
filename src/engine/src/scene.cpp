#include "scene.h"

#include "lib/json.hpp"

#include "utils_fluids.h"
#include "utils_data.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace ara {

    Scene::Scene() {
        // DEFAULT CONSTRUCTOR, DO NOT USE
    }

    Scene::Scene(const std::string& name) {
        mName = name;
    }

    Scene::~Scene() {
    }

    void Scene::Render(bool physics) {
        if (physics) Update();

        for (auto& entity : GetEntities()) {
            // If ARA_GET_CUSTOMER_DATA("entities") is not empty, then we will use it
            bool selected = nlohmann::json::parse(ARA_GET_CUSTOMER_DATA("entities").mData[entity->GetName()]).at("if_selected");

            entity->Render(selected);
        }

        for (auto& text : gTexts) {
            text->Render();
        }
    }

    void Scene::Update() {
        // TODO: Update the physics
    }

    const std::string& Scene::GetName() const {
        return mName;
    }

    std::vector<Entity*> Scene::GetEntities() {
        return gEntities;
    }

    void Scene::AddEntity(Entity *entity) {
        gEntities.push_back(entity);

        // Add the entity to the entities list
        CustomerData data = ARA_GET_CUSTOMER_DATA("entities");

        nlohmann::json j;
        j["name"] = entity->GetName();
        j["if_selected"] = false;

        data.mData[entity->GetName()] = j.dump();

        ARA_SET_CUSTOMER_DATA("entities", data);
    }

    void Scene::Save(const std::string scene_path, Scene& scene) {
        // Create a [scene_name].sara file in the scene path
        std::ofstream scene_file(scene_path + "/" + scene.GetName() + ".sara", std::ios::trunc);
            // Erase the file
            scene_file.seekp(0, std::ios::end);
            scene_file.seekp(0, std::ios::beg);

            // Write the scene name
            scene_file.write((scene.GetName() + "\n").c_str(), scene.GetName().size() + 1);

            // Write the entities
            for (auto entity : scene.GetEntities()) {
                // Write the entity name
                scene_file.write((entity->GetName() + "\n").c_str(), entity->GetName().size() + 1);

                // Create a file for the entity (.ent)
                std::ofstream entity_file(scene_path + "/" + entity->GetName() + ".ent", std::ios::trunc);
                    // Erase the file
                    entity_file.seekp(0, std::ios::end);
                    entity_file.seekp(0, std::ios::beg);

                    Entity::Save(entity_file, *entity);

                    // TODO: ENTITY DATA

                entity_file.close();
            }
        scene_file.close();
    }
    
    void Scene::Load(const std::string scene_path, Scene& scene) {
        std::istringstream scene_file(GetFileContent(scene_path + "/" + scene.GetName() + ".sara"));
            // First line the name, the following the name of the entities
            std::string line;
            std::getline(scene_file, line);

            scene.mName = line;

            while (std::getline(scene_file, line)) {
                // Create a file for the entity (.ent)t
                std::istringstream entity_file(GetFileContent(scene_path + "/" + line + ".ent"));
                    // First line the type and name, the following the position of the entity
 
                    Entity* entity = Entity::Load(entity_file);

                    // TODO: ENTITY RELATED DESERIALIZATION

                    // Add the entity to the scene
                    scene.AddEntity(entity);
            }
    }

} // ara
