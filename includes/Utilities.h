#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <windows.h>
#include <vector>
#include <map>
#include "WebSession.h"
class Utilities
{
public:
    static std::string CreateHeader(int ContentLength, std::string SessionID, int Status);
    static std::string GetCurrentFolder();
    // static std::vector<std::string> SplitString(std::string thisString, std::string Delimeter);
    static std::vector<std::string> GetFiles(std::string path);
    static std::string GetFileContents(std::string path);
};
#endif