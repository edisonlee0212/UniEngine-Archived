#include "AssimpImporter.h"
#include "Scene.h"

using namespace UniEngine;

void AssimpImporter::LoadScene(UniEngine::Scene* destination, std::string const& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		Debug::Error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
		return;
	}
	// retrieve the directory path of the filepath
	std::string directory = path.substr(0, path.find_last_of('/'));
	for (uint i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* amesh = scene->mMeshes[i];
		Mesh* mesh = new Mesh();
		ReadMesh(amesh, mesh);
		destination->_Meshes.push_back(mesh);
	}

	for (uint i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* amaterial = scene->mMaterials[i];
		Material* pointMaterial = new Material();
		auto loadedTexture2Ds = &destination->_Texture2Ds;
		ReadMaterial(directory, amaterial, pointMaterial, loadedTexture2Ds);
		destination->_Materials.push_back(pointMaterial);
	}
	ProcessNode(directory, scene->mRootNode, destination->_Root, scene);
}

void AssimpImporter::ProcessNode(std::string directory, aiNode* node, SceneNode* sceneNode, const aiScene* scene) {
	auto transform = node->mTransformation;
	sceneNode->_Matrix = float4x4(transform.a1, transform.a2, transform.a3, transform.a4, transform.b1, transform.b2, transform.b3, transform.b4, transform.c1, transform.c2, transform.c3, transform.c4, transform.d1, transform.d2, transform.d3, transform.d4);
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		sceneNode->_MeshIndices.push_back(node->mMeshes[i]);
	}

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		auto n = new SceneNode(sceneNode);
		sceneNode->_Children.push_back(n);
		ProcessNode(directory, node->mChildren[i], n, scene);
	}
}

void AssimpImporter::ReadMesh(aiMesh* src, Mesh* dest) {
	std::vector<Vertex> vertices;
	std::vector<uint> indices;

	// Walk through each of the mesh's vertices
	for (uint i = 0; i < src->mNumVertices; i++)
	{
		Vertex vertex;
		float3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder float3 first.
		// positions
		vector.x = src->mVertices[i].x;
		vector.y = src->mVertices[i].y;
		vector.z = src->mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = src->mNormals[i].x;
		vector.y = src->mNormals[i].y;
		vector.z = src->mNormals[i].z;
		vertex.Normal = vector;
		// Texture2D coordinates
		if (src->mTextureCoords[0]) // does the mesh contain Texture2D coordinates?
		{
			float2 vec;
			// a vertex can contain up to 8 different Texture2D coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple Texture2D coordinates so we always take the first set (0).
			vec.x = src->mTextureCoords[0][i].x;
			vec.y = src->mTextureCoords[0][i].y;
			vertex.TexCoords0 = vec;
		}
		else
			vertex.TexCoords0 = float2(0.0f, 0.0f);
		// tangent
		vector.x = src->mTangents[i].x;
		vector.y = src->mTangents[i].y;
		vector.z = src->mTangents[i].z;
		vertex.Tangent = vector;
		// bitangent
		vector.x = src->mBitangents[i].x;
		vector.y = src->mBitangents[i].y;
		vector.z = src->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's _Faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (uint i = 0; i < src->mNumFaces; i++)
	{
		aiFace face = src->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (uint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	dest->SetVertices(VertexAttribute::Normal, indices.size(), &vertices[0], &indices[0]);
}

void AssimpImporter::ReadMaterial(std::string directory, aiMaterial* src, Material* dest, std::vector<Texture2D*>* Texture2DsLoaded) {
	auto Texture2Ds = dest->Textures2Ds();
	std::vector<Texture2D*> diffuseMaps = LoadMaterialTexture2Ds(directory, Texture2DsLoaded, src, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	Texture2Ds->insert(Texture2Ds->end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture2D*> specularMaps = LoadMaterialTexture2Ds(directory, Texture2DsLoaded, src, aiTextureType_SPECULAR, TextureType::SPECULAR);
	Texture2Ds->insert(Texture2Ds->end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture2D*> normalMaps = LoadMaterialTexture2Ds(directory, Texture2DsLoaded, src, aiTextureType_HEIGHT, TextureType::NORMAL);
	Texture2Ds->insert(Texture2Ds->end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture2D*> heightMaps = LoadMaterialTexture2Ds(directory, Texture2DsLoaded, src, aiTextureType_AMBIENT, TextureType::HEIGHT);
	Texture2Ds->insert(Texture2Ds->end(), heightMaps.begin(), heightMaps.end());
}

inline std::vector<Texture2D*> AssimpImporter::LoadMaterialTexture2Ds(std::string directory, std::vector<Texture2D*>* Texture2DsLoaded, aiMaterial* mat, aiTextureType type, TextureType typeName) {
	std::vector<Texture2D*> Texture2Ds;
	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if Texture2D was loaded before and if so, continue to next iteration: skip loading a new Texture2D
		bool skip = false;
		for (uint j = 0; j < Texture2DsLoaded->size(); j++)
		{
			if (std::strcmp(Texture2DsLoaded->at(j)->Path().c_str(), str.C_Str()) == 0)
			{
				Texture2Ds.push_back(Texture2DsLoaded->at(j));
				skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if Texture2D hasn't been loaded already, load it
			Texture2D* Texture2D = new UniEngine::Texture2D(typeName);
			Texture2D->LoadTexture(str.C_Str(), directory);
			Texture2Ds.push_back(Texture2D);
			Texture2DsLoaded->push_back(Texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
		}
	}
	return Texture2Ds;
}
