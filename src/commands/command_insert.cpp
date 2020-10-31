#include "command_insert.h"

CommandInsert::CommandInsert() :
    Command("insert")
{}

CommandInsert::CommandInsert(const CommandInsert& other) :
    Command(other)
{}

CommandInsert::CommandInsert(CommandInsert&& other) :
    Command(std::move(other))
{}

Result CommandInsert::execute(std::shared_ptr<Controller> controller, std::stringstream& args)
{
    std::string tableName;
    args >> tableName;

    if (tableName.empty())
    {
        return Result::ResultCode::WRONG_ARGUMENT;
    }

    std::shared_ptr<Table> table = controller->getTable(tableName);
    if (nullptr == table)
    {
        return Result::ResultCode::UNKNOWN_TABLE;
    }

    int id;
    args >> id;
    if (args.bad())
    {
        return Result::ResultCode::WRONG_ARGUMENT;
    }

    std::string name;
    args >> name;
    if (name.empty())
    {
        return Result::ResultCode::WRONG_ARGUMENT;
    }

    return table->addValue(id, name);
}

std::string CommandInsert::getUsage()
{
    return "insert <table name> <id> <value>";
}
