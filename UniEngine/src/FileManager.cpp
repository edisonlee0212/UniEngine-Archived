#include "pch.h"
#include "TransformManager.h"
#include "FileManager.h"

#include <filesystem>

#include "MeshRenderer.h"
#include <stb_image.h>
#include "EntityManager.h"
#include "Default.h"
#include "SerializationManager.h"
#include "Application.h"
using namespace UniEngine;
bool FileManager::_EnableAssetMenu = true;
std::vector<std::shared_ptr<Model>> FileManager::_Models;
std::vector<std::shared_ptr<Texture2D>> FileManager::_Texture2Ds;
std::vector<std::shared_ptr<Cubemap>> FileManager::_Cubemaps;
std::vector<std::shared_ptr<Material>> FileManager::_Materials;
std::vector<std::shared_ptr<Mesh>> FileManager::_Meshes;
std::shared_ptr<Model> UniEngine::FileManager::LoadModel(std::string const& path, std::shared_ptr<GLProgram> shader, bool gamma, unsigned flags)
{
	stbi_set_flip_vertically_on_load(true);
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, flags);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		Debug::Log("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
		return nullptr;
	}
	// retrieve the directory path of the filepath
	std::string directory = path.substr(0, path.find_last_of('/'));
	std::vector<std::shared_ptr<Texture2D>> Texture2DsLoaded;
	auto retVal = std::make_shared<Model>();
	ProcessNode(directory, shader, retVal->RootNode(), Texture2DsLoaded, scene->mRootNode, scene);
	_Models.push_back(retVal);
	return retVal;
}

Entity UniEngine::FileManager::ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model)
{
	Entity entity = EntityManager::CreateEntity(archetype);
	entity.SetName(model->Name);
	Transform ltp;
	std::unique_ptr<ModelNode>& modelNode = model->RootNode();
	EntityManager::SetComponentData<Transform>(entity, ltp);
	for (auto& i : modelNode->_MeshMaterials) {
		auto mmc = std::make_unique<MeshRenderer>();
		mmc->Mesh = i.second;
		mmc->Material = i.first;
		EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(mmc));
	}
	int index = 0;
	for (auto& i : modelNode->Children) {
		AttachChildren(archetype, i, entity, model->Name + "_" + std::to_string(index));
		index++;
	}
	return entity;
}

void FileManager::ProcessNode(std::string directory, std::shared_ptr<GLProgram> shader, std::unique_ptr<ModelNode>& modelNode, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiNode* node, const aiScene* scene)
{
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		// the modelNode object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, modelNode is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ReadMesh(i, modelNode, directory, shader, Texture2DsLoaded, mesh, scene);
		modelNode->_LocalToParent = glm::mat4(
			node->mTransformation.a1, node->mTransformation.a2, node->mTransformation.a3, node->mTransformation.a4,
			node->mTransformation.b1, node->mTransformation.b2, node->mTransformation.b3, node->mTransformation.b4,
			node->mTransformation.c1, node->mTransformation.c2, node->mTransformation.c3, node->mTransformation.c4,
			node->mTransformation.d1, node->mTransformation.d2, node->mTransformation.d3, node->mTransformation.d4
		);
	}
	for (unsigned i = 0; i < node->mNumChildren; i++)
	{
		std::unique_ptr<ModelNode> childNode = std::make_unique<ModelNode>();
		ProcessNode(directory, shader, childNode, Texture2DsLoaded, node->mChildren[i], scene);
		modelNode->Children.push_back(std::move(childNode));
	}
}

