#pragma once
#include "Core.h"
#include "Material.h"
#include "Mesh.h"
#include "UniEngineAPI.h"


namespace UniEngine {
	class UNIENGINE_API Default {
	public:
		class UNIENGINE_API GLPrograms {
		public:
			static std::shared_ptr<GLProgram> ScreenProgram;
			static GLVAO* ScreenVAO;

			static std::shared_ptr<GLVAO> SkyboxVAO;

			static std::shared_ptr<GLProgram> SkyboxProgram;
			static std::shared_ptr<GLProgram> DeferredPrepass;
			static std::shared_ptr<GLProgram> DeferredPrepassInstanced;

			static std::shared_ptr<GLProgram> StandardProgram;
			static std::shared_ptr<GLProgram> StandardInstancedProgram;
			
			static std::shared_ptr<GLProgram> GizmoProgram;
			static std::shared_ptr<GLProgram> GizmoInstancedProgram;
		};

		class UNIENGINE_API ShaderIncludes {
		public:
			static std::string* Uniform;

			const static size_t MaxMaterialsAmount = 1;
			
			const static size_t MaxDirectionalLightAmount = 4;
			const static size_t MaxPointLightAmount = 16;
			const static size_t MaxSpotLightAmount = 16;
			const static size_t ShadowCascadeAmount = 4;
		};

		class UNIENGINE_API Textures {
		public:
			static std::shared_ptr<Texture2D> MissingTexture;
			static std::shared_ptr<Texture2D> UV;
			static std::shared_ptr<Texture2D> StandardTexture;
			static std::shared_ptr<Cubemap> DefaultSkybox;
		};

		class UNIENGINE_API Primitives {
		public:
			static std::shared_ptr<Mesh> Sphere;
			static std::shared_ptr<Mesh> Cube;
			static std::shared_ptr<Mesh> Quad;
			static std::shared_ptr<Mesh> FrontBackQuad;
			static std::shared_ptr<Mesh> Cylinder;
			static std::shared_ptr<Mesh> Cone;
			static std::shared_ptr<Mesh> Ring;
			static std::shared_ptr<Mesh> Monkey;
		};

		static void Load(World* world);
	};

}
