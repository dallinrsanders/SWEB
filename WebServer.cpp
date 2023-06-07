#include "Server.h"
int main(int argc, char *argv[])
{
    std::srand((unsigned)time(NULL));
    std::map<std::string, WebSession> allSessions;
    boost::asio::io_service io_service;

    Server mainServer(io_service, &allSessions);

    std::thread oldSessions(ClearOldSessions, &allSessions);
    io_service.run();
    oldSessions.join();
    return 0;
}