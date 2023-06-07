#include "Utilities.h"
#include <filesystem>
#include <fstream>
#include <sstream>
std::string Utilities::GetCurrentFolder()
{
    WCHAR path[MAX_PATH];
    char fullPath[MAX_PATH];
    WideCharToMultiByte(CP_ACP, (DWORD)NULL, path, -1, fullPath, MAX_PATH, NULL, NULL);
    std::string response(fullPath);
    size_t lastSlash = response.find_last_of('\\');
    response.resize(lastSlash + 1);
    return response;
}
std::vector<std::string> Utilities::GetFiles(std::string path)
{
    std::vector<std::string> response;
    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        if (file.is_directory())
        {
            std::vector<std::string> thisVector = GetFiles(file.path().string());
            for (size_t i = 0; i < thisVector.size(); i++)
            {
                response.push_back(thisVector[i]);
            }
        }
        else
        {
            response.push_back(file.path().string());
        }
    }
    return response;
}
std::string Utilities::GetFileContents(std::string path)
{
    std::ifstream infile(path, std::ifstream::binary);

    if (!std::filesystem::is_regular_file(path))
        return {};

    // Open the file
    // Note that we have to use binary mode as we want to return a string
    // representing matching the bytes of the file on the file system.
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return {};

    // Read contents
    std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    // Close the file
    file.close();
    return content;
}