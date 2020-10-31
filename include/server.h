#pragma once

#include "session.h"
#include "shell.h"

#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>

class Server
{
public:
    Server(boost::asio::io_service& io_service,
           const boost::asio::ip::tcp::endpoint& endpoint,
           shellPtr shell);

private:
    void accept();
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;
    std::set<std::shared_ptr<Session>> _clients;
    shellPtr _shell;
};