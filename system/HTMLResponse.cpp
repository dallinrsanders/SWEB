#include "HTMLResponse.h"
HTMLResponse::HTMLResponse(std::string data, WebSession * session)
{
    Data = data;
    thisSession = session;
}
void HTMLResponse::setStatus(int status)
{
    Status = status;
}
void HTMLResponse::addCookie(Cookie thisCookie)
{
    Cookies.push_back(thisCookie);
}
std::string HTMLResponse::Output()
{

    std::string HTMLHeader = "HTTP/1.1 ";
    switch (Status)
    {
    case 100:
        HTMLHeader += "100 Continue\r\n";
        break;
    case 101:
        HTMLHeader += "101 Switching Protocols\r\n";
        break;
    case 102:
        HTMLHeader += "102 Processing (WebDAV)\r\n";
        break;
    case 103:
        HTMLHeader += "103 Early Hints Exprimental\r\n";
        break;
    case 200:
        HTMLHeader += "200 OK\r\n";
        break;
    case 201:
        HTMLHeader += "201 Created\r\n";
        break;
    case 202:
        HTMLHeader += "202 Accepted\r\n";
        break;
    case 203:
        HTMLHeader += "203 Non-Authoritative Information\r\n";
        break;
    case 204:
        HTMLHeader += "204 No Content\r\n";
        break;
    case 205:
        HTMLHeader += "205 Reset Content\r\n";
        break;
    case 206:
        HTMLHeader += "206 Partial Content\r\n";
        break;
    case 207:
        HTMLHeader += "207 Multi-Status(WebDAV)\r\n";
        break;
    case 208:
        HTMLHeader += "208 Already Reported (WebDAV)\r\n";
        break;
    case 226:
        HTMLHeader += "226 IM Used (HTTP Delta encoding)\r\n";
        break;
    case 300:
        HTMLHeader += "300 Multiple Choices\r\n";
        break;
    case 301:
        HTMLHeader += "301 Moved Permanently\r\n";
        break;
    case 302:
        HTMLHeader += "302 Found\r\n";
        break;
    case 303:
        HTMLHeader += "303 See Other\r\n";
        break;
    case 304:
        HTMLHeader += "304 Not Modified\r\n";
        break;
    case 305:
        HTMLHeader += "305 Use Proxy Deprecated\r\n";
        break;
    case 306:
        HTMLHeader += "306 unused\r\n";
        break;
    case 307:
        HTMLHeader += "307 Temporary Redirect\r\n";
        break;
    case 308:
        HTMLHeader += "308 Permanent Redirect\r\n";
        break;
    case 400:
        HTMLHeader += "400 Bad Request\r\n";
        break;
    case 401:
        HTMLHeader += "401 Unauthorized\r\n";
        break;
    case 402:
        HTMLHeader += "402 Paymeent Required Experimental\r\n";
        break;
    case 403:
        HTMLHeader += "403 Forbidden\r\n";
        break;
    case 404:
        HTMLHeader += "404 Not Found\r\n";
        break;
    case 405:
        HTMLHeader += "405 Method Not Allowed\r\n";
        break;
    case 406:
        HTMLHeader += "406 Not Acceptable\r\n";
        break;
    case 407:
        HTMLHeader += "407 Proxy Authentication Required\r\n";
        break;
    case 408:
        HTMLHeader += "408 Request Timeout\r\n";
        break;
    case 409:
        HTMLHeader += "409 Conflict\r\n";
        break;
    case 410:
        HTMLHeader += "410 Gone\r\n";
        break;
    case 411:
        HTMLHeader += "411 Length Required\r\n";
        break;
    case 412:
        HTMLHeader += "412 Precondition Failed\r\n";
        break;
    case 413:
        HTMLHeader += "413 Payload Too Large\r\n";
        break;
    case 414:
        HTMLHeader += "414 URI Too Long\r\n";
        break;
    case 415:
        HTMLHeader += "415 Unsupported Media Type\r\n";
        break;
    case 416:
        HTMLHeader += "416 Range Not Satisfiable\r\n";
        break;
    case 417:
        HTMLHeader += "417 Excpectation Failed\r\n";
        break;
    case 418:
        HTMLHeader += "418 I'm a teapot\r\n";
        break;
    case 421:
        HTMLHeader += "421 Misdirected Request\r\n";
        break;
    case 422:
        HTMLHeader += "422 Unprocessable Content (WebDAV)\r\n";
        break;
    case 423:
        HTMLHeader += "423 Locked (WebDAV)\r\n";
        break;
    case 424:
        HTMLHeader += "424 Failed Dependency (WebDAV)\r\n";
        break;
    case 425:
        HTMLHeader += "425 Too Early Experimental\r\n";
        break;
    case 426:
        HTMLHeader += "426 Upgrade Required\r\n";
        break;
    case 428:
        HTMLHeader += "428 Precondition Required\r\n";
        break;
    case 429:
        HTMLHeader += "429 Too Many Requests\r\n";
        break;
    case 431:
        HTMLHeader += "431 Request Header Fields Too Large\r\n";
        break;
    case 451:
        HTMLHeader += "451 Unavailable For Legal Reasons\r\n";
        break;
    case 500:
        HTMLHeader += "500 Internal Server Error\r\n";
        break;
    case 501:
        HTMLHeader += "501 Not Implemented\r\n";
        break;
    case 502:
        HTMLHeader += "502 Bad Gateway\r\n";
        break;
    case 503:
        HTMLHeader += "503 Service Unavailable\r\n";
        break;
    case 504:
        HTMLHeader += "504 Gateway Timeout\r\n";
        break;
    case 505:
        HTMLHeader += "505 HTTP Version Not Supported\r\n";
        break;
    case 506:
        HTMLHeader += "506 Variant Also Negotiates\r\n";
        break;
    case 507:
        HTMLHeader += "507 Insufficient Storage (WebDAV)\r\n";
        break;
    case 508:
        HTMLHeader += "508 Loop Detected\r\n";
        break;
    case 510:
        HTMLHeader += "510 Not Extended\r\n";
        break;
    case 511:
        HTMLHeader += "511 Network Authentication Required\r\n";
        break;
    default:
        HTMLHeader += std::to_string(Status);
        break;
    }
    HTMLHeader += "Server: SWeb\r\nContent-Type: " + ContentType + "\r\n";
    HTMLHeader += "Set-Cookie: SessionID=" + thisSession->GetSession() + "; Secure; HttpOnly\r\n";
    for (size_t i = 0; i < Cookies.size(); i++)
    {
        HTMLHeader += "Set-Cookie: " + Cookies[i].Name + "=" + Cookies[i].Value + ";";
        if (Cookies[i].Secure)
        {
            HTMLHeader += " Secure;";
        }
        if (Cookies[i].HttpOnly)
        {
            HTMLHeader += " HttpOnly;";
        }
        HTMLHeader += "\r\n";
    }
    HTMLHeader += "Content-Length: ";
    HTMLHeader += std::to_string(Data.length()) + "\r\n";
    if (hsts.Enabled)
    {
        HTMLHeader += hsts.Output();
    }
    if (csp.Enabled)
    {
        HTMLHeader += csp.Output();
    }
    if (xFrame.Enabled)
    {
        HTMLHeader += xFrame.Output();
    }
    HTMLHeader += "\r\n";
    HTMLHeader += Data;
    return HTMLHeader;
}
void HTMLResponse::setContentType(std::string contentType)
{
    ContentType = contentType;
}