#ifndef URLPARAMETERS_H
#define URLPARAMETERS_H
#include <string>
#include <map>
class URLParameter
{
public:
    std::string Name;
    std::string Value;
    std::string FileName;
    void setName(std::string name);
    void setValue(std::string value);
    std::string URLDecode(std::string value);
};
#endif