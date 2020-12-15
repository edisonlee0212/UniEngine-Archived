#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"

namespace UniEngine {
	class UNIENGINE_API WindowManager : public Singleton<WindowManager>
	{
	public:
		static void LateUpdate();
		static void Init(std::string name, bool fullScreen = false);
		static GLFWwindow* GetWindow();
		static GLFWmonitor* PrimaryMonitor();
		static void PreUpdate();
		static void Swap();
		static void DrawTexture(GLTexture2D* texture);
		static void ResizeCallback(GLFWwindow*, int, int);
		static void SetMonitorCallback(GLFWmonitor* monitor, int event);
	private:
		static bool _EnableMenu;
		static std::vector<GLFWmonitor*> _Monitors;
		static GLFWmonitor* _PrimaryMonitor;
		static GLFWwindow* _Window;
		static unsigned _WindowWidth;
		static unsigned _WindowHeight;
	};

}
