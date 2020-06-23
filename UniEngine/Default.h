#pragma once
#include "UniEngineAPI.h"
#include "RenderManager.h"

namespace UniEngine {
	class UNIENGINE_API Default {
	public:
		static class UNIENGINE_API GLPrograms {
		public:
			static GLProgram* ScreenProgram;
			static GLVAO* ScreenVAO;

			static GLProgram* StandardProgram;
			static GLProgram* StandardInstancedProgram;
		};

		static class UNIENGINE_API ShaderIncludes {
		public:
			static std::string* Uniform;

			const static size_t MaxMaterialsAmount = 1;
			static std::string* Shadow;


			const static size_t MaxDirectionalLightAmount = 16;
			const static size_t MaxPointLightAmount = 16;
			const static size_t MaxSpotLightAmount = 16;
			static std::string* Lights;
		};

		static class UNIENGINE_API Textures {
		public:
			static Texture2D* MissingTexture;
			static Texture2D* UV;
			static Texture2D* StandardTexture;
		};

		static class UNIENGINE_API Primitives {
		public:
			static Mesh* Sphere;
			static Mesh* Cube;
			static Mesh* Quad;
			static Mesh* Cylinder;
			static Mesh* Cone;
			static Mesh* Monkey;
		};

		static class UNIENGINE_API Materials {
		public:
			static Material* StandardMaterial;
			static Material* StandardInstancedMaterial;
		};

		static void Load(World* world);
	};

}
