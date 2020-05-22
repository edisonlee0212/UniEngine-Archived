#include "FileIO.h"

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
