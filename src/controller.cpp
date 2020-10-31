#include "controller.h"

Result Controller::createTable(std::string name)
{
    if (_tables.count(name) != 0)
    {
        return Result::ResultCode::TABLE_ALREADY_EXISTS;
    }
    _tables[name] = std::make_shared<Table>();
    return Result::ResultCode::OK;
}

Controller::tablePtr Controller::getTable(std::string name)
{
    if (_tables.count(name) == 0)
    {
        return nullptr;
    }
    return _tables[name];
}

Result Controller::insert(std::string name, int id, std::string value)
{
    tablePtr table = getTable(name);
    if (table == nullptr)
    {
        return Result::ResultCode::UNKNOWN_TABLE;
    }
    return table->addValue(id, value);
}

Result Controller::truncate(std::string name)
{
    tablePtr table = getTable(name);
    if (table == nullptr)
    {
        return Result::ResultCode::UNKNOWN_TABLE;
    }
    return table->truncate();
}
