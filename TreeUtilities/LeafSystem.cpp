#include "pch.h"
#include "LeafSystem.h"
#include "TreeManager.h"
void TreeUtilities::LeafSystem::DrawGUI()
{
	ImGui::Begin("TreeUtilities");
	if (ImGui::CollapsingHeader("Leaf System", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Leaf Amount: %d ", _LeafEntities.size());
		ImGui::Separator();
		ImGui::CheckboxFlags("Draw Leafs", &_ConfigFlags, LeafSystem_DrawLeafs);
	}
	ImGui::End();
}
void TreeUtilities::LeafSystem::OnCreate()
{
	_LeafQuery = TreeManager::GetLeafQuery();
	_BudQuery = TreeManager::GetBudQuery();
	_TreeQuery = TreeManager::GetTreeQuery();

	_ConfigFlags = 0;
	_ConfigFlags += LeafSystem_DrawLeafs;

	_LeafMesh = new Mesh();
	std::vector<Vertex> leafVertices;
	std::vector<unsigned> leafIndices;

	float leafLength = 2;
	float leafWidth = 1;
	float leafThickness = 0.0f;
	float middleHeight = 0.3f;

	Vertex v;
	v.Position = glm::vec3(0, 0, 0);
	v.TexCoords0 = glm::vec2(0, 0);
	leafVertices.push_back(v);

	v.Position = glm::vec3(leafWidth / 2.0f, middleHeight + leafThickness / 2.0f, leafLength / 2.0f);
	v.TexCoords0 = glm::vec2(0, 1);
	leafVertices.push_back(v);
	v.Position = glm::vec3(-leafWidth / 2.0f, middleHeight + leafThickness / 2.0f, leafLength / 2.0f);
	v.TexCoords0 = glm::vec2(1, 0);
	leafVertices.push_back(v);
	v.Position = glm::vec3(leafWidth / 2.0f, middleHeight - leafThickness / 2.0f, leafLength / 2.0f);
	v.TexCoords0 = glm::vec2(0, 1);
	leafVertices.push_back(v);
	v.Position = glm::vec3(-leafWidth / 2.0f, middleHeight - leafThickness / 2.0f, leafLength / 2.0f);
	v.TexCoords0 = glm::vec2(1, 0);
	leafVertices.push_back(v);

	v.Position = glm::vec3(0, 0, leafLength);
	v.TexCoords0 = glm::vec2(1, 1);
	leafVertices.push_back(v);

	leafIndices.push_back(0);
	leafIndices.push_back(2);
	leafIndices.push_back(1);

	leafIndices.push_back(5);
	leafIndices.push_back(1);
	leafIndices.push_back(2);

	leafIndices.push_back(0);
	leafIndices.push_back(4);
	leafIndices.push_back(3);

	leafIndices.push_back(5);
	leafIndices.push_back(3);
	leafIndices.push_back(4);

	leafIndices.push_back(0);
	leafIndices.push_back(3);
	leafIndices.push_back(2);

	leafIndices.push_back(5);
	leafIndices.push_back(2);
	leafIndices.push_back(3);

	leafIndices.push_back(0);
	leafIndices.push_back(1);
	leafIndices.push_back(4);

	leafIndices.push_back(5);
	leafIndices.push_back(4);
	leafIndices.push_back(1);

	_LeafMesh->SetVertices((unsigned)VertexAttribute::Position | (unsigned)VertexAttribute::TexCoord0,
		&leafVertices, &leafIndices);

	Enable();
}

void TreeUtilities::LeafSystem::OnDestroy()
{
}

void TreeUtilities::LeafSystem::Update()
{
	_LeafEntities.clear();
	_LeafQuery.ToEntityArray(&_LeafEntities);

	std::vector<TreeIndex> treeIndices;
	_TreeQuery.ToComponentDataArray(&treeIndices);
	std::vector<TreeColor> treeColors;
	_TreeQuery.ToComponentDataArray(&treeColors);
	auto treeEntities = TreeManager::GetTreeSystem()->GetTreeEntities();
	if (_ConfigFlags & LeafSystem_DrawLeafs) {
		_LeafLTWList.clear();
		_LeafQuery.ToComponentDataArray(&_LeafLTWList);
		if (_LeafLTWList.size() != 0)RenderManager::DrawGizmoMeshInstanced(_LeafMesh, glm::vec4(0, 1, 0, 1), (glm::mat4*)_LeafLTWList.data(), _LeafLTWList.size(), Application::GetMainCameraComponent()->Value, glm::mat4(1.0f), 1.0f);
	}

	DrawGUI();
}

void TreeUtilities::LeafSystem::FixedUpdate()
{
}

Mesh* TreeUtilities::LeafSystem::GetLeafMesh()
{
	return _LeafMesh;
}

std::vector<Entity>* TreeUtilities::LeafSystem::GetTreeEntities()
{
	return &_LeafEntities;
}
