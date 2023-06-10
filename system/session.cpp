#include "session.h"
#include <string>
ssl_socket::lowest_layer_type &session::socket()
{
  return socket_.lowest_layer();
}
void session::start()
{
  socket_.async_handshake(boost::asio::ssl::stream_base::server,
                          boost::bind(&session::handle_handshake, this,
                                      boost::asio::placeholders::error));
}
void session::handle_handshake(const boost::system::error_code &error)
{
  if (!error)
  {
    // LastUsed=time(NULL);
    // deadline_.expires_from_now(boost::posix_time::seconds(SecondsToKeepAlive));

    // deadline_.async_wait(boost::bind(&session::CheckDeadline, this));
    thisHeader.Cookies.clear();
    thisHeader.Parameters.clear();
    thisHeader.PostParameters.clear();
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&session::handle_write, this,
                                        boost::asio::placeholders::error));
  }
  else
  {
    delete this;
  }
}
void session::handle_read(const boost::system::error_code &error,
                          size_t bytes_transferred)
{
  if (!error)
  {
    boost::asio::async_write(socket_,
                             boost::asio::buffer(data_, bytes_transferred),
                             boost::bind(&session::handle_write, this,
                                         boost::asio::placeholders::error));
  }
  else
  {
    delete this;
  }
}
void session::handle_write(const boost::system::error_code &error)
{
  if (!error)
  {
    std::string inbound(data_);
    boost::algorithm::trim(inbound);
    if (inbound.size() >= max_length - 5)
    {
    }
    if (inbound.size() > 0 && inbound.find(' ') != std::string::npos && (inbound.substr(0, inbound.find(' ')) == "GET" || inbound.substr(0, inbound.find(' ')) == "POST" || inbound.substr(0, inbound.find(' ')) == "HEAD" || inbound.substr(0, inbound.find(' ')) == "PUT" || inbound.substr(0, inbound.find(' ')) == "DELETE" || inbound.substr(0, inbound.find(' ')) == "CONNECT" || inbound.substr(0, inbound.find(' ')) == "OPTIONS" || inbound.substr(0, inbound.find(' ')) == "TRACE" || inbound.substr(0, inbound.find(' ')) == "PATCH"))
    {
      bool URLEncoded = false;
      FormData = false;
      boundary = "";
      std::vector<std::string> headerSplit;
      boost::split(headerSplit, inbound, boost::is_any_of("\n"));
      bool foundSession = false;
      SessionLock->lock();
      for (size_t i = 0; i < headerSplit.size(); i++)
      {
        if (i == 0)
        {
          std::vector<std::string> methodSplit;
          boost::split(methodSplit, headerSplit[i], boost::is_any_of(" "));
          if (methodSplit.size() >= 3)
          {
            thisHeader.Method = methodSplit[0];
            std::vector<std::string> URLHalf;
            boost::split(URLHalf, methodSplit[1], boost::is_any_of("?"));
            thisHeader.Page = URLHalf[0];
            if (thisHeader.Page.length() + 1 < methodSplit[1].length())
            {
              std::vector<std::string> parameterSplit;
              boost::split(parameterSplit, methodSplit[1].substr(thisHeader.Page.length() + 1), boost::is_any_of("&"));
              for (size_t j = 0; j < parameterSplit.size(); j++)
              {
                std::vector<std::string> thisParameterSplit;
                boost::split(thisParameterSplit, parameterSplit[j], boost::is_any_of("="));
                URLParameter thisParameter;
                thisParameter.setName(thisParameterSplit[0]);
                thisParameter.Value = "";
                for (size_t k = 1; k < thisParameterSplit.size(); k++)
                {
                  thisParameter.Value += thisParameterSplit[k];
                  if (k < thisParameterSplit.size() - 1)
                  {
                    thisParameter.Value += "=";
                  }
                }
                thisParameter.setValue(thisParameter.Value);
                thisHeader.Parameters.push_back(thisParameter);
              }
            }
          }
        }
        else
        {
          std::vector<std::string> lineSplit;
          boost::split(lineSplit, headerSplit[i], boost::is_any_of(" "));
          if (lineSplit.size() > 1 && lineSplit[0] == "Host:")
          {
            thisHeader.Host == lineSplit[1];
          }
          else if (lineSplit.size() > 1 && lineSplit[0] == "Content-Length:")
          {
            try
            {

              ContentLength = std::stoi(lineSplit[1].substr(0, lineSplit[1].size() - 1));
            }
            catch (...)
            {
            }
          }
          else if (lineSplit.size() > 1 && lineSplit[0] == "Cookie:")
          {
            for (size_t j = 1; j < lineSplit.size(); j++)
            {
              std::vector<std::string> CookieSplit;
              boost::split(CookieSplit, lineSplit[j], boost::is_any_of("="));
              if (CookieSplit.size() == 2)
              {
                Cookie thisCookie;
                thisCookie.Name = CookieSplit[0];
                thisCookie.Value = CookieSplit[1].substr(0, CookieSplit[1].length());
                boost::algorithm::trim(thisCookie.Value);
                if (thisCookie.Name == "SessionID")
                {
                  if (allSessions->count(thisCookie.Value))
                  {
                    foundSession = true;
                    allSessions->at(thisCookie.Value).UpdateTime();
                    thisHeader.Session = &allSessions->at(thisCookie.Value);
                  }
                }
                else
                {
                  thisHeader.Cookies.push_back(thisCookie);
                }
              }
            }
          }
          else if (lineSplit.size() > 1 && lineSplit[0] == "Content-Type:")
          {

            boost::algorithm::trim(lineSplit[1]);
            if (lineSplit[1] == "application/x-www-form-urlencoded")
            {
              URLEncoded = true;
            }
            else if (lineSplit[1] == "multipart/form-data;" && lineSplit.size() > 2 && lineSplit[2].size() > 9)
            {
              FormData = true;
              boundary = "--" + lineSplit[2].substr(9) + "\n";
            }
          }
          else if (URLEncoded == true && i == headerSplit.size() - 1 && headerSplit[i].size() > 2)
          {
            std::string thisLine = headerSplit[i].substr(0,ContentLength);
            std::vector<std::string> POSTParameter;
            boost::split(POSTParameter, thisLine, boost::is_any_of("&"));
            for (size_t k = 0; k < POSTParameter.size(); k++)
            {
              std::vector<std::string> ParameterValues;
              boost::split(ParameterValues, POSTParameter[k], boost::is_any_of("="));
              if (ParameterValues.size() == 2)
              {
                URLParameter thisParameter;
                thisParameter.setName(ParameterValues[0]);
                thisParameter.setValue(ParameterValues[1]);
                thisHeader.PostParameters.push_back(thisParameter);
              }
            }
          }
        }
      }
      if (!foundSession)
      {
        WebSession thisSession;
        thisSession.SetSession();
        thisSession.UpdateTime();
        allSessions->insert_or_assign(thisSession.GetSession(), thisSession);
        thisHeader.Session = &allSessions->at(thisSession.GetSession());
      }
      SessionLock->unlock();
      if (!FormData)
      {
        Route *thisRoute = mainRouter->CheckRoute(thisHeader);
        response = thisRoute->Response(thisHeader).Output();
        int responseSize = response.length();
        auto test = boost::asio::buffer(response, response.length());
        int test2 = test.size();
        boost::asio::async_write(socket_,boost::asio::buffer(response, response.length()), boost::bind(&session::handle_handshake, this, boost::asio::placeholders::error));
      }
      else
      {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&session::handle_write, this,
                                            boost::asio::placeholders::error));
      }
    }
    else if (FormData)
    {
      inbound = "";
      for (int i = 0; i < max_length; i++)
      {
        inbound.push_back(data_[i]);
      }
      partialForm += inbound;
      if (partialForm.size() >= ContentLength)
      {
        partialForm = partialForm.substr(0, ContentLength);
        int findlocation = 0;
        int lastLocation = 0;
        while (findlocation >= 0)
        {
          URLParameter thisParameter;
          findlocation = partialForm.find(boundary, lastLocation);
          if ((findlocation > 0 && lastLocation > 0))
          {
            std::string thisData = partialForm.substr(lastLocation, findlocation - lastLocation);
            int namePosition = thisData.find("name=\"") + 6;
            if (namePosition > 6)
            {
              int SecondQuote = thisData.find('"', namePosition);
              thisParameter.Name = thisData.substr(namePosition, SecondQuote - namePosition);
            }
            int filenamePosition = thisData.find("filename=\"") + 10;
            int firstLine = thisData.find('\n');
            if (filenamePosition > 10 && filenamePosition < firstLine)
            {
              thisParameter.FileName = thisData.substr(filenamePosition, thisData.find('"', filenamePosition) - filenamePosition);
            }
            if (thisData.find("\r\n\r\n") != std::string::npos)
            {
              thisParameter.Value = thisData.substr(thisData.find("\r\n\r\n") + 4);
            }
            thisHeader.PostParameters.push_back(thisParameter);
            lastLocation = findlocation + boundary.size();
          }
          else if (lastLocation == 0)
          {
            lastLocation = findlocation + boundary.size();
          }
        }
        std::string lastBit = partialForm.substr(partialForm.size() - (boundary.size() + 2), boundary.size() - 2);
        if (lastBit == boundary.substr(0, boundary.size() - 2))
        {

          URLParameter thisParameter;
          std::string thisData = partialForm.substr(lastLocation, findlocation - lastLocation);
          int namePosition = thisData.find("name=\"") + 6;
          if (namePosition > 6)
          {
            int SecondQuote = thisData.find('"', namePosition);
            thisParameter.Name = thisData.substr(namePosition, SecondQuote - namePosition);
          }
          int filenamePosition = thisData.find("filename=\"") + 10;
          int firstLine = thisData.find('\n');
          if (filenamePosition > 10 && filenamePosition < firstLine)
          {
            thisParameter.FileName = thisData.substr(filenamePosition, thisData.find('"', filenamePosition) - filenamePosition);
          }
          if (thisData.find("\r\n\r\n") != std::string::npos)
          {
            int newLine = thisData.find("\r\n\r\n") + 4;
            thisParameter.Value = thisData.substr(newLine, thisData.size() - newLine - boundary.size() - 4);
          }
          thisHeader.PostParameters.push_back(thisParameter);
          lastLocation = findlocation + boundary.size();
        }

        else
        {
          partialForm = partialForm.substr(lastLocation);
        }

        Route *thisRoute = mainRouter->CheckRoute(thisHeader);
        std::string response = thisRoute->Response(thisHeader).Output();
        socket_.async_write_some(boost::asio::buffer(response, response.length()), boost::bind(&session::handle_handshake, this, boost::asio::placeholders::error));
      }
      else
      {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&session::handle_write, this,
                                            boost::asio::placeholders::error));
      }
    }
  }
  else
  {
    delete this;
  }
}