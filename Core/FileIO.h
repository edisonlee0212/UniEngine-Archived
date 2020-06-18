#pragma once
#include "CoreAPI.h"
#include "Debug.h"
namespace UniEngine {
	class CORE_API FileIO {
	public:
		static std::string GetPath(std::string path);

		static std::string LoadFileAsString(std::string path);
	};
}