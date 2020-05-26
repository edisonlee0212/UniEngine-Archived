#include "Rendering.h"
using namespace UniEngine;

RenderTarget* Rendering::_CurrentRenderTarget;
uint Rendering::_DrawCall;
uint Rendering::_Triangles;

void UniEngine::Rendering::DrawMeshInstanced(Mesh* mesh, Material* material, float4x4* matrices, size_t count, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMeshInstanced(mesh, material, matrices, count);
}

void UniEngine::Rendering::DrawMesh(Mesh* mesh, float4x4 matrix, Material* material, RenderTarget* target)
{
	if (_CurrentRenderTarget != target) {
		target->Bind();
		_CurrentRenderTarget = target;
	}
	DrawMesh(mesh, matrix, material);
}

void UniEngine::Rendering::DrawMeshInstanced(Mesh* mesh, Material* material, float4x4* matrices, size_t count)
{
	_CurrentRenderTarget->BindDefault();
	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	auto amount = count;
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float4x4), matrices, GL_STATIC_DRAW);
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
			uint diffuseNr = 0;
			uint specularNr = 0;
			uint normalNr = 0;
			uint heightNr = 0;
			std::string name = "";
			uint size = -1;
			for (auto j = 0; j < tsize; j++)
			{
				auto texture = textures->at(j);
				texture->Texture()->Activate(GL_TEXTURE0 + j);
				switch (textures->at(j)->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					break;
				case TextureType::AMBIENT:
					size = specularNr;
					name = "AMBIENT";
					break;
				case TextureType::EMISSIVE:
					size = specularNr;
					name = "EMISSIVE";
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					break;
				default:
					break;
				}
				//"materials[" + std::to_string(size) + name, i;
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", i);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		else {
			//glActiveTexture(GL_TEXTURE0);
			//glUniform1i(glGetUniformLocation(pointMaterial->shader->ID, "materials[0].diffuse"), 0);
			// and finally bind the texture
			//glBindTexture(GL_TEXTURE_2D, Default::Textures::MissingTexture->ID());
		}
		glDrawElementsInstanced(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0, count);
		glActiveTexture(GL_TEXTURE0);
	}
	GLVAO::BindDefault();
}
void UniEngine::Rendering::DrawMesh(Mesh* mesh, float4x4 matrix, Material* material)
{
	_CurrentRenderTarget->BindDefault();
	mesh->VAO()->Bind();
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
			uint diffuseNr = 0;
			uint specularNr = 0;
			uint normalNr = 0;
			uint heightNr = 0;
			std::string name = "";
			uint size = -1;
			for (auto j = 0; j < tsize; j++)
			{
				auto texture = textures->at(j);
				texture->Texture()->Activate(GL_TEXTURE0 + j);
				switch (textures->at(j)->Type())
				{
				case TextureType::DIFFUSE:
					size = diffuseNr;
					name = "DIFFUSE";
					diffuseNr++;
					break;
				case TextureType::SPECULAR:
					size = specularNr;
					name = "SPECULAR";
					break;
				case TextureType::AMBIENT:
					size = specularNr;
					name = "AMBIENT";
					break;
				case TextureType::EMISSIVE:
					size = specularNr;
					name = "EMISSIVE";
					break;
				case TextureType::HEIGHT:
					size = heightNr;
					name = "HEIGHT";
					break;
				case TextureType::NORMAL:
					size = normalNr;
					name = "NORMAL";
					break;
				default:
					break;
				}
				//"materials[" + std::to_string(size) + name, i;
				if (size != -1) program->SetInt("TEXTURE_" + name + "[" + std::to_string(size) + "]", i);
				texture->Texture()->Bind(GL_TEXTURE_2D);
			}
		}
		else {
			//glActiveTexture(GL_TEXTURE0);
			//glUniform1i(glGetUniformLocation(pointMaterial->shader->ID, "materials[0].diffuse"), 0);
			// and finally bind the texture
			//glBindTexture(GL_TEXTURE_2D, Default::Textures::MissingTexture->ID());
		}

		glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
	}
	GLVAO::BindDefault();
}
