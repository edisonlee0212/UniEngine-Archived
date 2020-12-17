#include "pch.h"
#include "FileIO.h"
#include "Debug.h"
#include "WindowManager.h"
std::unique_ptr<std::string> UniEngine::FileIO::_ResourceRootPath = std::make_unique<std::string>("../Resources/");
std::unique_ptr<std::string> UniEngine::FileIO::_ProjectPath;

std::string UniEngine::FileIO::GetAssetFolderPath()
{
	std::string path = GetProjectPath() + "Assets";
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directory(path);
	}
	return path;
}

void UniEngine::FileIO::SetProjectPath(const std::string& path)
{
	_ProjectPath = std::make_unique<std::string>(path);
}

std::string UniEngine::FileIO::GetProjectPath()
{
	std::string path;
	if (!_ProjectPath) path = GetResourcePath();
	else path = *_ProjectPath;
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directory(path);
	}
	return path;
}

void UniEngine::FileIO::SetResourcePath(const std::string& path)
{
	_ResourceRootPath = std::make_unique<std::string>(path);
}

std::string UniEngine::FileIO::GetResourcePath(const std::string& path)
{
	return *_ResourceRootPath + path;
}

std::string UniEngine::FileIO::LoadFileAsString(const std::string& path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		file.open(path);
		std::stringstream stream;
		// read file's buffer contents into streams
		stream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		return stream.str();
	}
	catch (std::ifstream::failure e)
	{
		Debug::Error("FILESYSTEM::FILE_NOT_SUCCESFULLY_READ");
		return "";
	}
}

std::optional<std::string> UniEngine::FileIO::OpenFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)WindowManager::GetWindow());
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		std::string retVal = ofn.lpstrFile;
		const std::string search = "\\";
		size_t pos = retVal.find(search);
		// Repeat till end is reached
		while (pos != std::string::npos)
		{
			// Replace this occurrence of Sub String
			retVal.replace(pos, 1, "/");
			// Get the next occurrence from the current position
			pos = retVal.find(search, pos + 1);
		}
		return retVal;
	}

	return std::nullopt;
}

std::optional<std::string> UniEngine::FileIO::SaveFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)WindowManager::GetWindow());
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	// Sets the default extension by extracting it from the filter
	ofn.lpstrDefExt = strchr(filter, '\0') + 1;

	if (GetSaveFileNameA(&ofn) == TRUE) {
		std::string retVal = ofn.lpstrFile;
		const std::string search = "\\";
		size_t pos = retVal.find(search);
		// Repeat till end is reached
		while (pos != std::string::npos)
		{
			// Replace this occurrence of Sub String
			retVal.replace(pos, 1, "/");
			// Get the next occurrence from the current position
			pos = retVal.find(search, pos + 1);
		}
		return retVal;
	}
	return std::nullopt;
}

std::pair<bool, uint32_t> UniEngine::FileIO::DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask)
{
	const ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth;

	bool anyNodeClicked = false;
	uint32_t nodeClicked = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		ImGuiTreeNodeFlags nodeFlags = baseFlags;
		const bool isSelected = (*selection_mask & (1 << (*count))) != 0;
		if (isSelected)
			nodeFlags |= ImGuiTreeNodeFlags_Selected;

		std::string name = entry.path().string();

		auto lastSlash = name.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		name = name.substr(lastSlash, name.size() - lastSlash);

		const bool entryIsFile = !std::filesystem::is_directory(entry.path());
		if (entryIsFile)
			nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		const bool nodeOpen = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<intptr_t>(*count)), nodeFlags, name.c_str());

		if (ImGui::IsItemClicked())
		{
			nodeClicked = *count;
			anyNodeClicked = true;
		}

		(*count)--;

		if (!entryIsFile)
		{
			if (nodeOpen)
			{
				const auto clickState = DirectoryTreeViewRecursive(entry.path(), count, selection_mask);

				if (!anyNodeClicked)
				{
					anyNodeClicked = clickState.first;
					nodeClicked = clickState.second;
				}

				ImGui::TreePop();
			}
			else
			{
				for (const auto& e : std::filesystem::recursive_directory_iterator(entry.path()))
					(*count)--;
			}
		}
	}

	return { anyNodeClicked, nodeClicked };
}
