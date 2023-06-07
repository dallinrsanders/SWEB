#ifndef ROUTE_H
#define ROUTE_H
#include <string>
#include "Header.h"
#include "HTMLResponse.h"
class Route
{
public:
    virtual bool CheckRoute(Header thisHeader) { return false; };
    virtual HTMLResponse Response(Header thisHeader)
    {
        HTMLResponse response(std::string("Bye"), thisHeader.WebSession);
        return response;
    };
    bool CreateHeader(int ContentSize);
};
#endif