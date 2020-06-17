#pragma once
#include "UniEngineAPI.h"
#include "Debug.h"
namespace UniEngine {
	class UECORE_API FileIO {
	public:
		static std::string GetPath(std::string path);

		static std::string LoadFileAsString(std::string path);
	};
}