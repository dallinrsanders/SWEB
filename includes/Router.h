#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include "Route.h"
#include "Header.h"
class Router
{
private:
    std::vector<Route *> allRoutes;

public:
    void LoadRoutes();
    Route *CheckRoute(Header thisHeader);
};
#endif