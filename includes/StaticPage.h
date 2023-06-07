#ifndef STATIC_PAGE_H
#define STATIC_PAGE_H
#include "Route.h"
#include "Utilities.h"
#include "HTMLResponse.h"
#include "boost/algorithm/string.hpp"
class StaticPage : public Route
{
private:
    std::string URI;
    std::string fileContents;

public:
    bool CheckRoute(Header thisHeader);
    HTMLResponse Response(Header thisHeader);
    StaticPage(std::string fileName);
};
#endif