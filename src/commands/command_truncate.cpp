#include "command_truncate.h"

CommandTruncate::CommandTruncate() :
    Command("truncate")
{}

CommandTruncate::CommandTruncate(const CommandTruncate& other) :
    Command(other)
{}

CommandTruncate::CommandTruncate(CommandTruncate&& other) :
    Command(std::move(other))
{}

Result CommandTruncate::execute(std::shared_ptr<Controller> controller, std::stringstream& args)
{
    std::string tablename;
    args >> tablename;
    if (!args.eof())
    {
        return { Result::ResultCode::WRONG_ARGUMENT };
    }

    std::shared_ptr<Table> table = controller->getTable(tablename);

    if (table == nullptr)
    {
        return { Result::ResultCode::UNKNOWN_TABLE, { tablename } };
    }
    return table->truncate();
}

std::string CommandTruncate::getUsage()
{
    return "truncate <table name>";
}
