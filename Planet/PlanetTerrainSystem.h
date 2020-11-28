#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
	class PlanetTerrainSystem :
		public SystemBase
	{
		static std::shared_ptr<Material> _DefaultSurfaceMaterial;
	public:
		void OnCreate() override;
		void Update() override;
		void FixedUpdate() override;
		static std::shared_ptr<Material> GetDefaultSurfaceMaterial();
		void CheckLod(std::mutex& mutex, std::unique_ptr<TerrainChunk>& chunk, const PlanetInfo& info, const LocalToWorld& planetTransform, const LocalToWorld& cameraTransform);
		void RenderChunk(std::unique_ptr<TerrainChunk>& chunk, Material* material, glm::mat4& matrix, CameraComponent* camera, bool receiveShadow);
	};
}