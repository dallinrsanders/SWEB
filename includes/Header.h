#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <vector>
#include "WebSession.h"
#include "Cookie.h"
#include "URLParameter.h"
class Header
{
public:
    std::string Method;
    std::string Host;
    std::vector<URLParameter> Parameters;
    std::string Page;
    std::vector<Cookie> Cookies;
    WebSession * WebSession;
    std::vector<URLParameter> PostParameters;
};
#endif