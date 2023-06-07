#ifndef DEFAULT_PAGE
#define DEFAULT_PAGE
#include "Route.h"
#include "Utilities.h"
#include "HTMLResponse.h"
class DefaultPage : public Route
{
public:
    bool CheckRoute(Header thisHeader);
    HTMLResponse Response(Header thisHeader);
    DefaultPage();
};
#endif