void FileManager::ReadMesh(unsigned meshIndex, std::unique_ptr<ModelNode>& modelNode, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene) {
	unsigned mask = 1;
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	// Walk through each of the mesh's vertices
	for (unsigned i = 0; i < aimesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 v3; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		v3.x = aimesh->mVertices[i].x;
		v3.y = aimesh->mVertices[i].y;
		v3.z = aimesh->mVertices[i].z;
		vertex.Position = v3;
		if (aimesh->mNormals) {
			v3.x = aimesh->mNormals[i].x;
			v3.y = aimesh->mNormals[i].y;
			v3.z = aimesh->mNormals[i].z;
			vertex.Normal = v3;
			mask = mask | (1 << 1);
		}
		if (aimesh->mTangents) {
			v3.x = aimesh->mTangents[i].x;
			v3.y = aimesh->mTangents[i].y;
			v3.z = aimesh->mTangents[i].z;
			vertex.Tangent = v3;
			mask = mask | (1 << 2);
		}
		glm::vec4 v4;
		if (aimesh->mColors[0]) {
			v4.x = aimesh->mColors[0][i].r;
			v4.y = aimesh->mColors[0][i].g;
			v4.z = aimesh->mColors[0][i].b;
			v4.w = aimesh->mColors[0][i].a;
			vertex.Color = v4;
			mask = mask | (1 << 3);
		}
		glm::vec2 v2;
		if (aimesh->mTextureCoords[0]) {
			v2.x = aimesh->mTextureCoords[0][i].x;
			v2.y = aimesh->mTextureCoords[0][i].y;
			vertex.TexCoords0 = v2;
			mask = mask | (1 << 4);
		}
		else {
			vertex.TexCoords0 = glm::vec2(0.0f, 0.0f);
			mask = mask | (1 << 5);
		}
		if (aimesh->mTextureCoords[1]) {
			v2.x = aimesh->mTextureCoords[1][i].x;
			v2.y = aimesh->mTextureCoords[1][i].y;
			vertex.TexCoords1 = v2;
			mask = mask | (1 << 6);
		}
		if (aimesh->mTextureCoords[2]) {
			v2.x = aimesh->mTextureCoords[2][i].x;
			v2.y = aimesh->mTextureCoords[2][i].y;
			vertex.TexCoords2 = v2;
			mask = mask | (1 << 7);
		}
		if (aimesh->mTextureCoords[3]) {
			v2.x = aimesh->mTextureCoords[3][i].x;
			v2.y = aimesh->mTextureCoords[3][i].y;
			vertex.TexCoords3 = v2;
			mask = mask | (1 << 8);
		}
		if (aimesh->mTextureCoords[4]) {
			v2.x = aimesh->mTextureCoords[4][i].x;
			v2.y = aimesh->mTextureCoords[4][i].y;
			vertex.TexCoords4 = v2;
			mask = mask | (1 << 9);

		}
		if (aimesh->mTextureCoords[5]) {
			v2.x = aimesh->mTextureCoords[5][i].x;
			v2.y = aimesh->mTextureCoords[5][i].y;
			vertex.TexCoords5 = v2;
			mask = mask | (1 << 10);
		}
		if (aimesh->mTextureCoords[6]) {
			v2.x = aimesh->mTextureCoords[6][i].x;
			v2.y = aimesh->mTextureCoords[6][i].y;
			vertex.TexCoords6 = v2;
			mask = mask | (1 << 11);
		}
		if (aimesh->mTextureCoords[7]) {
			v2.x = aimesh->mTextureCoords[7][i].x;
			v2.y = aimesh->mTextureCoords[7][i].y;
			vertex.TexCoords7 = v2;
			mask = mask | (1 << 12);
		}
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's _Faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned i = 0; i < aimesh->mNumFaces; i++)
	{
		aiFace face = aimesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* pointMaterial = scene->mMaterials[aimesh->mMaterialIndex];

	auto mesh = std::make_shared<Mesh>();
	mesh->SetVertices(mask, vertices, indices);

	auto material = std::make_shared<Material>();
	float shininess;
	pointMaterial->Get(AI_MATKEY_SHININESS, shininess);
	if (shininess == 0.0f) shininess = 32.0f;
	material->Shininess = shininess;
	material->SetProgram(shader);
	if (pointMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j), TextureType::DIFFUSE);
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(directory + "/" + str.C_Str());
			material->SetTexture(texture2D, TextureType::DIFFUSE);
			_Texture2Ds.pop_back();
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	else
	{
		material->SetTexture(Default::Textures::StandardTexture, TextureType::DIFFUSE);
	}
	if (pointMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j), TextureType::SPECULAR);
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(directory + "/" + str.C_Str());
			material->SetTexture(texture2D, TextureType::SPECULAR);
			_Texture2Ds.pop_back();
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_HEIGHT, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j), TextureType::NORMAL);
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(directory + "/" + str.C_Str());
			material->SetTexture(texture2D, TextureType::NORMAL);
			_Texture2Ds.pop_back();
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_DISPLACEMENT) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_DISPLACEMENT, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j), TextureType::DISPLACEMENT);
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(directory + "/" + str.C_Str());
			material->SetTexture(texture2D, TextureType::DISPLACEMENT);
			_Texture2Ds.pop_back();
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	modelNode->_MeshMaterials.push_back(std::make_pair(material, mesh));
}

