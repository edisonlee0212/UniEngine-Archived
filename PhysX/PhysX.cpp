#include "UniEngine.h"

using namespace UniEngine;

int main()
{
	FileIO::SetResourcePath("../Resources/");
	RenderManager::SetEnableSSAO(true);
	Application::Init();
#pragma region EngineLoop
	bool loopable = true;
	//Start engine. Here since we need to inject procedures to the main engine loop we need to manually loop by our self.
	//Another way to run engine is to simply execute:
	//Application.Run();
	while (loopable) {
		Application::PreUpdate();
		
		Application::Update();
		loopable = Application::LateUpdate();
	}
	Application::End();
#pragma endregion
	return 0;
}
