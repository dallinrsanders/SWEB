#ifndef SESSION_H
#define SESSION_H
#include <cstdlib>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "boost/beast/core/buffers_to_string.hpp"
#include "Route.h"
#include "Router.h"
#include "WebSession.h"
#include <boost/algorithm/string.hpp>
#include <mutex>
#include <boost/asio/deadline_timer.hpp>
#define max_length 8192
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
class session
{
public:
  session(boost::asio::io_service &io_service,
          boost::asio::ssl::context &context, std::map<std::string, WebSession> *AllSessions, Router *MainRouter, std::mutex *sessionLock)
      : socket_(io_service, context),
        deadline_(io_service)
  {
    allSessions = AllSessions;
    mainRouter = MainRouter;
    SessionLock = sessionLock;
  }

  ssl_socket::lowest_layer_type &socket();

  void start();

  void handle_handshake(const boost::system::error_code &error);

  void handle_read(const boost::system::error_code &error,
                   size_t bytes_transferred);

  void handle_write(const boost::system::error_code &error);
  void shutdown(const boost::system::error_code &error);
  void CheckDeadline();

private:
  ssl_socket socket_;
  char data_[max_length];
  std::map<std::string, WebSession> *allSessions;
  Router *mainRouter;
  std::mutex *SessionLock;
  boost::asio::deadline_timer deadline_;
  time_t LastUsed = time(NULL);
  int SecondsToKeepAlive = 30;
  bool FormData = false;
  std::string boundary = "";
  Header thisHeader;
  std::string partialForm = "";
  int ContentLength = 0;
  std::string response="";
};
#endif