#include "E404.h"
bool E404Page::CheckRoute(Header thisHeader)
{
    return true;
}
HTMLResponse E404Page::Response(Header thisHeader)
{
    std::string PageData = "<h1>Page Not Found!</h1>";
    HTMLResponse response(PageData, thisHeader.WebSession);
    response.setStatus(404);
    return response;
}