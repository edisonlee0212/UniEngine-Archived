#include "Default.h"
#include "UniEngine.h"
#include "ModelManager.h"
#include "MeshMaterialComponent.h"
using namespace UniEngine;

EngineDriver* engine;

void LoadModelAsEntity(std::string path, glm::vec3 position, glm::vec3 scale) {
    Entity* suit = engine->GetWorld()->_EntityCollection->CreateEntity();
    Position t;
    t.value = position;
    Scale s;
    s.value = scale;
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(suit, t);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(suit, s);

    ModelManager::LoadModelAsEntity(suit, path, Default::GLPrograms::StandardProgram);
}

void InitGround() {
    auto entity = engine->GetWorld()->_EntityCollection->CreateEntity();
    Position translation = Position();
    translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
    Scale scale = Scale();
    scale.value = glm::vec3(20.0f);
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(entity, translation);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(entity, scale);

    auto mat = new Material();
    mat->Programs()->push_back(Default::GLPrograms::StandardProgram);
    auto texture = new Texture2D(TextureType::DIFFUSE);
    texture->LoadTexture(FileIO::GetPath("Textures/floor.png"), "");
    mat->Textures2Ds()->push_back(texture);
    mat->SetMaterialProperty("material.shininess", 32.0f);
    MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
    meshMaterial->_Mesh = Default::Primitives::Quad;
    meshMaterial->_Material = mat;
    engine->GetWorld()->_EntityCollection->SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);
}

int main()
{
    engine = new EngineDriver();
    engine->Start();

    
    LoadModelAsEntity(std::string("Resources/Models/nanosuit/nanosuit.obj"), 
        glm::vec3(0.0f, 0.0f, -4.0f), glm::vec3(0.5f));
    LoadModelAsEntity(std::string("Resources/Models/backpack/backpack.obj"), 
        glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f));

    InitGround();
    
    bool loopable = true;
    while (loopable) {
        loopable = engine->Loop();
    }
    
    engine->End();
    return 0;
}


