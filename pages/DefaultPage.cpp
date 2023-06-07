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
    std::string PageData = "SessionID: " + thisHeader.WebSession->GetSession() + "<br>";
    PageData+="Number of Clicks = "+std::to_string(thisHeader.WebSession->Clicks+1)+"<br>";
    for (size_t i = 0; i < thisHeader.Cookies.size(); i++)
    {
        PageData += "Cookie: " + thisHeader.Cookies[i].Name + " |||||   " + thisHeader.Cookies[i].Value + "<br>";
    }
    for (size_t i = 0; i < thisHeader.Parameters.size(); i++)
    {
        PageData += "Parameters: " + thisHeader.Parameters[i].Name + " |||||   " + thisHeader.Parameters[i].Value + "<br>";
    }
    PageData += "<form method=post enctype=\"multipart/form-data\"><input type=text name=test><br><input type=file name=test2><input type=submit></form>";
    HTMLResponse response(PageData, thisHeader.WebSession);
    thisHeader.WebSession->Clicks++;
    return response;
}
DefaultPage::DefaultPage()
{
}