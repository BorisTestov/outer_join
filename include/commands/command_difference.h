#pragma once

#include "command.h"

class CommandDifference : public Command
{
public:
    CommandDifference();
    CommandDifference(const CommandDifference& other);
    CommandDifference(CommandDifference&& other);
    ~CommandDifference() = default;

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) override;
    virtual std::string getUsage() override;
};