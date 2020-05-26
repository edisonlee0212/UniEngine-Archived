
#include "UniEngine.h"
#include "ModelManager.h"
using namespace UniEngine;

EngineDriver* engine;
void LoadNanoSuit(float3 position, float3 scale, std::string* vertShaderCode, std::string* fragShaderCode) {
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
    translation.value = float3(0.0f, 0.0f, 0.0f);
    Scale scale = Scale();
    scale.value = float3(10.0f);
    engine->GetWorld()->_EntityCollection->SetFixedData<Position>(entity, translation);
    engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(entity, scale);
    entity->SetSharedComponent<Mesh>(Default::Primitives::Quad);
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
    entity->SetSharedComponent<Material>(mat);
}

int main()
{
    engine = new EngineDriver();
    engine->Start();

    std::string vertShaderCode = std::string("#version 420 core")
        + "\n"
        + *Default::ShaderIncludes::MainCamera +
        +"\n"
        + FileIO::LoadFileAsString("Resources/Shaders/Vertex/Default.vert");


    std::string fragShaderCode = std::string("#version 420 core")
        + "\n"
        + *Default::ShaderIncludes::MainCamera
        + "\n"
        + *Default::ShaderIncludes::Material
        + "\n"
        + *Default::ShaderIncludes::Lights
        + "\n"
        + FileIO::LoadFileAsString("Resources/Shaders/Fragment/Default.frag");

    LoadNanoSuit(float3(-4.0f, 0.0f, 0.0f), float3(1.0f), &vertShaderCode, &fragShaderCode);
    InitGround(&vertShaderCode, &fragShaderCode);
    engine->Loop();
    engine->End();
    return 0;
}


