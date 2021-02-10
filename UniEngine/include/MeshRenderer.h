#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Mesh.h"
#include "Material.h"
namespace UniEngine {
	class UNIENGINE_API MeshRenderer :
		public PrivateComponentBase
	{
		friend class EditorManager;
		void RenderBound(glm::vec4& color) const;
	public:
		glm::vec4 DisplayBoundColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);;
		bool DisplayBound = true;
		bool ForwardRendering = false;
		bool CastShadow = true;
		bool ReceiveShadow = true;
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;
		void OnGui() override;
		MeshRenderer();
		~MeshRenderer() override;
		void Serialize(YAML::Emitter& out) override;
		void Deserialize(const YAML::Node& in) override;
	};
}

