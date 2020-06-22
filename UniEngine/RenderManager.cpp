#include "pch.h"
#include "RenderManager.h"
#include "LightingManager.h"
using namespace UniEngine;

GLenum RenderManager::_TextureStartIndex = 2;
RenderTarget* RenderManager::_CurrentRenderTarget;
unsigned RenderManager::_DrawCall;
unsigned RenderManager::_Triangles;


void UniEngine::RenderManager::DrawMeshInstanced(InstancedMeshMaterialComponent* immc, glm::mat4 matrix, glm::mat4* matrices, size_t count, Camera* camera)
{
	DrawMeshInstanced(immc->_Mesh, immc->_Material, matrix, matrices, count, camera);
}

void UniEngine::RenderManager::DrawMesh(MeshMaterialComponent* mmc, glm::mat4 matrix, Camera* camera)
{
	DrawMesh(mmc->_Mesh, mmc->_Material, matrix, camera);
}

void UniEngine::RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count, Camera* camera)
{
	DrawMeshInstanced(mesh, material, matrix, matrices, count, camera->GetRenderTarget());
}

void UniEngine::RenderManager::DrawMesh(Mesh* mesh, Material* material, glm::mat4 matrix, Camera* camera)
{
	DrawMesh(mesh, material, matrix, camera->GetRenderTarget());
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMeshInstanced(mesh, material, matrix, matrices, count);
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 matrix, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMesh(mesh, material, matrix);
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count)
{
	GLVBO* matricesBuffer = new GLVBO();
	matricesBuffer->SetData(count * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->Enable();
	GLVAO::EnableAttributeArray(12);
	GLVAO::SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	GLVAO::EnableAttributeArray(13);
	GLVAO::SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	GLVAO::EnableAttributeArray(14);
	GLVAO::SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	GLVAO::EnableAttributeArray(15);
	GLVAO::SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	GLVAO::SetAttributeDivisor(12, 1);
	GLVAO::SetAttributeDivisor(13, 1);
	GLVAO::SetAttributeDivisor(14, 1);
	GLVAO::SetAttributeDivisor(15, 1);
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() * count / 3;
		auto program = programs->at(i);
		program->Bind();
		GLTexture::Activate(GL_TEXTURE0);
		program->SetInt("directionalShadowMap", 0);
		LightingManager::_DirectionalLightShadowMap->DepthCubeMapArray()->Bind(GL_TEXTURE_2D_ARRAY);
		GLTexture::Activate(GL_TEXTURE1);
		program->SetInt("pointShadowMap", 1);
		LightingManager::_PointLightShadowMap->DepthCubeMapArray()->Bind(GL_TEXTURE_CUBE_MAP_ARRAY);

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
		glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);
		GLTexture::BindDefault();
	}
	GLVAO::BindDefault();
	delete matricesBuffer;
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 matrix)
{
	mesh->Enable();
	GLVAO::DisableAttributeArray(12);
	GLVAO::DisableAttributeArray(13);
	GLVAO::DisableAttributeArray(14);
	GLVAO::DisableAttributeArray(15);
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Bind();
		GLTexture::Activate(GL_TEXTURE0);
		program->SetInt("directionalShadowMap", 0);
		LightingManager::_DirectionalLightShadowMap->DepthCubeMapArray()->Bind(GL_TEXTURE_2D_ARRAY);
		GLTexture::Activate(GL_TEXTURE1);
		program->SetInt("pointShadowMap", 1);
		LightingManager::_PointLightShadowMap->DepthCubeMapArray()->Bind(GL_TEXTURE_CUBE_MAP_ARRAY);
		
		
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

