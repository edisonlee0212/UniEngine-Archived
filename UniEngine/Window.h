#pragma once
#include "Misc.h"
#include "Texture2D.h"
#include "Math.h"
#include "Default.h"
namespace UniEngine {
	class Window
	{
		GLFWwindow* _Window;
		unsigned _Width;
		unsigned _Height;
		friend class WindowManager;
		void SetSize(unsigned width, unsigned height);
	public:
		Window(GLFWwindow* window, unsigned width, unsigned height) {
			_Window = window;
			_Width = width;
			_Height = height;
		};
		float2 GetSize();
		GLFWwindow* GLFWwindow();
		void Update(Texture2D* texture);
	};
}
