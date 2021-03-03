#include "pch.h"
#include "TransformManager.h"
#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "EntityManager.h"
#include "Default.h"
#include "SerializationManager.h"
#include "Application.h"
using namespace UniEngine;
std::map<size_t, std::pair<std::string, std::map<size_t, std::shared_ptr<ResourceBehaviour>>>> ResourceManager::m_resources;

void ResourceManager::Remove(size_t id, size_t hashCode)
{
	m_resources[id].second.erase(hashCode);
}

std::shared_ptr<Model> UniEngine::ResourceManager:: LoadModel(bool addResource, std::string const& path, std::shared_ptr<GLProgram> shader, bool gamma, unsigned flags)
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
	retVal->m_name = path.substr(path.find_last_of("/\\") + 1);
	ProcessNode(directory, shader, retVal->RootNode(), Texture2DsLoaded, scene->mRootNode, scene);
	if(addResource) Push(retVal);
	return retVal;
}

Entity UniEngine::ResourceManager::ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model)
{
	Entity entity = EntityManager::CreateEntity(archetype);
	entity.SetName(model->m_name);
	Transform ltp;
	std::unique_ptr<ModelNode>& modelNode = model->RootNode();
	EntityManager::SetComponentData<Transform>(entity, ltp);
	for (auto& i : modelNode->_MeshMaterials) {
		auto mmc = std::make_unique<MeshRenderer>();
		mmc->m_mesh = i.second;
		mmc->m_material = i.first;
		EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(mmc));
	}
	int index = 0;
	for (auto& i : modelNode->Children) {
		AttachChildren(archetype, i, entity, model->m_name + "_" + std::to_string(index));
		index++;
	}
	return entity;
}

void ResourceManager::ProcessNode(std::string directory, std::shared_ptr<GLProgram> shader, std::unique_ptr<ModelNode>& modelNode, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiNode* node, const aiScene* scene)
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

void ResourceManager::ReadMesh(unsigned meshIndex, std::unique_ptr<ModelNode>& modelNode, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene) {
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
	//PBR
	if (pointMaterial->GetTextureCount(aiTextureType_BASE_COLOR) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::ALBEDO);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_NORMAL_CAMERA) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_NORMAL_CAMERA, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::NORMAL);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_EMISSION_COLOR) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_NORMAL_CAMERA, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::EMISSIVE);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_METALNESS) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_METALNESS, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false,directory + "/" + str.C_Str(), TextureType::METALLIC);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::ROUGHNESS);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	if (pointMaterial->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::AO);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	//Others
	if (pointMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		aiString str;
		pointMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		bool skip = false;
		for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
		{
			if (Texture2DsLoaded.at(j)->Path()._Equal(directory + "/" + str.C_Str()))
			{
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::DIFFUSE);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
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
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::SPECULAR);
			material->SetTexture(texture2D);
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
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::NORMAL);
			material->SetTexture(texture2D);
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
				material->SetTexture(Texture2DsLoaded.at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			auto texture2D = LoadTexture(false, directory + "/" + str.C_Str(), TextureType::DISPLACEMENT);
			material->SetTexture(texture2D);
			Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	modelNode->_MeshMaterials.emplace_back(material, mesh);
}

