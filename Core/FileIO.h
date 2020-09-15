#pragma once
#include "CoreAPI.h"
#include "Debug.h"

namespace UniEngine
{
	class CORE_API FileIO
	{
		static std::string* _ResourceRootPath;
	public:
		static void SetResourcePath(std::string path);
		static std::string GetResourcePath(std::string path);

		static std::string LoadFileAsString(std::string path);
	};
}
