#include "pch.h"
#include "TransformSystem.h"
#include "AssetManager.h"
#include "MeshRenderer.h"
#include <stb_image.h>


#include "Default.h"
#include "FileBrowser.h"

using namespace UniEngine;
bool AssetManager::_EnableAssetMenu = true;
std::vector<std::shared_ptr<Model>> AssetManager::_Models;
std::vector<std::shared_ptr<Texture2D>> AssetManager::_Texture2Ds;
std::vector<std::shared_ptr<Cubemap>> AssetManager::_Cubemaps;

FileBrowser AssetManager::_FileBrowser;
std::shared_ptr<Model> UniEngine::AssetManager::LoadModel(std::string const& path, std::shared_ptr<GLProgram> shader, bool gamma)
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

Entity UniEngine::AssetManager::ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model)
{
    Entity entity = EntityManager::CreateEntity(archetype);
    LocalToWorld ltw;
    std::unique_ptr<ModelNode>& modelNode = model->RootNode();
    ltw.Value = modelNode->_LocalToParent;
    EntityManager::SetComponentData<LocalToWorld>(entity, ltw);
    for (const auto& i : modelNode->_MeshMaterialComponents) {
        EntityManager::SetSharedComponent<MeshRenderer>(entity, i);
    }
    for (auto& i : modelNode->Children) {
        AttachChildren(archetype, i, entity);
    }
    return entity;
}

void AssetManager::ProcessNode(std::string directory, std::shared_ptr<GLProgram> shader, std::unique_ptr<ModelNode>& modelNode, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiNode* node, const aiScene* scene)
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

void AssetManager::ReadMesh(unsigned meshIndex, std::unique_ptr<ModelNode>& modelNode, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene) {
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
    if (shininess == 0.0f) shininess = 32.0f;
    material->SetShininess(shininess);
    material->SetProgram(shader);
	if(pointMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
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
            auto texture2D = LoadTexture(directory + "/" + str.C_Str(), TextureType::DIFFUSE);
            material->SetTexture(texture2D);
            _Texture2Ds.pop_back();
            Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
        }
	}else
	{
        material->SetTexture(Default::Textures::StandardTexture);
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
            auto texture2D = LoadTexture(directory + "/" + str.C_Str(), TextureType::SPECULAR);
            material->SetTexture(texture2D);
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
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            auto texture2D = LoadTexture(directory + "/" + str.C_Str(), TextureType::NORMAL);
            material->SetTexture(texture2D);
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
                material->SetTexture(Texture2DsLoaded.at(j));
                skip = true; // a Texture2D with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if Texture2D hasn't been loaded already, load it
            auto texture2D = LoadTexture(directory + "/" + str.C_Str(), TextureType::DISPLACEMENT);
            material->SetTexture(texture2D);
            _Texture2Ds.pop_back();
            Texture2DsLoaded.push_back(texture2D);  // store it as Texture2D loaded for entire model, to ensure we won't unnecesery load duplicate Texture2Ds.
        }
    }
    auto mmc = std::make_shared<MeshRenderer>();
    mmc->Mesh = mesh;
    mmc->Material = material;
    modelNode->_MeshMaterialComponents.push_back(mmc);
}

void UniEngine::AssetManager::AttachChildren(EntityArchetype archetype, std::unique_ptr<ModelNode>& modelNode, Entity parentEntity)
{
    Entity entity = EntityManager::CreateEntity(archetype);
    EntityManager::SetParent(entity, parentEntity);
    LocalToParent ltp;
    ltp.Value = modelNode->_LocalToParent;
    EntityManager::SetComponentData<LocalToParent>(entity, ltp);
    for (auto i : modelNode->_MeshMaterialComponents) {
        EntityManager::SetSharedComponent<MeshRenderer>(entity, std::shared_ptr<MeshRenderer>(i));
    }
    for (auto& i : modelNode->Children) {
        AttachChildren(archetype, i, entity);
    }
}

void AssetManager::ModelGuiNode(int i)
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
    ImGui::PopID();
    ImGui::SameLine();
    ImGui::TextWrapped(_Models[i]->Name.c_str(), ImVec2(30, 30));
    
}

