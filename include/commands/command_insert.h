#pragma once

#include "command.h"

class CommandInsert : public Command
{
public:
    CommandInsert();
    CommandInsert(const CommandInsert& other);
    CommandInsert(CommandInsert&& other);
    ~CommandInsert() = default;

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) override;
    virtual std::string getUsage() override;
};