void UniEngine::ResourceManager::AttachChildren(EntityArchetype archetype, std::unique_ptr<ModelNode>& modelNode, Entity parentEntity, std::string parentName)
{
	Entity entity = EntityManager::CreateEntity(archetype);
	entity.SetName(parentName);
	EntityManager::SetParent(entity, parentEntity);
	Transform ltp;
	ltp.Value = modelNode->_LocalToParent;
	EntityManager::SetComponentData<Transform>(entity, ltp);
	for (auto i : modelNode->_MeshMaterials) {
		auto mmc = std::make_unique<MeshRenderer>();
		mmc->m_mesh = i.second;
		mmc->m_material = i.first;
		EntityManager::SetPrivateComponent<MeshRenderer>(entity, std::move(mmc));
	}
	int index = 0;
	for (auto& i : modelNode->Children) {
		AttachChildren(archetype, i, entity, (parentName + "_" + std::to_string(index)));
		index++;
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(bool addResource, const std::string& path, TextureType type)
{
	stbi_set_flip_vertically_on_load(true);
	auto retVal = std::make_shared<Texture2D>(type);
	const std::string filename = path;
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
		retVal->_Texture = std::make_shared<GLTexture2D>(mipmap, iformat, width, height, true);
		retVal->_Texture->SetData(0, format, GL_UNSIGNED_BYTE, data);
		retVal->_Texture->SetInt(GL_TEXTURE_WRAP_S, GL_REPEAT);
		retVal->_Texture->SetInt(GL_TEXTURE_WRAP_T, GL_REPEAT);
		retVal->_Texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		retVal->_Texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		retVal->_Texture->GenerateMipMap();
		retVal->_Texture->MakeResident();
		stbi_image_free(data);
		
	}
	else {
		Debug::Log("Texture failed to load at path: " + filename);
		stbi_image_free(data);
		return nullptr;
	}
	retVal->m_icon = retVal;
	retVal->m_name = path.substr(path.find_last_of("/\\") + 1);
	if (addResource) Push(retVal);
	return retVal;
}


std::shared_ptr<Cubemap> ResourceManager::LoadCubemap(bool addResource, const std::vector<std::string>& paths)
{
	int width, height, nrComponents;
	auto size = paths.size();
	if (size != 6) {
		Debug::Error("Texture::LoadCubeMap: Size error.");
		return nullptr;
	}
	unsigned char* temp = stbi_load(paths[0].c_str(), &width, &height, &nrComponents, 0);
	stbi_image_free(temp);
	auto texture = std::make_unique<GLTextureCubeMap>(1, GL_RGB, width, height, false);
	for (int i = 0; i < size; i++)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum iformat = GL_R8;
			GLenum format = GL_RED;
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

			texture->SetData((CubeMapIndex)i, 0, iformat, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
			stbi_image_free(data);
			return nullptr;
		}
	}
	texture->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//texture->GenerateMipMap();
	texture->MakeResident();
	auto retVal = std::make_shared<Cubemap>();
	retVal->_Texture = std::move(texture);
	retVal->_Paths = paths;
	retVal->m_name = paths[0].substr(paths[0].find_last_of("/\\") + 1);
	if(addResource) Push(retVal);
	return retVal;
}

std::shared_ptr<Material> ResourceManager::LoadMaterial(bool addResource, const std::shared_ptr<GLProgram>& program)
{
	auto retVal = std::make_shared<Material>();
	retVal->Shininess = 32.0f;
	retVal->SetProgram(program);
	if(addResource) Push(retVal);
	return retVal;
}

std::shared_ptr<GLProgram> ResourceManager::LoadProgram(bool addResource, const std::shared_ptr<GLShader>& vertex,
	const std::shared_ptr<GLShader>& fragment)
{
	auto retVal = std::make_shared<GLProgram>();
	retVal->Attach(vertex);
	retVal->Attach(fragment);
	retVal->Link();
	if(addResource) Push(retVal);
	return retVal;
}

std::shared_ptr<GLProgram> ResourceManager::LoadProgram(bool addResource, const std::shared_ptr<GLShader>& vertex,
	const std::shared_ptr<GLShader>& geometry, const std::shared_ptr<GLShader>& fragment)
{
	auto retVal = std::make_shared<GLProgram>();
	retVal->Attach(vertex);
	retVal->Attach(geometry);
	retVal->Attach(fragment);
	retVal->Link();
	if(addResource) Push(retVal);
	return retVal;
}

void ResourceManager::LateUpdate()
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
					auto result = FileIO::OpenFile("Model (*.obj,*.gltf,*.glb,*.blend,*.ply,*.fbx)\0*.obj;*.gltf;*.glb;*.blend;*.ply;*.fbx\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							LoadModel(true, path, Default::GLPrograms::StandardProgram);
							Debug::Log("Loaded model from \"" + path);
						}
					}
				}
				if (ImGui::Button("Texture"))
				{
					auto result = FileIO::OpenFile("Texture (*.png,*.jpg,*.jpeg)\0*.jpg;*.png;*.jpeg\0");
					if (result.has_value())
					{
						const std::string path = result.value();
						if (!path.empty())
						{
							LoadTexture(true, path);
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
			ImGui::Checkbox("Asset Manager", &GetInstance().m_enableAssetMenu);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	if (GetInstance().m_enableAssetMenu)
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
			for (auto& collection : m_resources) {
				if (ImGui::BeginTabItem(collection.second.first.substr(6).c_str()))
				{
					if (ImGui::BeginDragDropTarget())
					{
						const std::string hash = std::to_string(std::hash<std::string>{}(collection.second.first));
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(hash.c_str()))
						{
							IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<ResourceBehaviour>));
							std::shared_ptr<ResourceBehaviour> payload_n = *static_cast<std::shared_ptr<ResourceBehaviour>*>(payload->Data);
							Push(payload_n);
						}
						ImGui::EndDragDropTarget();
					}
					for (auto& i : collection.second.second)
					{
						if (EditorManager::Draggable(collection.second.first, i.second))
						{
							Remove(i.first, i.second->GetHashCode());
							break;
						}
					}

					ImGui::EndTabItem();
				}
			}
			
		}
		ImGui::EndTabBar();
		ImGui::End();
	}
}
