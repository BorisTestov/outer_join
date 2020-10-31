#include "server.h"

#include "session.h"

Server::Server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint, shellPtr shell) :
    _acceptor(io_service, endpoint),
    _socket(io_service),
    _clients(),
    _shell(shell)
{
    accept();
}

void Server::accept()
{
    _acceptor.async_accept(_socket,
                           [this](boost::system::error_code ec) {
                               if (!ec)
                               {
                                   auto session_new = std::make_shared<Session>(std::move(_socket), _clients, _shell);
                                   _clients.insert(session_new);
                                   session_new->start();
                               }
                               accept();
                           });
}