void AssetManager::TextureGuiNode(int i)
{
    ImGui::PushID(i);
    ImGui::ImageButton((ImTextureID)_Texture2Ds[i]->Texture()->ID(), ImVec2(30, 30));
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
    {
        // Set payload to carry the index of our item (could be anything)
        switch (_Texture2Ds[i]->Type())
        {
        case TextureType::DIFFUSE:
            ImGui::SetDragDropPayload("ASSET_TEXTURE_DIFFUSE", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
            break;
        case TextureType::SPECULAR:
            ImGui::SetDragDropPayload("ASSET_TEXTURE_SPECULAR", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
            break;
        case TextureType::NORMAL:
            ImGui::SetDragDropPayload("ASSET_TEXTURE_NORMAL", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
            break;
        case TextureType::DISPLACEMENT:
            ImGui::SetDragDropPayload("ASSET_TEXTURE_DISPLACEMENT", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
            break;
        case TextureType::NONE:
            ImGui::SetDragDropPayload("ASSET_TEXTURE_NONE", &_Texture2Ds[i], sizeof(std::shared_ptr<Texture2D>));
            break;
        }

        ImGui::Image((ImTextureID)_Texture2Ds[i]->Texture()->ID(), ImVec2(30, 30));
        ImGui::EndDragDropSource();
    }
    ImGui::PopID();
    ImGui::SameLine();
    std::string typeStr;
    switch (_Texture2Ds[i]->Type())
    {
    case TextureType::DIFFUSE:
        typeStr = "Diffuse";
        break;
    case TextureType::SPECULAR:
        typeStr = "Specular";
        break;
    case TextureType::NORMAL:
        typeStr = "Normal";
        break;
    case TextureType::DISPLACEMENT:
        typeStr = "Displacement";
        break;
    case TextureType::NONE:
        typeStr = "None";
        break;
    }
    ImGui::TextWrapped((_Texture2Ds[i]->Name + " Type: " + typeStr).c_str());
    
}

std::shared_ptr<Model> AssetManager::GetModel(int i)
{
    return _Models[i];
}

std::shared_ptr<Texture2D> AssetManager::GetTexture2D(int i)
{
    return _Texture2Ds[i];
}

std::shared_ptr<Texture2D> AssetManager::LoadTexture(std::string path, TextureType type)
{
    auto retVal = std::make_shared<Texture2D>(type);
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
        retVal->Texture() = std::make_unique<GLTexture2D>(1, iformat, width, height, false);
        retVal->Texture()->SetData(0, iformat, format, GL_UNSIGNED_BYTE, data);
        retVal->Texture()->GenerateMipMap();

        retVal->Texture()->SetInt(GL_TEXTURE_WRAP_S, GL_REPEAT);
        retVal->Texture()->SetInt(GL_TEXTURE_WRAP_T, GL_REPEAT);
        retVal->Texture()->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        retVal->Texture()->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

void AssetManager::RemoveModel(int index)
{
    _Models.erase(_Models.begin() + index);
}

void AssetManager::OnGui()
{
    bool openModelLoader = false;
    bool openTextureLoader = false;
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Load"))
            {
                if(ImGui::Button("Model"))
                {
                    openModelLoader = true;
                }
                if (ImGui::Button("Texture"))
                {
                    openTextureLoader = true;
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
        ImGui::Begin("Asset Manager");
        if (ImGui::BeginTabBar("##AssetTabs", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton)) {
            if (ImGui::BeginTabItem("Model"))
            {
                for (int i = 0; i < _Models.size(); i++)
                {
                    ModelGuiNode(i);
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Texture"))
            {
                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_DIFFUSE"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
                        std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
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
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_NORMAL"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
                        std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
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
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_SPECULAR"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
                        std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
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
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_DISPLACEMENT"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(std::shared_ptr<Texture2D>));
                        std::shared_ptr<Texture2D> payload_n = *(std::shared_ptr<Texture2D>*)payload->Data;
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
                for (int i = 0; i < _Texture2Ds.size(); i++)
                {
                    TextureGuiNode(i);
                }
            	
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem("Cubemap"))
            {
                for (int i = 0; i < _Cubemaps.size(); i++)
                {
                    ImGui::Image((ImTextureID)_Cubemaps[i]->Texture()->ID(), ImVec2(50, 50));
                    ImGui::SameLine();
                    ImGui::Text("[%d] %s", i + 1, _Cubemaps[i]->Name.c_str());
                }
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
        ImGui::End();
    }
    if(openModelLoader)
    {
        ImGui::OpenPopup("Model Loader");
    }

    if (openTextureLoader)
    {
        ImGui::OpenPopup("Texture Loader");
    }
    if (_FileBrowser.showFileDialog("Model Loader", FileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".obj"))
    {
        LoadModel(_FileBrowser.selected_path, Default::GLPrograms::DeferredPrepass);
        Debug::Log("Loaded model from \"" + _FileBrowser.selected_path);
        //std::cout << _FileBrowser.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        //std::cout << _FileBrowser.selected_path << std::endl;    // The absolute path to the selected file

    }

    if (_FileBrowser.showFileDialog("Texture Loader", FileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".png,.jpg,.jpeg"))
    {
        LoadTexture(_FileBrowser.selected_path);
        Debug::Log("Loaded texture from \"" + _FileBrowser.selected_path);
        //std::cout << _FileBrowser.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        //std::cout << _FileBrowser.selected_path << std::endl;    // The absolute path to the selected file

    }
}
