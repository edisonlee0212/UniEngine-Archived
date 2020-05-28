#include "Default.h"
#include "UniEngine.h"
#include "ModelManager.h"
#include "MeshMaterialComponent.h"
using namespace UniEngine;

EngineDriver* engine;

void LoadBackpack(glm::vec3 position, glm::vec3 scale, std::string* vertShaderCode, std::string* fragShaderCode) {
    Entity* suit = engine->GetWorld()->_EntityCollection->CreateEntity();
    Position t;
    t.value = position;
    Scale s;
    s.value = scale;
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(suit, t);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(suit, s);
    GLProgram* program = new GLProgram(
        new GLShader(ShaderType::Vertex, vertShaderCode),
        new GLShader(ShaderType::Fragment, fragShaderCode));
    ModelManager::LoadModel(suit, "Resources/Models/backpack/backpack.obj", program);
}

void LoadNanoSuit(glm::vec3 position, glm::vec3 scale, std::string* vertShaderCode, std::string* fragShaderCode) {
    Entity* suit = engine->GetWorld()->_EntityCollection->CreateEntity();
    Position t;
    t.value = position;
    Scale s;
    s.value = scale;
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(suit, t);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(suit, s);
    GLProgram* program = new GLProgram(
        new GLShader(ShaderType::Vertex, vertShaderCode),
        new GLShader(ShaderType::Fragment, fragShaderCode));
    ModelManager::LoadModel(suit, "Resources/Models/nanosuit/nanosuit.obj", program);
}

void InitGround(std::string* vertShaderCode, std::string* fragShaderCode) {
    auto entity = engine->GetWorld()->_EntityCollection->CreateEntity();
    Position translation = Position();
    translation.value = glm::vec3(0.0f, 0.0f, 0.0f);
    Scale scale = Scale();
    scale.value = glm::vec3(10.0f);
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(entity, translation);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(entity, scale);
    
    //entity->SetSharedComponent<Mesh>(Default::Primitives::Quad);
    auto mat = new Material();
    mat->Programs()->push_back(
        new GLProgram(
            new GLShader(ShaderType::Vertex, vertShaderCode),
            new GLShader(ShaderType::Fragment, fragShaderCode)
        )
    );
    auto texture = new Texture2D(TextureType::DIFFUSE);
    texture->LoadTexture(FileIO::GetPath("Textures/white.png"), "");
    mat->Textures2Ds()->push_back(texture);
    MeshMaterialComponent* meshMaterial = new MeshMaterialComponent();
    meshMaterial->_Mesh = Default::Primitives::Quad;
    meshMaterial->_Material = mat;
    engine->GetWorld()->_EntityCollection->SetSharedComponent<MeshMaterialComponent>(entity, meshMaterial);
}

int main()
{
    engine = new EngineDriver();
    engine->Start();

    std::string vertShaderCode = std::string("#version 460 core")
        + "\n"
        + *Default::ShaderIncludes::MainCamera +
        +"\n"
        + FileIO::LoadFileAsString("Resources/Shaders/Vertex/Default.vert");


    std::string fragShaderCode = std::string("#version 460 core")
        + "\n"
        + *Default::ShaderIncludes::MainCamera
        + "\n"
        + *Default::ShaderIncludes::Material
        + "\n"
        + *Default::ShaderIncludes::Lights
        + "\n"
        + FileIO::LoadFileAsString("Resources/Shaders/Fragment/Default.frag");

    //LoadNanoSuit(glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(1.0f), &vertShaderCode, &fragShaderCode);

    LoadBackpack(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f), &vertShaderCode, &fragShaderCode);

    InitGround(&vertShaderCode, &fragShaderCode);
    engine->Loop();
    engine->End();
    return 0;
}


