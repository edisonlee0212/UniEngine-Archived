#pragma once
#include "Misc.h"
#include "Core.h"
#include "ModelManager.h"
#include "RenderManager.h"

namespace UniEngine {
	class Default {
	public:
		static class GLPrograms {
		public:
			static GLProgram* ScreenProgram;
			static GLVAO* ScreenVAO;

			static GLProgram* StandardProgram;
			static GLProgram* StandardInstancedProgram;
		};

		static class ShaderIncludes {
		public:
			static std::string* Uniform;

			const static size_t MaxMaterialsAmount = 1;
			static std::string* Shadow;


			const static size_t MaxDirectionalLightAmount = 16;
			const static size_t MaxPointLightAmount = 16;
			const static size_t MaxSpotLightAmount = 16;
			static std::string* Lights;
		};

		static class Textures {
		public:
			static Texture2D* MissingTexture;
			static Texture2D* UV;
			static Texture2D* StandardTexture;
		};

		static class Primitives {
		public:
			static Mesh* Sphere;
			static Mesh* Cube;
			static Mesh* Quad;
			static Mesh* Cylinder;
			static Mesh* Cone;
		};

		static class Materials {
		public:
			static Material* StandardMaterial;
			static Material* StandardInstancedMaterial;
		};

		static void Load(World* world);
	};

}
