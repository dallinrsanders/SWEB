#ifndef XFRAME_H
#define XFRAME_H
#include <string>
class XFrame
{
public:
    bool Enabled = true;
    std::string Value = "deny";
    std::string Output() { return "X-Frame-Options: " + Value + "\r\n"; }
};
#endif