#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <vector>
#include <map>
#include "WebSession.h"
#include <boost/dll/runtime_symbol_info.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
class Utilities
{
public:
    static std::string CreateHeader(int ContentLength, std::string SessionID, int Status);
    static std::string GetCurrentFolder();
    static std::vector<std::string> GetFiles(std::string path);
    static std::string GetFileContents(std::string path);
};
#endif