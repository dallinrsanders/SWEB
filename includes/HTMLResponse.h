#ifndef HTMLRESPONSE_H
#define HTMLRESPONSE_H
#include <string>
#include <vector>
#include "Cookie.h"
#include "WebSession.h"
#include "HSTS.h"
#include "CSP.h"
#include "XFrame.h"
class HTMLResponse
{
private:
    std::string Data;
    int Status = 200;
    std::vector<Cookie> Cookies;
    WebSession * thisSession;
    HSTS hsts;
    CSP csp;
    XFrame xFrame;
    std::string ContentType = "text/html";

public:
    HTMLResponse(std::string Data, WebSession * session);
    void setStatus(int status);
    void addCookie(Cookie thisCookie);
    std::string Output();
    void setContentType(std::string contentType);
};
#endif