#include "RenderManager.h"
#include "LightingManager.h"
using namespace UniEngine;
GLenum RenderManager::_TextureStartIndex = 2;
RenderTarget* RenderManager::_CurrentRenderTarget;
unsigned RenderManager::_DrawCall;
unsigned RenderManager::_Triangles;

void UniEngine::RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, size_t count, Camera* camera)
{

	DrawMeshInstanced(mesh, material, matrices, count, camera->GetRenderTarget());
}

void UniEngine::RenderManager::DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, Camera* camera)
{
	DrawMesh(mesh, matrix, material, camera->GetRenderTarget());
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4* matrices, size_t count, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMeshInstanced(mesh, material, matrices, count);
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, glm::mat4 matrix, Material* material, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMesh(mesh, matrix, material);
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4* matrices, size_t count)
{
	unsigned buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	auto amount = count;
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->VAO()->Bind();
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Use();
		for (auto j : material->_FloatPropertyList) {
			program->SetFloat(j.first, j.second);
		}
		for (auto j : material->_Float4x4PropertyList) {
			program->SetFloat4x4(j.first, j.second);
		}
		if (material->Textures2Ds()->size() != 0) {
			auto textures = material->Textures2Ds();
			auto tsize = textures->size();
			unsigned diffuseNr = 0;
			unsigned ambientNr = 0;
			unsigned emissiveNr = 0;
			unsigned heightNr = 0;
			unsigned specularNr = 0;
			unsigned normalNr = 0;

			for (auto j = 0; j < tsize; j++)
			{
				std::string name = "";
				int size = -1;
				auto texture = textures->at(j);
				texture->Texture()->Activate(GL_TEXTURE0 + _TextureStartIndex + j);
				switch (texture->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					specularNr++;
					break;
				case TextureType::AMBIENT:
					size = ambientNr;
					name = "AMBIENT";
					ambientNr++;
					break;
				case TextureType::EMISSIVE:
					size = emissiveNr;
					name = "EMISSIVE";
					emissiveNr++;
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					heightNr++;
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					normalNr++;
					break;
				default:
					break;
				}
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", _TextureStartIndex + j);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		mesh->VAO()->Bind();
		glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, amount);
		GLTexture::BindDefault();
	}
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, glm::mat4 matrix, Material* material)
{
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Use();
		program->SetFloat3("lightPos", LightingManager::_LightPos);
		program->SetFloat3("lightDir", LightingManager::_LightDir);
		program->SetFloat4x4("lightSpaceMatrix", LightingManager::_LightSpaceMatrix);

		GLTexture::Activate(GL_TEXTURE0);
		program->SetInt("shadowMap", 0);
		LightingManager::_DirectionalLightShadowMap->DepthMap()->Bind(GL_TEXTURE_2D);
		
		program->SetFloat4x4("model", matrix);
		for (auto j : material->_FloatPropertyList) {
			program->SetFloat(j.first, j.second);
		}
		for (auto j : material->_Float4x4PropertyList) {
			program->SetFloat4x4(j.first, j.second);
		}
		if (material->Textures2Ds()->size() != 0) {
			auto textures = material->Textures2Ds();
			auto tsize = textures->size();
			unsigned diffuseNr = 0;
			unsigned ambientNr = 0;
			unsigned emissiveNr = 0;
			unsigned heightNr = 0;
			unsigned specularNr = 0;
			unsigned normalNr = 0;

			for (auto j = 0; j < tsize; j++)
			{
				std::string name = "";
				int size = -1;
				auto texture = textures->at(j);
				
				GLTexture::Activate(GL_TEXTURE0 + _TextureStartIndex + j);
				switch (texture->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					specularNr++;
					break;
				case TextureType::AMBIENT:
					size = ambientNr;
					name = "AMBIENT";
					ambientNr++;
					break;
				case TextureType::EMISSIVE:
					size = emissiveNr;
					name = "EMISSIVE";
					emissiveNr++;
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					heightNr++;
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					normalNr++;
					break;
				default:
					break;
				}
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", _TextureStartIndex + j);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		mesh->VAO()->Bind();
		glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
		GLTexture::BindDefault();
	}
	GLVAO::BindDefault();
}

void UniEngine::RenderManager::Start()
{
	RenderManager::_CurrentRenderTarget = nullptr;
	_Triangles = 0;
	_DrawCall = 0;
}
unsigned UniEngine::RenderManager::Triangles()
{
	return _Triangles;
}

unsigned UniEngine::RenderManager::DrawCall()
{
	return _DrawCall;
}
