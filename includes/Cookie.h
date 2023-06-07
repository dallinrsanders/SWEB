#ifndef COOKIE_H
#define COOKIE_H
#include <string>
class Cookie
{
public:
    std::string Name;
    std::string Value;
    bool Secure = false;
    bool HttpOnly = false;
};
#endif