#include "controller.h"
#include "server.h"
#include "session.h"
#include "shell.h"
#include "version.h"

#include <boost/asio.hpp>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, char** argv)
{
    std::cout << "Current version: " << version() << std::endl;

    if (argc != 2)
    {
        std::cout << "Using: join_server <port> " << std::endl;
        return -1;
    }

    std::shared_ptr<Controller> controller = std::make_shared<Controller>();
    shellPtr shell = std::make_shared<Shell>(controller);

    std::stringstream init;
    init << "create A" << std::endl;
    init << "create B" << std::endl;

    {
        std::string line;
        while (std::getline(init, line))
        {
            /*std::cout << "line:" <<*/ shell->execute(line) /*<< std::endl*/;
        }
    }

    int port(atoi(argv[1]));
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    Server serverDB(io_service, endpoint, shell);

    io_service.run();
    return 0;
}
