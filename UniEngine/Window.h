#pragma once
#include "Misc.h"
#include "Texture2D.h"
#include "Math.h"
#include "Default.h"
namespace UniEngine {
	class Window
	{
		GLFWwindow* _Window;
		uint _Width;
		uint _Height;
		friend class WindowManager;
		void SetSize(uint width, uint height);
	public:
		Window(GLFWwindow* window, uint width, uint height) {
			_Window = window;
			_Width = width;
			_Height = height;
		};
		float2 GetSize();
		GLFWwindow* GLFWwindow();
		void Update(Texture2D* texture);
	};
}
