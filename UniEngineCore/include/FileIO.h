#pragma once
#include "Misc.h"
#include "Debug.h"
namespace UniEngine {
	class FileIO {
	public:
		static std::string GetPath(std::string path) {
			return "Resources/" + path;
		}

		static std::string LoadFileAsString(std::string path);
	};
}