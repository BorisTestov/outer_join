#pragma once

#include "command.h"

class CommandIntersection : public Command
{
public:
    CommandIntersection();
    CommandIntersection(const CommandIntersection& other);
    CommandIntersection(CommandIntersection&& other);
    ~CommandIntersection() = default;

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) override;
    virtual std::string getUsage() override;
};