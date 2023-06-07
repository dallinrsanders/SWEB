#ifndef CSP_H
#define CSP_H
#include <string>
class CSP
{
public:
    bool Enabled = true;
    std::string SourceValue = "default-src";
    std::string SpecialKeyword = "self";
    std::string Output() { return "Content-Security-Policy: " + SourceValue + " '" + SpecialKeyword + "'\r\n"; }
};
#endif