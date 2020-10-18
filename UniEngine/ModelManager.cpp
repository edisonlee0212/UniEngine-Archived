#include "pch.h"
#include "TransformSystem.h"
#include "ModelManager.h"
#include "MeshRenderer.h"
#include <stb_image.h>


#include "Default.h"
#include "FileBrowser.h"

using namespace UniEngine;
bool ModelManager::_EnableListMenu;
std::vector<std::shared_ptr<Model>> ModelManager::_Models;
FileBrowser ModelManager::_FileBrowser;
std::shared_ptr<Model> UniEngine::ModelManager::LoadModel(std::string const& path, std::shared_ptr<GLProgram> shader, bool gamma)
{
    stbi_set_flip_vertically_on_load(true);
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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

Entity UniEngine::ModelManager::ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model)
{
    Entity entity = EntityManager::CreateEntity(archetype);
    LocalToWorld ltw;
    ModelNode* modelNode = model->RootNode();
    ltw.Value = modelNode->_LocalToParent;
    EntityManager::SetComponentData<LocalToWorld>(entity, ltw);
    for (auto i : modelNode->_MeshMaterialComponents) {
        EntityManager::SetSharedComponent<MeshRenderer>(entity, i);
    }
    for (auto i : modelNode->Children) {
        AttachChildren(archetype, i, entity);
    }
    return entity;
}

void ModelManager::ProcessNode(std::string directory, std::shared_ptr<GLProgram> shader, ModelNode* modelNode, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiNode* node, const aiScene* scene)
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
        ModelNode* childNode = new ModelNode();
        childNode->Parent = modelNode;
        modelNode->Children.push_back(childNode);
        ProcessNode(directory, shader, childNode, Texture2DsLoaded, node->mChildren[i], scene);
    }
}

void ModelManager::ReadMesh(unsigned meshIndex, ModelNode* modelNode, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene) {
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

    auto mesh = std::make_shared<Mesh>() ;
    mesh->SetVertices(mask, vertices, indices);

    auto material = std::make_shared<Material>();
    float shininess;
    pointMaterial->Get(AI_MATKEY_SHININESS, shininess);
    material->SetShininess(shininess);
    material->SetProgram(shader);
	if(pointMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
        aiString str;
        pointMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        bool skip = false;
        for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
        {
            if (std::strcmp(Texture2DsLoaded.at(j)->Path().c_str(), str.C_Str()) == 0)
            {
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            std::shared_ptr<Texture2D> texture2D = std::make_shared<Texture2D>(TextureType::DIFFUSE);
            texture2D->LoadTexture(str.C_Str(), directory);
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
            if (std::strcmp(Texture2DsLoaded.at(j)->Path().c_str(), str.C_Str()) == 0)
            {
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            std::shared_ptr<Texture2D> texture2D = std::make_shared<Texture2D>(TextureType::SPECULAR);
            texture2D->LoadTexture(str.C_Str(), directory);
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
            if (std::strcmp(Texture2DsLoaded.at(j)->Path().c_str(), str.C_Str()) == 0)
            {
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            std::shared_ptr<Texture2D> texture2D = std::make_shared<Texture2D>(TextureType::NORMAL);
            texture2D->LoadTexture(str.C_Str(), directory);
            material->SetTexture(texture2D);
            Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
        }
    }
    if (pointMaterial->GetTextureCount(aiTextureType_HEIGHT) > 1)
    {
        aiString str;
        pointMaterial->GetTexture(aiTextureType_HEIGHT, 1, &str);
        bool skip = false;
        for (unsigned j = 0; j < Texture2DsLoaded.size(); j++)
        {
            if (std::strcmp(Texture2DsLoaded.at(j)->Path().c_str(), str.C_Str()) == 0)
            {
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            std::shared_ptr<Texture2D> texture2D = std::make_shared<Texture2D>(TextureType::HEIGHT);
            texture2D->LoadTexture(str.C_Str(), directory);
            material->SetTexture(texture2D);
            Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
        }
    }
    auto mmc = std::make_shared<MeshRenderer>();
    mmc->Mesh = mesh;
    mmc->Material = material;
    modelNode->_MeshMaterialComponents.push_back(mmc);
}

void UniEngine::ModelManager::AttachChildren(EntityArchetype archetype, ModelNode* modelNode, Entity parentEntity)
{
    Entity entity = EntityManager::CreateEntity(archetype);
    EntityManager::SetParent(entity, parentEntity);
    LocalToParent ltp;
    ltp.Value = modelNode->_LocalToParent;
    EntityManager::SetComponentData<LocalToParent>(entity, ltp);
    for (auto i : modelNode->_MeshMaterialComponents) {
        EntityManager::SetSharedComponent<MeshRenderer>(entity, std::shared_ptr<MeshRenderer>(i));
    }
    for (auto i : modelNode->Children) {
        AttachChildren(archetype, i, entity);
    }
}

void ModelManager::RemoveModel(int index)
{
    _Models.erase(_Models.begin() + index);
}

void ModelManager::OnGui()
{
    bool openLoader = false;
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("New"))
            {
                if(ImGui::Button("Model"))
                {
                    openLoader = true;
                }
                
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::Checkbox("Model Manager", &_EnableListMenu);
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
    if (_EnableListMenu)
    {
        ImGui::Begin("Model Manager");
    	if(ImGui::TreeNode("Loaded models"))
    	{
    		for(int i = 0; i < _Models.size(); i++)
    		{
                ImGui::Text("[%d] %s", i + 1, _Models[i]->Name);
                ImGui::SameLine();
                if(ImGui::Button(("Add to scene##" + std::to_string(i)).c_str()))
                {
                    EntityArchetype archetype = EntityManager::CreateEntityArchetype("Model",
                        LocalToParent(),
                        Translation(),
                        Scale(),
                        LocalToWorld());
                    ToEntity(archetype, _Models[i]);
                }
    		}
            ImGui::TreePop();
    	}
        ImGui::End();
    }
    if(openLoader)
    {
        ImGui::OpenPopup("Model Loader");
    }
    if (_FileBrowser.showFileDialog("Model Loader", FileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".obj"))
    {
        LoadModel(_FileBrowser.selected_path, Default::GLPrograms::DeferredPrepass);
        Debug::Log("Loaded model from \"" + _FileBrowser.selected_path);
        //std::cout << _FileBrowser.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        //std::cout << _FileBrowser.selected_path << std::endl;    // The absolute path to the selected file

    }
}
