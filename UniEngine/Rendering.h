#pragma once
#include "Mesh.h"
#include "Material.h"
#include "RenderTarget.h"
namespace UniEngine {
	class Rendering
	{
		static RenderTarget* _CurrentRenderTarget;
		static uint _Triangles;
		static uint _DrawCall;
	public:
		static void DrawMeshInstanced(Mesh* mesh, Material* material, float4x4* matrices, size_t count, RenderTarget* target);
		static void DrawMesh(Mesh* mesh, float4x4 matrix, Material* material, RenderTarget* target);
	};
}
