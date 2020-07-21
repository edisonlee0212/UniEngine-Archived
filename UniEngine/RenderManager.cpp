#include "pch.h"
#include "RenderManager.h"
#include "LightingManager.h"
using namespace UniEngine;

unsigned RenderManager::_DrawCall;
unsigned RenderManager::_Triangles;
bool RenderManager::_EnableNormalMapping = true;
void UniEngine::RenderManager::DrawMeshInstanced(InstancedMeshMaterialComponent* immc, glm::mat4 matrix, glm::mat4* matrices, size_t count, Camera* camera)
{
	DrawMeshInstanced(immc->_Mesh, immc->_Material, matrix, matrices, count, camera, immc->_ReceiveShadow);
}

void UniEngine::RenderManager::DrawMesh(MeshMaterialComponent* mmc, glm::mat4 matrix, Camera* camera)
{
	DrawMesh(mmc->_Mesh, mmc->_Material, matrix, camera, mmc->_ReceiveShadow);
}

void UniEngine::RenderManager::DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count, Camera* camera, bool receiveShadow)
{
	DrawMeshInstanced(mesh, material, matrix, matrices, count, camera->GetRenderTarget(), receiveShadow);
}

void UniEngine::RenderManager::DrawMesh(Mesh* mesh, Material* material, glm::mat4 matrix, Camera* camera, bool receiveShadow)
{
	DrawMesh(mesh, material, matrix, camera->GetRenderTarget(), receiveShadow);
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count, RenderTarget* target, bool receiveShadow)
{
		target->Bind();
		
	DrawMeshInstanced(mesh, material, matrix, matrices, count, receiveShadow);
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 matrix, RenderTarget* target, bool receiveShadow)
{
	target->Bind();
	DrawMesh(mesh, material, matrix, receiveShadow);
}

void UniEngine::RenderManager::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4 matrix, glm::mat4* matrices, size_t count, bool receiveShadow)
{
	GLVBO* matricesBuffer = new GLVBO();
	matricesBuffer->SetData(count * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->Enable();
	mesh->VAO()->EnableAttributeArray(12);
	mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	mesh->VAO()->EnableAttributeArray(13);
	mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(14);
	mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(15);
	mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	mesh->VAO()->SetAttributeDivisor(12, 1);
	mesh->VAO()->SetAttributeDivisor(13, 1);
	mesh->VAO()->SetAttributeDivisor(14, 1);
	mesh->VAO()->SetAttributeDivisor(15, 1);
	

	size_t textureStartIndex = 0;
	if (receiveShadow) {
		LightingManager::_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
		LightingManager::_PointLightShadowMap->DepthCubeMapArray()->Bind(1);
		textureStartIndex += 2;
	}
	GLint max = GLTexture::GetMaxAllowedTexture();
	if (material->Textures2Ds()->size() != 0) {
		for (auto texture : *material->Textures2Ds()) {
			if (textureStartIndex >= max) {
				Debug::Error("Max allowed texture exceeded!");
				break;
			}
			texture->Texture()->Bind(textureStartIndex);
			textureStartIndex++;
		}
	}

	auto programs = material->Programs();
	textureStartIndex = 0;
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() * count / 3;
		auto program = programs->at(i);
		program->Bind();
		program->SetBool("receiveShadow", receiveShadow);
		if (receiveShadow) {
			program->SetInt("directionalShadowMap", 0);
			program->SetInt("pointShadowMap", 1);
			textureStartIndex += 2;
		}
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
				if (size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) {
					program->SetInt("TEXTURE_" + name + std::to_string(size), j + textureStartIndex);
				}
				if (normalNr == 0) {
					program->SetInt("TEXTURE_NORMAL0", textureStartIndex);
					program->SetBool("enableNormalMapping", false);
				}
				else{
					program->SetBool("enableNormalMapping", _EnableNormalMapping);
				}
				if (specularNr == 0) {
					program->SetInt("TEXTURE_SPECULAR0", textureStartIndex);
					program->SetBool("enableSpecularMapping", false);
				}
				else {
					program->SetBool("enableSpecularMapping", true);
				}
			}
		}
		glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);
	}
	GLVAO::BindDefault();
	delete matricesBuffer;
}

void UniEngine::RenderManager::DrawMesh(
	Mesh* mesh, Material* material, glm::mat4 matrix, bool receiveShadow)
{
	mesh->Enable();
	mesh->VAO()->DisableAttributeArray(12);
	mesh->VAO()->DisableAttributeArray(13);
	mesh->VAO()->DisableAttributeArray(14);
	mesh->VAO()->DisableAttributeArray(15);

	size_t textureStartIndex = 0;
	if (receiveShadow) {
		LightingManager::_DirectionalLightShadowMap->DepthMapArray()->Bind(0);
		LightingManager::_PointLightShadowMap->DepthCubeMapArray()->Bind(1);
		textureStartIndex += 2;
	}
	GLint max = GLTexture::GetMaxAllowedTexture();
	if (material->Textures2Ds()->size() != 0) {
		for (auto texture : *material->Textures2Ds()) {
			if (textureStartIndex >= max) {
				Debug::Error("Max allowed texture exceeded!");
				break;
			}
			texture->Texture()->Bind(textureStartIndex);
			textureStartIndex++;
		}
	}

	auto programs = material->Programs();
	textureStartIndex = 0;
	for (auto i = 0; i < programs->size(); i++) {
		RenderManager::_DrawCall++;
		RenderManager::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Bind();
		program->SetBool("receiveShadow", receiveShadow);
		if (receiveShadow) {
			program->SetInt("directionalShadowMap", 0);
			program->SetInt("pointShadowMap", 1);
			
			textureStartIndex += 2;
		}
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
				if (size != -1 && size < Default::ShaderIncludes::MaxMaterialsAmount) {
					program->SetInt("TEXTURE_" + name + std::to_string(size), j + textureStartIndex);
				}
				if (normalNr == 0) {
					program->SetInt("TEXTURE_NORMAL0", textureStartIndex);
					program->SetBool("enableNormalMapping", false);
				}
				else{
					program->SetBool("enableNormalMapping", _EnableNormalMapping);
				}
				if (specularNr == 0) {
					program->SetInt("TEXTURE_SPECULAR0", textureStartIndex);
					program->SetBool("enableSpecularMapping", false);
				}
				else {
					program->SetBool("enableSpecularMapping", true);
				}
			}
		}
		glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
	}
	GLVAO::BindDefault();
}


void UniEngine::RenderManager::SetEnableNormalMapping(bool value)
{
	_EnableNormalMapping = value;
}

void UniEngine::RenderManager::Start()
{
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

