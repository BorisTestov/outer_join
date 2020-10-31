#pragma once

#include "command.h"

class CommandCreate : public Command
{
public:
    CommandCreate();
    CommandCreate(const CommandCreate& other);
    CommandCreate(CommandCreate&& other);
    ~CommandCreate() = default;

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) override;
    virtual std::string getUsage() override;
};