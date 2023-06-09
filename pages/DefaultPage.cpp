#include "DefaultPage.h"
bool DefaultPage::CheckRoute(Header thisHeader)
{
    if (thisHeader.Page == "/")
    {
        return true;
    }
    return false;
}
HTMLResponse DefaultPage::Response(Header thisHeader)
{
    std::string PageData = "SessionID: " + thisHeader.Session->GetSession() + "<br>";
    PageData+="Number of Clicks = "+std::to_string(thisHeader.Session->Clicks+1)+"<br>";
    for (size_t i = 0; i < thisHeader.Cookies.size(); i++)
    {
        PageData += "Cookie: " + thisHeader.Cookies[i].Name + " |||||   " + thisHeader.Cookies[i].Value + "<br>";
    }
    for (size_t i = 0; i < thisHeader.Parameters.size(); i++)
    {
        PageData += "Parameters: " + thisHeader.Parameters[i].Name + " |||||   " + thisHeader.Parameters[i].Value + "<br>";
    }
    HTMLResponse response(PageData, thisHeader.Session);
    thisHeader.Session->Clicks++;
    return response;
}
DefaultPage::DefaultPage()
{
}