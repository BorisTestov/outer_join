#include "commands/command.h"

Command::Command(std::string name) :
    _name(name)
{
}

Command::Command(const Command& other) :
    _name(other._name)
{
}

Command::Command(Command&& other) :
    _name(other._name)
{
}

Result Command::exec(std::shared_ptr<Controller> controller, std::stringstream& args)
{
    return execute(controller, args);
}

std::string Command::usage()
{
    return getUsage();
}

std::string Command::getName()
{
    return _name;
}
