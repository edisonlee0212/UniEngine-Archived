#pragma once
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "MeshMaterialComponent.h"
#include "InstancedMeshMaterialComponent.h"
#include "RenderTarget.h"



#include "Cubemap.h"
#include "Texture2D.h"


namespace UniEngine {
	class UNIENGINE_API RenderManager : public ManagerBase
	{
		friend class RenderTarget;
		static size_t _Triangles;
		static size_t _DrawCall;
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, bool receiveShadow);
		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, bool receiveShadow);
		
		static void DrawGizmoInstanced(Mesh* mesh, glm::vec4 color, glm::mat4 model, glm::mat4* matrices, size_t count, glm::mat4 scaleMatrix);
		static void DrawGizmo(Mesh* mesh, glm::vec4 color, glm::mat4 matrix);

		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size);
	public:
		static void Start();
		static size_t Triangles();
		static size_t DrawCall();

		static void DrawTexture2D(GLTexture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, glm::vec2 center, glm::vec2 size, RenderTarget* target);
		static void DrawTexture2D(Texture2D* texture, float depth, float centerX, float centerY, float sizeX, float sizeY, RenderTarget* target);

		static void DrawMesh(Mesh* mesh, Material* material, glm::mat4 model, RenderTarget* target, bool receiveShadow = true);
		static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4 model, glm::mat4* matrices, size_t count, RenderTarget* target, bool receiveShadow = true);

		static void DrawGizmoPoint(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoPointInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCube(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoCubeInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuad(glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoQuadInstanced(glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMesh(Mesh* mesh, glm::vec4 color, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
		static void DrawGizmoMeshInstanced(Mesh* mesh, glm::vec4 color, glm::mat4* matrices, size_t count, RenderTarget* target, glm::mat4 model = glm::mat4(1.0f), float size = 1.0f);
	};
}
