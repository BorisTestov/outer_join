#include "command_create.h"

CommandCreate::CommandCreate() :
    Command("create")
{}

CommandCreate::CommandCreate(const CommandCreate& other) :
    Command(other)
{}

CommandCreate::CommandCreate(CommandCreate&& other) :
    Command(std::move(other))
{}

Result CommandCreate::execute(std::shared_ptr<Controller> controller, std::stringstream& args)
{
    std::string name;
    args >> name;
    if (name.empty())
    {
        return Result::ResultCode::WRONG_ARGUMENT;
    }
    return controller->createTable(name);
}

std::string CommandCreate::getUsage()
{
    return "create <table name>";
}
