#pragma once
#include "UniEngineAPI.h"

namespace UniEngine {
	class UNIENGINE_API FileIO {
		static std::unique_ptr<std::string> _ProjectPath;
		static std::unique_ptr<std::string> _ResourceRootPath;
	public:
		static std::string GetAssetFolderPath();
		static void SetProjectPath(const std::string& path);
		static std::string GetProjectPath();
		static void SetResourcePath(const std::string& path);
		static std::string GetResourcePath(const std::string& path = "");
		static std::string LoadFileAsString(const std::string& path = "");

		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);

		static std::pair<bool, uint32_t> DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask);
	};
}