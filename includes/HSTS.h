#ifndef HSTS_H
#define HSTS_H
#include <string>
class HSTS
{
public:
    bool Enabled = true;
    int MaxAge = 63072000;
    bool includeSubDomains = true;
    bool preload = true;
    std::string Output();
};
#endif