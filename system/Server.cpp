#include "Server.h"
#include "URLParameter.h"
void HandleMessage(SOCKET AcceptSocket, int DATA_BUFSIZE);

std::mutex SessionLock;
Server::Server(boost::asio::io_service &io_service, std::map<std::string, WebSession> *allSessionsPTR)
    : io_service_(io_service),
      acceptor_(io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT)),
      context_(boost::asio::ssl::context::sslv23)
{
  allSessions = allSessionsPTR;
  mainRouter.LoadRoutes();
  context_.set_options(
      boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 | boost::asio::ssl::context::single_dh_use);
  // context_.set_password_callback(boost::bind(&server::get_password, this));
  context_.use_certificate_chain_file(certLocation);
  context_.use_private_key_file(keyLocation, boost::asio::ssl::context::pem);
  // context_.use_tmp_dh_file("dh512.pem");

  start_accept();
}
void Server::start_accept()
{
  session *new_session = new session(io_service_, context_, allSessions, &mainRouter, &SessionLock);
  acceptor_.async_accept(new_session->socket(),
                         boost::bind(&Server::handle_accept, this, new_session,
                                     boost::asio::placeholders::error));
}
void Server::handle_accept(session *new_session,
                           const boost::system::error_code &error)
{
  if (!error)
  {
    new_session->start();
  }
  else
  {
    delete new_session;
  }

  start_accept();
}

void ClearOldSessions(std::map<std::string, WebSession> *allSessions)
{
  while (true)
  {
    SessionLock.lock();
    for (auto i = allSessions->begin(); i != allSessions->end();)
    {
      if (!i->second.CheckTime())
      {
        allSessions->erase(i++->first);
      }
      else
      {
        ++i;
      }
    }
    SessionLock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
}