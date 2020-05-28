#include "MeshMaterialComponent.h"

size_t UniEngine::MeshMaterialComponent::GetHashCode()
{
	return (size_t)_Mesh + (size_t)_Material;
}
