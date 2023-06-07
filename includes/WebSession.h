#ifndef WEBSESSION_H
#define WEBSESSION_H
#include <string>
#include <cstdlib>
#include "Utilities.h"
class WebSession
{
private:
    std::string SessionID;
    time_t LastUsed;

public:
    std::string GetSession();
    void SetSession();
    void UpdateTime();
    bool CheckTime();
    int Clicks=0;
};
#endif