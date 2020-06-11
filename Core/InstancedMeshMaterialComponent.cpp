#include "pch.h"
#include "InstancedMeshMaterialComponent.h"

size_t UniEngine::InstancedMeshMaterialComponent::GetHashCode()
{
	return ((size_t)_Matrices + (size_t)_Mesh + (size_t)_Material);
}
