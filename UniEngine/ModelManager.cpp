#include "ModelManager.h"
#include "World.h"
using namespace UniEngine;
std::vector<Entity*> ModelManager::entities = std::vector<Entity*>();

void ModelManager::LoadModel(Entity* root, std::string const& path, GLProgram* shader, bool gamma) {
    // read file via ASSIMP
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
    std::vector<Texture2D*>* Texture2DsLoaded = new std::vector<Texture2D*>();
    ProcessNode(directory, shader, root, Texture2DsLoaded, scene->mRootNode, scene);
}

void ModelManager::ProcessNode(std::string directory, GLProgram* program, Entity* parent, std::vector<Texture2D*>* Texture2DsLoaded, aiNode* node, const aiScene* scene)
{
    for (unsigned i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        auto entity = ReadMesh(directory, program, Texture2DsLoaded, mesh, scene);
        entities.push_back(entity);

        LocalScale ls;
        ls.value = float3(1.0f);
        _World->_EntityCollection->SetFixedData<LocalPosition>(entity, LocalPosition());
        _World->_EntityCollection->SetFixedData<LocalRotation>(entity, LocalRotation());
        _World->_EntityCollection->SetFixedData<LocalScale>(entity, ls);
        _World->_EntityCollection->SetParent(entity, parent);
    }
    for (unsigned i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(directory, program, parent, Texture2DsLoaded, node->mChildren[i], scene);
    }
}

Entity* ModelManager::ReadMesh(std::string directory, GLProgram* program, std::vector<Texture2D*>* Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene) {
    Entity* entity = _World->_EntityCollection->CreateEntity();
    unsigned mask = 1;
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    // Walk through each of the mesh's vertices
    for (unsigned i = 0; i < aimesh->mNumVertices; i++)
    {
        Vertex vertex;
        float3 v3; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder float3 first.
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
        if (aimesh->mBitangents) {
            v3.x = aimesh->mBitangents[i].x;
            v3.y = aimesh->mBitangents[i].y;
            v3.z = aimesh->mBitangents[i].z;
            vertex.Bitangent = v3;
            mask = mask | (1 << 3);
        }
        float4 v4;
        if (aimesh->mColors[0]) {
            v4.x = aimesh->mColors[0]->r;
            v4.y = aimesh->mColors[0]->g;
            v4.z = aimesh->mColors[0]->b;
            v4.w = aimesh->mColors[0]->a;
            vertex.Color = v4;
            mask = mask | (1 << 4);
        }
        float2 v2;
        if (aimesh->mTextureCoords[0]) {
            v2.x = aimesh->mTextureCoords[0]->x;
            v2.y = aimesh->mTextureCoords[0]->y;
            vertex.TexCoords0 = v2;
            mask = mask | (1 << 5);
        }
        if (aimesh->mTextureCoords[1]) {
            v2.x = aimesh->mTextureCoords[1]->x;
            v2.y = aimesh->mTextureCoords[1]->y;
            vertex.TexCoords1 = v2;
            mask = mask | (1 << 6);
        }
        if (aimesh->mTextureCoords[2]) {
            v2.x = aimesh->mTextureCoords[2]->x;
            v2.y = aimesh->mTextureCoords[2]->y;
            vertex.TexCoords2 = v2;
            mask = mask | (1 << 7);
        }
        if (aimesh->mTextureCoords[3]) {
            v2.x = aimesh->mTextureCoords[3]->x;
            v2.y = aimesh->mTextureCoords[3]->y;
            vertex.TexCoords3 = v2;
            mask = mask | (1 << 8);
        }
        if (aimesh->mTextureCoords[4]) {
            v2.x = aimesh->mTextureCoords[4]->x;
            v2.y = aimesh->mTextureCoords[4]->y;
            vertex.TexCoords4 = v2;
            mask = mask | (1 << 9);

        }
        if (aimesh->mTextureCoords[5]) {
            v2.x = aimesh->mTextureCoords[5]->x;
            v2.y = aimesh->mTextureCoords[5]->y;
            vertex.TexCoords5 = v2;
            mask = mask | (1 << 10);
        }
        if (aimesh->mTextureCoords[6]) {
            v2.x = aimesh->mTextureCoords[6]->x;
            v2.y = aimesh->mTextureCoords[6]->y;
            vertex.TexCoords6 = v2;
            mask = mask | (1 << 11);
        }
        if (aimesh->mTextureCoords[7]) {
            v2.x = aimesh->mTextureCoords[7]->x;
            v2.y = aimesh->mTextureCoords[7]->y;
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

    auto mesh = new Mesh();
    mesh->SetVertices(mask, indices.size(), &vertices, &indices);

    entity->SetSharedComponent<Mesh>(mesh);
    auto material = new Material();
    entity->SetSharedComponent<Material>(material);
    if(program != nullptr) material->Programs()->push_back(program);
    std::vector<Texture2D*>* Texture2Ds = material->Textures2Ds();
    std::vector<Texture2D*> diffuseMaps = LoadMaterialTextures(directory, Texture2DsLoaded, pointMaterial, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
    Texture2Ds->insert(Texture2Ds->end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture2D*> specularMaps = LoadMaterialTextures(directory, Texture2DsLoaded, pointMaterial, aiTextureType_SPECULAR, TextureType::SPECULAR);
    Texture2Ds->insert(Texture2Ds->end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture2D*> normalMaps = LoadMaterialTextures(directory, Texture2DsLoaded, pointMaterial, aiTextureType_HEIGHT, TextureType::NORMAL);
    Texture2Ds->insert(Texture2Ds->end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture2D*> heightMaps = LoadMaterialTextures(directory, Texture2DsLoaded, pointMaterial, aiTextureType_AMBIENT, TextureType::HEIGHT);
    Texture2Ds->insert(Texture2Ds->end(), heightMaps.begin(), heightMaps.end());
    return entity;
}
std::vector<Texture2D*> ModelManager::LoadMaterialTextures(std::string directory, std::vector<Texture2D*>* Texture2DsLoaded, aiMaterial* mat, aiTextureType type, TextureType typeName)
{
    std::vector<Texture2D*> Texture2Ds;
    for (unsigned i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if Texture2D was loaded before and if so, continue to next iteration: skip loading a new Texture2D
        bool skip = false;
        for (unsigned j = 0; j < Texture2DsLoaded->size(); j++)
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
            Texture2D* texture2D = new Texture2D(typeName);
            texture2D->LoadTexture(str.C_Str(), directory);
            Texture2Ds.push_back(texture2D);
            Texture2DsLoaded->push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
        }
    }
    return Texture2Ds;
}