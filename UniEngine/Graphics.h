#pragma once
#include "GLProgram.h"
#include "GLTexture.h"

#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class Graphics
	{
		static void DrawMeshInstanced(Mesh* mesh, Material* pointMaterial, float4x4* matrices, size_t count);
		static void DrawMesh(Mesh* mesh, float4x4 matrix, Material* pointMaterial);
	};
}
