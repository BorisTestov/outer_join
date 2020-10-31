#include "command_intersection.h"

CommandIntersection::CommandIntersection() :
    Command("intersection")
{}

CommandIntersection::CommandIntersection(const CommandIntersection& other) :
    Command(other)
{}

CommandIntersection::CommandIntersection(CommandIntersection&& other) :
    Command(std::move(other))
{}

Result CommandIntersection::execute(std::shared_ptr<Controller> controller, std::stringstream& args)
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
    return tableLeft->intersection(tableRight);
}

std::string CommandIntersection::getUsage()
{
    return "intersection";
}
