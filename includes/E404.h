#ifndef E404_PAGE
#define E404_PAGE
#include "Route.h"
#include "Utilities.h"
class E404Page : public Route
{
public:
    bool CheckRoute(Header thisHeader);
    HTMLResponse Response(Header thisHeader);
};
#endif