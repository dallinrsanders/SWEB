#include "HSTS.h"
std::string HSTS::Output()
{
    std::string output = "Strict-Transport-Security: max-age=" + std::to_string(MaxAge) + ";";
    if (includeSubDomains)
    {
        output += "includeSubDomains;";
    }
    if (preload)
    {
        output += "preload";
    }
    output += "\r\n";
    return output;
}