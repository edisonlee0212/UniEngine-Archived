#include "pch.h"
#include "FileIO.h"
#include <sstream>
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Debug.h"
#include "WindowManager.h"
std::string* UniEngine::FileIO::_ResourceRootPath = nullptr;

void UniEngine::FileIO::SetResourcePath(std::string path)
{
    if (_ResourceRootPath != nullptr) delete _ResourceRootPath;
    _ResourceRootPath = new std::string(path);
}

std::string UniEngine::FileIO::GetResourcePath(std::string path)
{
    return *_ResourceRootPath + path;
}

std::string UniEngine::FileIO::LoadFileAsString(std::string path)
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
