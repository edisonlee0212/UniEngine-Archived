#include "pch.h"
#include "FileIO.h"

#include "Debug.h"
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
