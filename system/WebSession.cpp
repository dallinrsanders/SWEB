#include "WebSession.h"
std::string WebSession::GetSession()
{
    return SessionID;
}
void WebSession::SetSession()
{
    std::string AllLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()[]{}':,./?`~";
    SessionID = "";
    for (int i = 0; i < 32; i++)
    {
        SessionID += AllLetters[std::rand() % AllLetters.length()];
    }
}
void WebSession::UpdateTime()
{
    LastUsed = time(NULL);
}
bool WebSession::CheckTime()
{
    if (time(NULL) - LastUsed < 15 * 60)
    {
        return true;
    }
    return false;
}