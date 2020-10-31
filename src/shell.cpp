#include "shell.h"

Shell::Shell(std::shared_ptr<Controller> controller) :
    _controller(controller), _commands()
{
    std::shared_ptr<Command> ptrCommand;

    ptrCommand = std::make_shared<CommandCreate>();
    _commands[ptrCommand->getName()] = ptrCommand;

    ptrCommand = std::make_shared<CommandInsert>();
    _commands[ptrCommand->getName()] = ptrCommand;

    ptrCommand = std::make_shared<CommandIntersection>();
    _commands[ptrCommand->getName()] = ptrCommand;

    ptrCommand = std::make_shared<CommandDifference>();
    _commands[ptrCommand->getName()] = ptrCommand;

    ptrCommand = std::make_shared<CommandTruncate>();
    _commands[ptrCommand->getName()] = ptrCommand;
}

Shell::~Shell()
{
    _commands.clear();
}
std::string Shell::execute(std::string strCommand)
{
    std::lock_guard<std::mutex> lock(_mutexTransaction);
    std::stringstream sstream(strCommand);

    std::string command;
    sstream >> command;

    std::string result;

    if (_commands.count(command) == 0)
    {
        result = std::string("ERR ") + "Command " + command + " not found.\n";
    }
    else
    {
        std::shared_ptr<Command> ptrCommand = _commands[command];
        auto Res = ptrCommand->exec(_controller, sstream);
        result = Res.toString();
    }
    return result;
}
