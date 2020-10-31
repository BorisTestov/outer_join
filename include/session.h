#pragma once

#include "shell.h"

#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket,
            std::set<std::shared_ptr<Session>>& container,
            shellPtr shell);
    virtual ~Session() = default;
    void start();

private:
    void read();
    boost::asio::ip::tcp::socket _socket;
    char _symbol;
    std::string _read_line;
    std::set<std::shared_ptr<Session>>& _container;
    shellPtr _shell;
};