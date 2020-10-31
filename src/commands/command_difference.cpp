#include "command_difference.h"

CommandDifference::CommandDifference() :
    Command("symmetric_difference")
{}

CommandDifference::CommandDifference(const CommandDifference& other) :
    Command(other)
{}

CommandDifference::CommandDifference(CommandDifference&& other) :
    Command(std::move(other))
{}

Result CommandDifference::execute(std::shared_ptr<Controller> controller, std::stringstream& args)
{
    (void) args;
    std::shared_ptr<Table> tableLeft = controller->getTable("A");
    if (tableLeft == nullptr)
    {
        return { Result::ResultCode::UNKNOWN_TABLE, { "A" } };
    }

    std::shared_ptr<Table> tableRight = controller->getTable("B");
    if (tableRight == nullptr)
    {
        return { Result::ResultCode::UNKNOWN_TABLE, { "B" } };
    }

    Result result = tableLeft->symmetricDifference(tableRight);
    return result;
}

std::string CommandDifference::getUsage()
{
    return "symmetric_difference";
}
