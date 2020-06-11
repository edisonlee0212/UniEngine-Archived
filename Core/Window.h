#pragma once
#include "Core.h"
#include "RenderManager.h"
namespace UniEngine {
	class UECORE_API Window : public RenderTarget
	{
		GLFWwindow* _Window;
		GLTexture* _ColorTexture;
		GLRenderBuffer* _RenderBuffer;
		unsigned _Width;
		unsigned _Height;
		friend class WindowManager;
		void SetSizeCallback(unsigned width, unsigned height);
	public:
		Window(GLFWwindow* window, unsigned width, unsigned height);
		glm::vec2 GetWindowSize();
		GLFWwindow* GetGLFWWinwow();
		void Update(Texture2D* texture);
		void Update();
	};
}
