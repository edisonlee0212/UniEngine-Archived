#include "Rendering.h"
#include "GLTexture.h"
#include "GLBuffer.h"
using namespace UniEngine;

RenderTarget* Rendering::_CurrentRenderTarget;
unsigned Rendering::_DrawCall;
unsigned Rendering::_Triangles;

void UniEngine::Rendering::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4* matrices, size_t count, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMeshInstanced(mesh, material, matrices, count);
}

void UniEngine::Rendering::DrawMesh(
	Mesh* mesh, glm::mat4 matrix, Material* material, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMesh(mesh, matrix, material);
}

void UniEngine::Rendering::DrawMeshInstanced(
	Mesh* mesh, Material* material, glm::mat4* matrices, size_t count)
{
	_CurrentRenderTarget->BindDefault();
	unsigned buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	auto amount = count;
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), matrices, GL_STATIC_DRAW);
	mesh->VAO()->Bind();
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		Rendering::_DrawCall++;
		Rendering::_Triangles += mesh->Size() * count / 3;
		auto program = programs->at(i);
		program->Use();
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
				texture->Texture()->Activate(GL_TEXTURE0 + j);
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
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", j);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);

		GLTexture::BindDefault();
	}GLVAO::BindDefault();
}

void UniEngine::Rendering::DrawMesh(
	Mesh* mesh, glm::mat4 matrix, Material* material)
{
	_CurrentRenderTarget->BindDefault();
	
	auto programs = material->Programs();
	for (auto i = 0; i < programs->size(); i++) {
		Rendering::_DrawCall++;
		Rendering::_Triangles += mesh->Size() / 3;
		auto program = programs->at(i);
		program->Use();
		program->SetFloat4x4("model", matrix);
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
				texture->Texture()->Activate(GL_TEXTURE0 + j);
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
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", j);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		mesh->VAO()->Bind();
		glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
		GLTexture::BindDefault();
	}
	GLVAO::BindDefault();
}
