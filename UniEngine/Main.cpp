#include "UniEngine.h"
#include "ModelManager.h"
using namespace UniEngine;

EngineDriver* engine;
void LoadNanoSuit(float3 position, float3 scale, std::string* vertShaderCode, std::string* fragShaderCode) {
	Entity* suit = engine->GetWorld()->_EntityCollection->CreateEntity();
	Translation t;
	t.value = position;
	Scale s;
	s.value = scale;
	LocalToWorld ltw;
	ltw.value = TRS(t.value, float4(0.0f), s.value);
	engine->GetWorld()->_EntityCollection->SetFixedData<Translation>(suit, t);
	engine->GetWorld()->_EntityCollection->SetFixedData<Scale>(suit, s);
	engine->GetWorld()->_EntityCollection->SetFixedData<LocalToWorld>(suit, ltw);
	GLProgram* program = new GLProgram(
		new GLShader(ShaderType::Vertex, vertShaderCode),
		new GLShader(ShaderType::Fragment, fragShaderCode));
	ModelManager::LoadModel(suit, "Resources/Models/nanosuit/nanosuit.obj", program);
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

	LoadNanoSuit(float3(-4.0f, 0.0f, 0.0f), float3(0.2f), &vertShaderCode, &fragShaderCode);

	engine->Loop();
	engine->End();
	return 0;
}