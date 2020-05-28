#pragma once
#include "Core.h"
#include "ManagerBase.h"

#include "Mesh.h"
#include "Material.h"
#include "RenderTarget.h"


#include "Camera.h"
#include "Cubemap.h"
#include "Texture2D.h"


namespace UniEngine {
	class RenderManager : public ManagerBase
	{
		friend class RenderTarget;
		static RenderTarget* _CurrentRenderTarget;
		static unsigned _Triangles;
		static unsigned _DrawCall;

		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, size_t count);
		static void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material);
	public:
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, size_t count, Camera* camera);
		static void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, Camera* camera);

		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, size_t count, RenderTarget* target);
		static void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, RenderTarget* target);

	};
}
