#include "session.h"

Session::Session(boost::asio::ip::tcp::socket socket, std::set<std::shared_ptr<Session>>& container, shellPtr shell) :
    _socket(std::move(socket)),
    _symbol(0),
    _read_line(""),
    _container(container),
    _shell(shell)
{}

void Session::start()
{
    read();
}

void Session::read()
{
    auto self(shared_from_this());
    boost::asio::async_read(_socket,
                            boost::asio::buffer(&_symbol, 1),
                            [this, self](boost::system::error_code errorCode, std::size_t length) {
                                (void) length;
                                if (not errorCode)
                                {
                                    if ('\n' != _symbol)
                                    {
                                        _read_line += _symbol;
                                    }
                                    else
                                    {
                                        if ('\r' == _read_line.back())
                                        {
                                            _read_line.pop_back();
                                        }
                                        std::string res(_shell->execute(_read_line));
                                        boost::asio::async_write(_socket,
                                                                 boost::asio::buffer(res.data(), res.length()),
                                                                 [](const boost::system::error_code& error, std::size_t bytes_transferred) {
                                                                     (void) bytes_transferred;
                                                                     if (error)
                                                                         std::cout << "Error while writing data: "
                                                                                   << error.message() << std::endl;
                                                                 });
                                        _read_line.clear();
                                    }
                                    read();
                                }
                                else
                                {
                                    _container.erase(self);
                                    _socket.close();
                                }
                            });
}
