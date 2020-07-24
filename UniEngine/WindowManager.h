#pragma once
#include "UniEngineAPI.h"
#include "Window.h"
#include "Texture2D.h"
namespace UniEngine {
	class UNIENGINE_API WindowManager : public ManagerBase
	{
	public:
		static void Init();
		static GLFWwindow* CreateGLFWwindow(unsigned width, unsigned height, std::string name, GLFWmonitor* monitor);
		static std::vector<Window*>* Windows();
		static Window* CurrentWindow();
		static GLFWmonitor* PrimaryMonitor();
		static void Update();
		static void ResizeCallback(GLFWwindow*, int, int);
		static void SetMonitorCallback(GLFWmonitor* monitor, int event);
		static Window* NewWindow(GLFWwindow* window, unsigned resolutionX, unsigned resolutionY);
	private:
		static std::vector<GLFWmonitor*> _Monitors;
		static GLFWmonitor* _PrimaryMonitor;
		static Window* _CurrentWindow;
		static std::vector<Window*> _Windows;
		
	};

}