void UniEngine::FileManager::AttachChildren(EntityArchetype archetype, std::unique_ptr<ModelNode>& modelNode, Entity parentEntity, std::string parentName)
{
	Entity entity = EntityManager::CreateEntity(archetype);
	entity.SetName(parentName);
	EntityManager::SetParent(entity, parentEntity);
	Transform ltp;
	ltp.Value = modelNode->_LocalToParent;
	EntityManager::SetComponentData<Transform>(entity, ltp);
	for (auto i : modelNode->_MeshMaterials) {
		auto mmc = std::make_unique<MeshRenderer>();
		mmc->Mesh = i.second;
		mmc->Material = i.first;
		EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(mmc));
	}
	int index = 0;
	for (auto& i : modelNode->Children) {
		AttachChildren(archetype, i, entity, (parentName + "_" + std::to_string(index)));
		index++;
	}
}

void FileManager::ModelGuiNode(int i)
{
	ImGui::PushID(i);
	ImGui::ImageButton(reinterpret_cast<ImTextureID>(Default::Textures::ObjectIcon->Texture()->ID()), ImVec2(30, 30));
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		// Set payload to carry the index of our item (could be anything)
		ImGui::SetDragDropPayload("ASSET_MODEL", &_Models[i], sizeof(std::shared_ptr<Model>));
		ImGui::Image(reinterpret_cast<ImTextureID>(Default::Textures::ObjectIcon->Texture()->ID()), ImVec2(30, 30));
		ImGui::EndDragDropSource();
	}
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(i).c_str()))
	{
		if (ImGui::BeginMenu("Rename"))
		{
			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm")) _Models[i]->Name = std::string(newName);
			ImGui::EndMenu();
		}
		if (ImGui::Button("Delete")) {
			RemoveModel(i);
			deleted = true;
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
	ImGui::SameLine();
	if (!deleted) {
		ImGui::TextWrapped(_Models[i]->Name.c_str(), ImVec2(30, 30));
	}
}

void FileManager::TextureGuiNode(int i)
{
	ImGui::PushID(i);
	ImGui::ImageButton((ImTextureID)_Texture2Ds[i]->Texture()->ID(), ImVec2(30, 30));
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		ImGui::SetDragDropPayload("ASSET_TEXTURE2D", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
		ImGui::Image((ImTextureID)_Texture2Ds[i]->Texture()->ID(), ImVec2(30, 30));
		ImGui::EndDragDropSource();
	}
	bool deleted = false;
	if (ImGui::BeginPopupContextItem(std::to_string(i).c_str()))
	{
		if (ImGui::BeginMenu("Rename"))
		{
			static char newName[256];
			ImGui::InputText("New name", newName, 256);
			if (ImGui::Button("Confirm")) _Texture2Ds[i]->Name = std::string(newName);
			ImGui::EndMenu();
		}
		if (ImGui::Button("Delete")) {
			RemoveTexture(i);
			deleted = true;
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
	ImGui::SameLine();
	ImGui::TextWrapped(_Texture2Ds[i]->Name.c_str());

}

std::shared_ptr<Model> FileManager::GetModel(int i)
{
	return _Models[i];
}

std::shared_ptr<Texture2D> FileManager::GetTexture2D(int i)
{
	return _Texture2Ds[i];
}

std::shared_ptr<Texture2D> FileManager::LoadTexture(std::string path)
{
	stbi_set_flip_vertically_on_load(true);
	auto retVal = std::make_shared<Texture2D>();
	std::string filename = path;
	retVal->_Path = filename;
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RED;
		GLenum iformat = GL_R8;
		if (nrComponents == 2) {
			format = GL_RG;
			iformat = GL_RG8;
		}
		else if (nrComponents == 3) {
			format = GL_RGB;
			iformat = GL_RGB8;
		}
		else if (nrComponents == 4) {
			format = GL_RGBA;
			iformat = GL_RGBA8;
		}
		GLsizei mipmap = static_cast<GLsizei>(log2(std::max(width, height))) + 1;
		retVal->Texture() = std::make_unique<GLTexture2D>(mipmap, iformat, width, height, true);
		retVal->Texture()->SetData(0, format, GL_UNSIGNED_BYTE, data);
		retVal->Texture()->SetInt(GL_TEXTURE_WRAP_S, GL_REPEAT);
		retVal->Texture()->SetInt(GL_TEXTURE_WRAP_T, GL_REPEAT);
		retVal->Texture()->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		retVal->Texture()->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		retVal->Texture()->GenerateMipMap();
		retVal->Texture()->MakeResident();
		stbi_image_free(data);
	}
	else
	{
		Debug::Log("Texture failed to load at path: " + filename);
		stbi_image_free(data);
	}
	_Texture2Ds.push_back(retVal);
	return retVal;
}

void FileManager::RemoveModel(int index)
{
	_Models.erase(_Models.begin() + index);
}

void FileManager::RemoveTexture(int index)
{
	_Texture2Ds.erase(_Texture2Ds.begin() + index);
}

void FileManager::LateUpdate()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Open..."))
			{
				if (ImGui::Button("World"))
				{
					auto result = FileIO::OpenFile("WorldSave (*.uniengineworld)\0*.uniengineworld\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							SerializationManager::Deserialize(Application::GetCurrentWorld(), path);
						}
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Save..."))
			{
				if (ImGui::Button("World"))
				{
					auto result = FileIO::SaveFile("WorldSave (*.uniengineworld)\0*.uniengineworld\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							SerializationManager::Serialize(Application::GetCurrentWorld(), path);
						}
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Load"))
			{
				if (ImGui::Button("Model"))
				{
					auto result = FileIO::OpenFile("Model (*.obj)\0*.obj\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							LoadModel(path, Default::GLPrograms::StandardProgram);
							Debug::Log("Loaded model from \"" + path);
						}
					}
				}
				if (ImGui::Button("Texture"))
				{
					auto result = FileIO::OpenFile("Texture (*.png)\0*.jpg\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							LoadTexture(path);
							Debug::Log("Loaded texture from \"" + path);
						}
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Asset Manager", &_EnableAssetMenu);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	if (_EnableAssetMenu)
	{
		ImGui::Begin("Resource Manager");
		if (ImGui::BeginTabBar("##Resource Tab", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)) {
			if (ImGui::BeginTabItem("Assets")) {
				uint32_t count = 0;
				for (const auto& entry : std::filesystem::recursive_directory_iterator(FileIO::GetAssetFolderPath()))
					count++;
				static int selection_mask = 0;
				auto clickState = FileIO::DirectoryTreeViewRecursive(FileIO::GetAssetFolderPath(), &count, &selection_mask);
				if (clickState.first)
				{
					// Update selection state
					// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
					if (ImGui::GetIO().KeyCtrl)
						selection_mask ^= 1 << (clickState.second);          // CTRL+click to toggle
					else //if (!(selection_mask & (1 << clickState.second))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
						selection_mask = 1 << (clickState.second);           // Click to single-select
				}
				ImGui::EndTabItem();
			}
			
			if (ImGui::BeginTabItem("Model"))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeid(Model).name()))
					{
						IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Model>));
						std::shared_ptr<Model> payload_n = *static_cast<std::shared_ptr<Model>*>(payload->Data);
						bool missing = true;
						for (auto i : _Models)
						{
							if (i.get() == payload_n.get())
							{
								missing = false;
								break;
							}
						}
						if (missing)
						{
							_Models.push_back(payload_n);
						}
					}
					ImGui::EndDragDropTarget();
				}
				bool removed = false;
				for (auto& i : _Models)
				{
					if (EditorManager::Draggable(i)) removed = true;
				}
				if (removed)
				{
					for (int i = 0; i < _Models.size(); i++)
					{
						if (!_Models[i]) {
							_Models.erase(_Models.begin() + i);
							i--;
						}
					}
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Mesh"))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeid(Mesh).name()))
					{
						IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Mesh>));
						std::shared_ptr<Mesh> payload_n = *static_cast<std::shared_ptr<Mesh>*>(payload->Data);
						bool missing = true;
						for (auto i : _Meshes)
						{
							if (i.get() == payload_n.get())
							{
								missing = false;
								break;
							}
						}
						if (missing)
						{
							_Meshes.push_back(payload_n);
						}
					}
					ImGui::EndDragDropTarget();
				}
				bool removed = false;
				for (auto& i : _Meshes)
				{
					if (EditorManager::Draggable(i)) removed = true;
				}
				if (removed)
				{
					for (int i = 0; i < _Meshes.size(); i++)
					{
						if (!_Meshes[i]) {
							_Meshes.erase(_Meshes.begin() + i);
							i--;
						}
					}
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Material"))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeid(Material).name()))
					{
						IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Material>));
						std::shared_ptr<Material> payload_n = *static_cast<std::shared_ptr<Material>*>(payload->Data);
						bool missing = true;
						for (auto i : _Materials)
						{
							if (i.get() == payload_n.get())
							{
								missing = false;
								break;
							}
						}
						if (missing)
						{
							_Materials.push_back(payload_n);
						}
					}
					ImGui::EndDragDropTarget();
				}
				bool removed = false;
				for (auto& i : _Materials)
				{
					if (EditorManager::Draggable(i)) removed = true;
				}
				if (removed)
				{
					for (int i = 0; i < _Materials.size(); i++)
					{
						if (!_Materials[i]) {
							_Materials.erase(_Materials.begin() + i);
							i--;
						}
					}
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Texture"))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeid(Texture2D).name()))
					{
						IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
						std::shared_ptr<Texture2D> payload_n = *static_cast<std::shared_ptr<Texture2D>*>(payload->Data);
						bool missing = true;
						for (auto i : _Texture2Ds)
						{
							if (i.get() == payload_n.get())
							{
								missing = false;
								break;
							}
						}
						if (missing)
						{
							_Texture2Ds.push_back(payload_n);
						}
					}
					ImGui::EndDragDropTarget();
				}
				bool removed = false;
				for (auto& i : _Texture2Ds)
				{
					if (EditorManager::Draggable(i)) removed = true;
				}
				if (removed)
				{
					for (int i = 0; i < _Texture2Ds.size(); i++)
					{
						if (!_Texture2Ds[i]) {
							_Texture2Ds.erase(_Texture2Ds.begin() + i);
							i--;
						}
					}
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Cubemap"))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeid(Cubemap).name()))
					{
						IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Cubemap>));
						std::shared_ptr<Cubemap> payload_n = *static_cast<std::shared_ptr<Cubemap>*>(payload->Data);
						bool missing = true;
						for (auto i : _Cubemaps)
						{
							if (i.get() == payload_n.get())
							{
								missing = false;
								break;
							}
						}
						if (missing)
						{
							_Cubemaps.push_back(payload_n);
						}
					}
					ImGui::EndDragDropTarget();
				}
				bool removed = false;
				for (auto& i : _Cubemaps)
				{
					if (EditorManager::Draggable(i)) removed = true;
				}
				if (removed)
				{
					for (int i = 0; i < _Cubemaps.size(); i++)
					{
						if (!_Cubemaps[i]) {
							_Cubemaps.erase(_Cubemaps.begin() + i);
							i--;
						}
					}
				}
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
		ImGui::End();
	}
}
