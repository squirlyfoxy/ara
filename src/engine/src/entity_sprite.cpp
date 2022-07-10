#include "entity_sprite.h"

#include <iostream>
#include <stdlib.h>

#include <lib/json.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils_transforms.h"
#include "utils_fluids.h"
#include "utils_data.h"
#include "shader.h"

#include "gl_global_buffers.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace ara {

    static Shader* sSpriteShader = nullptr;

    EntitySprite::EntitySprite() {
        mType = "EntitySprite";
        mName = "Sprite";

        Init();

        // Edit modalities
        mEditModalities = {
            EntityEditModality::Textures
        };
    }

    void EntitySprite::Init() {    
        if (sSpriteShader == nullptr) sSpriteShader = new Shader("./shaders/base.vert", "./shaders/base_textured.frag");
        if (GetGBuffer("spr_buffer") == nullptr) InitGBufferSquare();

        if (mTextures.size() == 0) {
            mTextures.push_back(new Texture("./assets/textures/default.png"));
        }
    }

    void EntitySprite::Render(bool selected) {
        //if (selected) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        sSpriteShader->Use();
        mTextures[mCurrentFrame]->Bind(0);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.0f));
        model = glm::scale(model, glm::vec3(mSize.x, mSize.y, 1.0f));

        sSpriteShader->SetMat4("view", GetView());
        sSpriteShader->SetMat4("proj", GetProjection());
        sSpriteShader->SetMat4("model", model);
        sSpriteShader->SetInt("u_uid", (int)GetUid());

        glBindVertexArray(GetGBuffer("sq_buffer")->buffers[ARA_GLOBAL_BUFFER_VAO_LOCATION]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //if (selected) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void EntitySprite::Edit() {
        BasicEdit();

        ara::CustomerData engine;
        engine = ARA_GET_CUSTOMER_DATA("engine_gui");

        // Get files
        std::vector<ara::File> files;
        files = ara::GetFiles(engine.mData["current_path"] + engine.mData["current_scene"] + "/assets/textures/");

        // checkbox
        bool checkbox = mFPS > 0;
        ImGui::Checkbox("Animated", &checkbox);

        if (checkbox) {
            if (mFPS == 0) mFPS = 8;

            ImGui::SliderInt("FPS", &mFPS, 0, 60);
        } else {
            mFPS = 0;

            if (files.size() == 0) {
                ImGui::Text("No textures found");
            } else {
                ImGui::Text("Choose a texture");
                ImGui::Separator();
                int selected = 0;
                for (int i = 0; i < files.size(); i++) {
                    if (ImGui::Selectable(files[i].Path.c_str(), mTextures[0]->GetPath() == files[i].Path)) {
                        mTextures.clear();
                        mTextures.push_back(new Texture(files[i].Path));
                    }
                }
            }
        }
    }

    void EntitySprite::Save(std::ofstream& file) {
        file << "textures" << std::endl;
        file << "{" << std::endl;
        file << "\"paths\":[" << std::endl;
        for (Texture* tex : mTextures) {
            file << "\"" << tex->GetPath() << "\"," << std::endl;
        }
        // Remove from the last line ","
        file.seekp(-2, std::ios_base::end);
        file << std::endl;

        file << "]," << std::endl;
        file << "\"FPS\": " << mFPS << std::endl;
        file << "}" << std::endl;
    }

    void EntitySprite::CustomLoad(std::istringstream& file) {
        nlohmann::json json;

        // remove textures line
        std::string line;
        std::getline(file, line);
        if (line != "textures") {
            std::cout << "Error: expected textures line" << std::endl;
            exit(1);
        }

        // read textures
        file >> json;
        mFPS = json["FPS"];
        mTextures.clear();
        for (auto& tex : json["paths"]) {
            mTextures.push_back(new Texture(tex.get<std::string>()));
        }
    }

} // ara
