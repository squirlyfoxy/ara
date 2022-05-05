#include "scene.h"

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

} // ara
