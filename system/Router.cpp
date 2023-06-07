#include "Router.h"
#include "E404.h"
#include "DefaultPage.h"
#include "StaticPage.h"
#include "Utilities.h"
void Router::LoadRoutes()
{
    DefaultPage *defaultPage = new DefaultPage();
    allRoutes.push_back(defaultPage);

    // Load Static Pages
    std::vector<std::string> allFiles = Utilities::GetFiles(Utilities::GetCurrentFolder() + "static");
    for (size_t i = 0; i < allFiles.size(); i++)
    {
        StaticPage *thisPage = new StaticPage(allFiles[i]);
        allRoutes.push_back(thisPage);
    }
    // E404Page must be last one in route because it will always return true;
    E404Page *RouteNotFound = new E404Page();
    allRoutes.push_back(RouteNotFound);
}
Route *Router::CheckRoute(Header thisHeader)
{
    for (size_t i = 0; i < allRoutes.size(); i++)
    {
        if (allRoutes[i]->CheckRoute(thisHeader))
        {
            return allRoutes[i];
        }
    }
    return allRoutes.back();
}