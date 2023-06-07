#ifndef SERVER_H
#define SERVER_H
#include <cstdlib>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "Router.h"
#include "Header.h"
#include "WebSession.h"
#include "Utilities.h"
#include <vector>
#include "Cookie.h"
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include "session.h"
#define PORT 443
class Server
{
private:
    std::string certLocation = Utilities::GetCurrentFolder() + "cert.crt";
    std::string keyLocation = Utilities::GetCurrentFolder() + "Key.key";
    std::map<std::string, WebSession> *allSessions;
    Router mainRouter;
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ssl::context context_;

public:
    Server(boost::asio::io_service &io_service, std::map<std::string, WebSession> *allSessionsPTR);
    void start_accept();

    void handle_accept(session *new_session,
                       const boost::system::error_code &error);
};
void ClearOldSessions(std::map<std::string, WebSession> *allSessions);

#endif